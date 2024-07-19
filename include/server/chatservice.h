#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include "usermodel.h"
#include "offlinemsgmodel.h"

#include <muduo/net/TcpServer.h>
#include <json.h>
#include <functional>
#include <unordered_map>
#include <mutex>

using json = nlohmann::json;

// 消息处理器
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr&, json&, muduo::Timestamp)>;

// 业务处理类
class ChatService {
public:
    // 获取唯一实例
    static ChatService& GetInstance();

    // 登录业务
    void Login(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time);

    // 注册业务
    void Register(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time);

    // 一对一聊天业务
    void OneToOneChat(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time);

    // 获取消息处理器
    MsgHandler GetMsgHandler(int msgid);

    // 客户端异常退出处理函数
    void ClientExceptionHandler(const muduo::net::TcpConnectionPtr&);

    // 服务端异常退出处理函数
    void Reset();
    
private:
    ChatService();
    ChatService(const ChatService&) = delete;
    ChatService(ChatService&&) = delete;
    ChatService& operator=(const ChatService&) = delete; 
    ChatService& operator=(ChatService&&) = delete; 

    // 消息类型与消息处理器的映射表
    std::unordered_map<int, MsgHandler> handler_map_;

    // 存放已登录（在线）用户的连接与id的映射
    std::unordered_map<int, muduo::net::TcpConnectionPtr> conn_map_;

    // 维护连接映射表的线程安全的锁
    std::mutex conn_mutex_;

    // 对应表的数据操作类
    UserModel user_model_;  // user表
    OfflineMsgModel offlinemsg_model_;  // offlinemessage表
};

#endif