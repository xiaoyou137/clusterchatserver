#include "chatservice.hpp"
#include "public.hpp"
#include <functional>
#include <muduo/base/Logging.h>

using namespace muduo;

using namespace std::placeholders;

// 单例类，获取实例对象
ChatService *ChatService::instance()
{
    static ChatService instance;
    return &instance;
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int id = js["id"].get<int>();
    string passwd = js["passwd"];
    // 使用id查询User表
    User user = _userModel.query(id);

    json response;
    if (user.getId() == -1)
    { // 用户不存在
        response["msgid"] = LOGIN_MSG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "该用户不存在!";
    }
    else
    {
        if (user.getState() == "online")
        { // 重复登录
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "该用户已经登录!";
        }
        else if (user.getPasswd() != passwd)
        { // 密码错误
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 3;
            response["errmsg"] = "密码错误!";
        }
        else
        { // 用户登录成功

            // 更新状态为online
            user.setState("online");
            _userModel.updatestate(user);

            // 保存用户连接
            {
                std::lock_guard<std::mutex> lock(_connMutex);
                _userConnMap.insert({id, conn});
            }

            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();

            // 检查离线消息，并发送给用户
            std::vector<std::string> vec = _offlineMsgModel.query(id);
            if (!vec.empty())
            {
                response["offlinemsg"] = vec;
                // 删除数据库中的离线消息
                _offlineMsgModel.remove(id);
            }

            // 返回好友列表
            vec = _friendModel.query(id);
            if(!vec.empty())
            {
                response["friend"] = vec;
            }
        }
    }
    conn->send(response.dump());
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    std::string name = js["name"];
    std::string passwd = js["passwd"];
    User user(-1, name, "offline", passwd);
    // 向user表中插入数据（注册用户数据）
    bool state = _userModel.insert(user);
    json response;
    if (state)
    { // 注册成功，构建返回json
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.getId();
    }
    else
    {
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "reg failed!";
    }

    // 发送响应消息给客户端
    conn->send(response.dump());
}

// 一对一聊天
void ChatService::onechat(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int toid = js["to"].get<int>();
    {
        std::lock_guard<std::mutex> lock(_connMutex);
        auto it = _userConnMap.find(toid);
        if (it != _userConnMap.end())
        {
            // toid用户在线,直接转发消息
            it->second->send(js.dump());
            return;
        }
    }
    // toid用户不在线，离线存储消息
    _offlineMsgModel.insert(toid, js.dump());
}

// 添加好友
void ChatService::addfriend(const TcpConnectionPtr& conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int friendid = js["friendid"].get<int>();

    _friendModel.insert(userid, friendid);
}

// 注册msgid对应的业务处理函数
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
    _msgHandlerMap.insert({ONE_CHAT_MSG, std::bind(&ChatService::onechat, this, _1, _2, _3)});
    _msgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addfriend, this, _1, _2, _3)});
}

// 获取msgid对应的处理函数
MsgHandler ChatService::getHandler(int msgid)
{
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {
        // msgid错误，返回一个空操作，并提示错误
        return [=](const TcpConnectionPtr &, json &js, Timestamp)
        {
            LOG_ERROR << "msgid: " << msgid << "can not found its handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}

// 处理客户端异常退出
void ChatService::clientClosedException(const TcpConnectionPtr &conn)
{
    User user;
    {
        std::lock_guard<std::mutex> lock(_connMutex);
        for (auto it = _userConnMap.begin(); it != _userConnMap.end(); it++)
        {
            if (it->second == conn)
            {
                // 设置user id
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }

    if (user.getId() != -1)
    {
        // 重置用户状态为offline
        user.setState("offline");
        _userModel.updatestate(user);
    }
}