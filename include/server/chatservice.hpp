#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemsgmodel.hpp"
#include "friendmodel.hpp"

using namespace muduo::net;
using namespace muduo;
using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr &, json &js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 单例类，获取实例对象
    static ChatService *instance();

    // 处理登录业务
    void login(const TcpConnectionPtr &, json &js, Timestamp);
    // 处理注册业务
    void reg(const TcpConnectionPtr &, json &js, Timestamp);
    // 一对一聊天
    void onechat(const TcpConnectionPtr &, json &js, Timestamp);
    // 添加好友
    void addfriend(const TcpConnectionPtr &, json &js, Timestamp);

    // 处理服务器异常退出，重置业务
    void reset()
    {
        _userModel.reset();
    }
    
    
    
    // 获取msgid对应的处理函数
    MsgHandler getHandler(int msgid);

    // 处理客户端异常退出
    void clientClosedException(const TcpConnectionPtr& conn);

private:
    // 作为单例类，私有化构造函数，删除拷贝构造和赋值运算符
    ChatService();
    ChatService(const ChatService &) = delete;
    ChatService &operator=(const ChatService &) = delete;
    // 存储msgid和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储User id 和其对应的连接
    std::unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 互斥量，保证对_userConnMap;操作的线程安全
    std::mutex _connMutex;

    // 存储离线消息
    OfflineMsgModel _offlineMsgModel;
    // 组合user表操作类
    UserModel _userModel;
    // friend操作类
    FriendModel _friendModel;
};

#endif