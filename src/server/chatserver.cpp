#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"
#include <string>

using namespace std::placeholders;
using json = nlohmann::json;

//初始化chatserver聊天服务器
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
                       : server_(loop, listenAddr, nameArg),
                       loop_(loop)
{
    // 注册链接回调
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 注册消息回调
    server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    // 设置线程数量
    server_.setThreadNum(4);
}

//启动server
void ChatServer::start()
{
    server_.start();
}

// 链接回调函数
void ChatServer::onConnection(const TcpConnectionPtr & conn)
{
    if(!conn->connected()) // 如果链接断开
    {
        // 处理客户端异常退出的情况
        ChatService::instance()->clientClosedException(conn);
        // 释放链接资源
        conn->shutdown(); 
    }
}

// 消息回调函数
void ChatServer::onMessage(const TcpConnectionPtr & conn,
                           Buffer * buffer,
                           Timestamp time)
{
    // 获取消息缓冲区所有字符
    std::string sbuf = buffer->retrieveAllAsString();
    // 利用json进行反序列化
    json js = json::parse(sbuf);
    // 将网络I/O与业务模块解耦，一个js["msgid"]对应一个服务器service处理函数（msgHandler）
    // 通过js["msgid"],找到对应的处理函数，并调用
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn, js, time);

}