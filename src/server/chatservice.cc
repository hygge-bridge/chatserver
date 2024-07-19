#include "chatservice.h"
#include "public.h"
#include <muduo/base/Logging.h>
#include <iostream>

ChatService& ChatService::GetInstance() {
    static ChatService service;
    return service;
}

ChatService::ChatService() {
    // 注册消息类型和事件处理器的映射关系
    handler_map_.insert({kLoginMsg, std::bind(&ChatService::Login, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});
    handler_map_.insert({kRegisterMsg, std::bind(&ChatService::Register, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});   
    handler_map_.insert({kOneToOneChatMsg, std::bind(&ChatService::OneToOneChat, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});                    
}

MsgHandler ChatService::GetMsgHandler(int msgid) {
    auto it = handler_map_.find(msgid);
    // 如果msgid没有对应的处理器，那么返回一个默认处理器
    if (it == handler_map_.end()) {
        return [=](const muduo::net::TcpConnectionPtr&, json &, muduo::Timestamp) {
            LOG_ERROR << "msgid:" << msgid << " cannot find the handler!";
        };
    }
    return it->second;
}

void ChatService::Login(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int id = js["id"];
    std::string password = js["password"];
    User user = user_model_.Query(id);

    json response;
    response[kMsgId] = kLoginAckMsg;
    // 账户密码均正确
    if (user.GetId() == id && user.GetPassword() == password) {
        // 用户已经登录，无需重新登陆
        if (user.GetState() == "online") {
            response[kErrNo] = 2;
            response[kErrMsg] = "The user has already logged in!";
        }
        else {  
            // 登录成功，保存连接
            {
                std::lock_guard<std::mutex> lock(conn_mutex_);
                conn_map_.insert({id, conn});
            }
            user.SetState("online");
            user_model_.UpdateState(user);
            response[kErrNo] = 0;
            response[kId] = id;
            // 查看是否有离线消息
            std::vector<std::string> offlinemsg_vec = offlinemsg_model_.Query(id);
            if (!offlinemsg_vec.empty()) {
                response[kMsg] = offlinemsg_vec;
                offlinemsg_model_.Erase(id);
            }
        }
    }
    else {
        response[kErrNo] = 1;
        response[kErrMsg] = "Incorrect account or password!";
    }
    conn->send(response.dump());
}

void ChatService::Register(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    std::string name = js["name"];
    std::string password = js["password"];
    User user;
    user.SetName(name);
    user.SetPassword(password);
    bool insert_state = user_model_.Insert(user);
    // 填写json响应
    json response;
    response[kMsgId] = kRedisterAckMsg;
    if (insert_state) {
        response[kId] = user.GetId();
        response[kErrNo] = 0;
    }
    else {
        response[kErrNo] = 1;
        response[kErrMsg] = "Failed to insert into user!";
    }
    conn->send(response.dump());
}

// 用户在线时直接转化消息，用户离线时将消息存入离线消息表中
void ChatService::OneToOneChat(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int toid = js[kToId];
    {   
        std::lock_guard<std::mutex> lock(conn_mutex_);
        auto it = conn_map_.find(toid);
        if (it != conn_map_.end()) {
            it->second->send(js.dump());
            return;
        }
    }
    offlinemsg_model_.Insert(toid, js.dump());
}

// 当客户端断开连接时，需要重置用户的在线状态，将其设置为离线
void ChatService::ClientExceptionHandler(const muduo::net::TcpConnectionPtr& conn) {
    User user;
    {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        for (auto it = conn_map_.begin(); it != conn_map_.end(); ++it) {
            if (it->second == conn) {
                user.SetId(it->first);
                conn_map_.erase(it);
                break;
            }
        }
    }
    if (user.GetId() != -1) {
        user.SetState("offline");
        user_model_.UpdateState(user);
    }
}

void ChatService::Reset() {
    user_model_.ResetState();
}