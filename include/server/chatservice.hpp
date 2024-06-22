#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include "json.hpp"
#include "usermodel.hpp"


using namespace muduo::net;
using namespace muduo;
using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr&, json& js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 单例类，获取实例对象
    static ChatService* instance();

    // 处理登录业务
    void login(const TcpConnectionPtr&, json& js, Timestamp);
    // 处理注册业务
    void reg(const TcpConnectionPtr&, json& js, Timestamp);
    // 获取msgid对应的处理函数
    MsgHandler getHandler(int msgid);
private:
    // 作为单例类，私有化构造函数，删除拷贝构造和赋值运算符
    ChatService();
    ChatService(const ChatService&) = delete;
    ChatService& operator=(const ChatService&) = delete;
    // 存储msgid和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    // 组合user表操作类
    UserModel _userModel;
};

#endif