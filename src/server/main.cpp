#include "chatserver.hpp"
#include "chatservice.hpp"
#include <signal.h>
#include <iostream>

const string saddr = "127.0.0。1";

// 处理服务器CTRL+C，异常退出,重置状态
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        std::cout << "usage: ChatServer <port>" << std::endl;
    }

    int port = atoi(argv[1]);

    signal(SIGINT, resetHandler);
    
    EventLoop loop;
    InetAddress addr(saddr.c_str(), port);

    ChatServer server(&loop, addr, "chatserver");
    server.start();
    loop.loop();

}