#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Timestamp.h>
#include <functional>
#include <iostream>

using namespace std;
using namespace std::placeholders;
using namespace muduo::net;
using namespace muduo;

class ChatServer
{
public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg)
        : server_(loop, listenAddr, nameArg),
          loop_(loop)
    {
        server_.setConnectionCallback(std::bind(&ChatServer::OnConnection, this, _1));

        server_.setMessageCallback(std::bind(&ChatServer::OnMessage, this, _1, _2, _3));

        server_.setThreadNum(4);
    }

    void OnConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " status: on!" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " status: off!" << endl;
            conn->shutdown();
        }
    }

    void OnMessage(const TcpConnectionPtr &conn,
         Buffer *buf,
         Timestamp time)
    {
        string sendbuf = buf->retrieveAllAsString();
        conn->send(sendbuf);
    }

    void start()
    {
        server_.start();
    }

private:
    TcpServer server_;
    EventLoop *loop_;
};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start();
    loop.loop();

    return 0;
}
