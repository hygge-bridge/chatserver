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
    handler_map_.insert({kAddFriendMsg, std::bind(&ChatService::AddFriend, this, std::placeholders::_1, 
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
    int id = js[kUserId];
    std::string password = js[kUserPwd];
    User user = user_model_.Query(id);

    json response;
    response[kMsgId] = kLoginAckMsg;
    // 账户密码均正确
    if (user.GetId() == id && user.GetPassword() == password) {
        // 用户已经登录，无需重新登陆
        if (user.GetState() == kUserOnline) {
            response[kMsgErrNo] = 2;
            response[kMsgErr] = "The user has already logged in!";
        }
        else {  
            // 登录成功，保存连接
            {
                std::lock_guard<std::mutex> lock(conn_mutex_);
                conn_map_.insert({id, conn});
            }
            user.SetState(kUserOnline);
            user_model_.UpdateState(user);
            response[kMsgErrNo] = 0;
            response[kMsgUserId] = id;

            // 查看是否有离线消息，如果有就返回
            std::vector<std::string> offlinemsg_vec = offlinemsg_model_.Query(id);
            if (!offlinemsg_vec.empty()) {
                response[kMsg] = offlinemsg_vec;
                offlinemsg_model_.Erase(id);
            }

            // 返回好友列表
            std::vector<User> user_vec = friend_model_.Query(id);
            std::vector<std::string> friends;
            for (const User& user : user_vec) {
                json temp;
                temp[kUserId] = user.GetId();
                temp[kUserName] = user.GetName();
                temp[kUserState] = user.GetState();
                friends.push_back(temp.dump());
            }
            response[kMsgFriendList] = friends;
        }
    }
    else {
        response[kMsgErrNo] = 1;
        response[kMsgErr] = "Incorrect account or password!";
    }
    conn->send(response.dump());
}

void ChatService::Register(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    std::string name = js[kUserName];
    std::string password = js[kUserPwd];
    User user;
    user.SetName(name);
    user.SetPassword(password);
    bool insert_state = user_model_.Insert(user);
    // 填写json响应
    json response;
    response[kMsgId] = kRedisterAckMsg;
    if (insert_state) {
        response[kMsgUserId] = user.GetId();
        response[kMsgErrNo] = 0;
    }
    else {
        response[kMsgErrNo] = 1;
        response[kMsgErr] = "Failed to insert into user!";
    }
    conn->send(response.dump());
}

// 用户在线时直接转化消息，用户离线时将消息存入离线消息表中
void ChatService::OneToOneChat(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int toid = js[kMsgToId];
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

void ChatService::AddFriend(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int userid = js[kFriUserId];
    int friendid = js[kFriendId];
    friend_model_.Insert(userid, friendid);
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
        user.SetState(kUserOffline);
        user_model_.UpdateState(user);
    }
}

void ChatService::Reset() {
    user_model_.ResetState();
}