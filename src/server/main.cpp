#include "chatserver.hpp"

const string saddr = "127.0.0。1";

int main()
{
    EventLoop loop;
    InetAddress addr(saddr.c_str(), 6000);

    ChatServer server(&loop, addr, "chatserver");
    server.start();
    loop.loop();

}