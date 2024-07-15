#include "chatserver.h"

#include <functional>
#include <thread>

static int kThreadNum = 4;  // tcp server线程个数

ChatServer::ChatServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr,
            const std::string& nameArg)
    : tcp_server_(loop, listenAddr, nameArg)
    , event_loop_(loop) {
    // 注册回调
    tcp_server_.setConnectionCallback(std::bind(&ChatServer::OnConnection, this, std::placeholders::_1));
    tcp_server_.setMessageCallback(std::bind(&ChatServer::OnMessage, this, std::placeholders::_1,
                                    std::placeholders::_2, std::placeholders::_3));
    // 设置线程个数
    tcp_server_.setThreadNum(kThreadNum);
}

void ChatServer::OnConnection(const muduo::net::TcpConnectionPtr& conn) {

}

void ChatServer::OnMessage(const muduo::net::TcpConnectionPtr&,
                muduo::net::Buffer*,
                muduo::Timestamp) {
                    
}