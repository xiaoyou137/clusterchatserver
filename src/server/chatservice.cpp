#include "chatservice.hpp"
#include "public.hpp"
#include <functional>
#include <muduo/base/Logging.h>

using namespace muduo;

using namespace std::placeholders;

   // 单例类，获取实例对象
    ChatService* ChatService::instance()
    {
        static ChatService instance;
        return &instance;
    }

    // 处理登录业务
    void ChatService::login(const TcpConnectionPtr&, json& js, Timestamp)
    {
        LOG_INFO << "do login service!!!";
    }

    // 处理注册业务
    void ChatService::reg(const TcpConnectionPtr& conn, json& js, Timestamp time)
    {
        std::string name = js["name"];
        std::string passwd = js["passwd"];
        User user(name, passwd);
        // 向user表中插入数据（注册用户数据）
        bool state = _userModel.insert(user);
        json response;
        if(state)
        {// 注册成功，构建返回json
            response["msgid"] = REG_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
        }else{
            response["msgid"] = REG_MSG_ACK;
            response["errno"] = 1;
            response["errmsg"] = "reg failed!";
        }

        // 发送响应消息给客户端
        conn->send(response.dump());
    }

    // 注册msgid对应的业务处理函数
    ChatService::ChatService()
    {
        _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
        _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
    }

    // 获取msgid对应的处理函数
    MsgHandler ChatService::getHandler(int msgid)
    {
        auto it = _msgHandlerMap.find(msgid);
        if(it == _msgHandlerMap.end())
        {
            // msgid错误，返回一个空操作，并提示错误
            return [=](const TcpConnectionPtr&, json& js, Timestamp){
                LOG_ERROR << "msgid: " << msgid << "can not found its handler!";
            };
        }else{
            return _msgHandlerMap[msgid];
        }
    }