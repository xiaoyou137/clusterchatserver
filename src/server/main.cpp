#include "chatserver.hpp"

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);

    ChatServer server(&loop, addr, "chatserver");
    server.start();
    loop.loop();

}