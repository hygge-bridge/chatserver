#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <string>

// 服务器类，实现网络模块
class ChatServer {
public:
    ChatServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr,
            const std::string& nameArg);
    // 启动服务器
    void Start() { tcp_server_.start(); }
private:
    // 处理连接的回调函数
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    // 处理可读写事件的回调函数
    void OnMessage(const muduo::net::TcpConnectionPtr&,
                    muduo::net::Buffer*,
                    muduo::Timestamp);

    // 组合tcpserver对象
    muduo::net::TcpServer tcp_server_;
    // 组合eventloop对象
    muduo::net::EventLoop* event_loop_;
};

#endif