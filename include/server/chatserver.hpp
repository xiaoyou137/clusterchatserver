#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

class ChatServer
{
public:
    //初始化chatserver聊天服务器
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);
        
    //启动server
    void start();

private:
    // 链接回调函数
    void onConnection(const TcpConnectionPtr &);
    // 消息回调函数
    void onMessage(const TcpConnectionPtr &,
                   Buffer *,
                   Timestamp);

    TcpServer server_; // muduo实现的TcpServer封装
    EventLoop *loop_; // muduo网络库的loop
};

#endif