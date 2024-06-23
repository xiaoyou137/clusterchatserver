#include "chatserver.hpp"

const string saddr = "192.168.1.131";

int main()
{
    EventLoop loop;
    InetAddress addr(saddr.c_str(), 6000);

    ChatServer server(&loop, addr, "chatserver");
    server.start();
    loop.loop();

}