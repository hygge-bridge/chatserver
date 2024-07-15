#include "chatserver.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

int main() {
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer chat_server(&loop, addr, "ChatServer");
    chat_server.Start();
    loop.loop();
    return 0;
}