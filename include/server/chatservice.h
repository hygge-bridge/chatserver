#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include <muduo/net/TcpServer.h>
#include <json.h>
#include <functional>
#include <unordered_map>

using json = nlohmann::json;

// 消息处理器
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr&, json &, muduo::Timestamp)>;

// 业务处理类
class ChatService {
public:
    // 获取唯一实例
    static ChatService& GetInstance();

    // 登录业务
    void Login(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time);

    // 注册业务
    void Register(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time);

    // 获取消息处理器
    MsgHandler GetMsgHandler(int msgid);
    
private:
    ChatService();
    ChatService(const ChatService&) = delete;
    ChatService(ChatService&&) = delete;
    ChatService& operator=(const ChatService&) = delete; 
    ChatService& operator=(ChatService&&) = delete; 

    // 消息类型与消息处理器的映射表
    std::unordered_map<int, MsgHandler> handler_map_;
};

#endif