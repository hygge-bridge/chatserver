#include "chatserver.h"
#include "chatservice.h"
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
    // 连接断开时应回收对应的socket资源
    if (!conn->connected()) {
        ChatService::GetInstance().ClientExceptionHandler(conn);
        conn->shutdown();
    }
}

void ChatServer::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                muduo::net::Buffer* buffer,
                muduo::Timestamp time) {
    // 获取消息类型对应的处理器，利用回调机制实现对应业务方法的调用
    // 实现网络模块与业务模块的解耦
    std::string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    MsgHandler handler = ChatService::GetInstance().GetMsgHandler(js["msgid"].get<int>());
    handler(conn, js, time);
}