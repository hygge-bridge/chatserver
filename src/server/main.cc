#include "chatserver.h"
#include "chatservice.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <signal.h>

// 捕获信号SIGINT，重置用户状态后再退出
void SigHandler(int) {
    ChatService::GetInstance().Reset();
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGINT, SigHandler);

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer chat_server(&loop, addr, "ChatServer");
    chat_server.Start();
    loop.loop();
    return 0;
}