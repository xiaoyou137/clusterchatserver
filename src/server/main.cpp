#include "chatserver.hpp"
#include "chatservice.hpp"
#include <signal.h>

const string saddr = "127.0.0。1";

// 处理服务器CTRL+C，异常退出,重置状态
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main()
{

    signal(SIGINT, resetHandler);
    
    EventLoop loop;
    InetAddress addr(saddr.c_str(), 6000);

    ChatServer server(&loop, addr, "chatserver");
    server.start();
    loop.loop();

}