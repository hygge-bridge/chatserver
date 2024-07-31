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

    handler_map_.insert({kCreateGroupMsg, std::bind(&ChatService::CreateGroup, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});
    handler_map_.insert({kAddGroupMsg, std::bind(&ChatService::AddGroup, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});  
    handler_map_.insert({kChatGroupMsg, std::bind(&ChatService::ChatGroup, this, std::placeholders::_1, 
                        std::placeholders::_2, std::placeholders::_3)});           
    // 注册redis的消息回调
    if (redis_.Connect()) {
        redis_.InitNotifyHandler(std::bind(&ChatService::HandleSubscibedMessage, this, std::placeholders::_1, 
                        std::placeholders::_2));
    }
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
    int id = js[userfield::id];
    std::string password = js[userfield::password];
    User user = user_model_.Query(id);

    json response;
    response[msgfield::msgid] = kLoginAckMsg;
    // 账户密码均正确
    if (user.GetId() == id && user.GetPassword() == password) {
        // 用户已经登录，无需重新登陆
        if (user.GetState() == userfield::online) {
            response[msgfield::errorno] = 2;
            response[msgfield::errormsg] = "The user has already logged in!";
        }
        else {  
            // 登录成功，保存连接
            {
                std::lock_guard<std::mutex> lock(conn_mutex_);
                conn_map_.insert({id, conn});
            }
            user.SetState(userfield::online);
            user_model_.UpdateState(user);
            response[msgfield::errorno] = 0;
            response[msgfield::id] = id;

            // 以id为通道号订阅通道
            redis_.Subscribe(id);
            
            // 查看是否有离线消息，如果有就返回
            std::vector<std::string> offlinemsg_vec = offlinemsg_model_.Query(id);
            if (!offlinemsg_vec.empty()) {
                response[msgfield::msg] = offlinemsg_vec;
                offlinemsg_model_.Erase(id);
            }

            // 返回好友列表
            std::vector<User> user_vec = friend_model_.Query(id);
            std::vector<std::string> friends;
            for (const User& user : user_vec) {
                json temp;
                temp[userfield::id] = user.GetId();
                temp[userfield::name] = user.GetName();
                temp[userfield::state] = user.GetState();
                friends.push_back(temp.dump());
            }
            response[msgfield::friendlist] = friends;
        }
    }
    else {
        response[msgfield::errorno] = 1;
        response[msgfield::errormsg] = "Incorrect account or password!";
    }
    conn->send(response.dump());
}

void ChatService::Register(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    std::string name = js[userfield::name];
    std::string password = js[userfield::password];
    User user;
    user.SetName(name);
    user.SetPassword(password);
    bool insert_state = user_model_.Insert(user);
    // 填写json响应
    json response;
    response[msgfield::id] = kRedisterAckMsg;
    if (insert_state) {
        response[msgfield::id] = user.GetId();
        response[msgfield::errorno] = 0;
    }
    else {
        response[msgfield::errorno] = 1;
        response[msgfield::errormsg] = "Failed to insert into user!";
    }
    conn->send(response.dump());
}

// 用户在线时直接转化消息，用户离线时将消息存入离线消息表中
void ChatService::OneToOneChat(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int toid = js[msgfield::toid];
    {   
        std::lock_guard<std::mutex> lock(conn_mutex_);
        auto it = conn_map_.find(toid);
        if (it != conn_map_.end()) {
            it->second->send(js.dump());
            return;
        }
    }
    // 如果用户在其他机器登录，那么发布消息到通道中
    User user = user_model_.Query(toid);
    if (user.GetState() == userfield::online) {
        redis_.Publish(toid, js.dump());
    }
    else {  
        // 用户处于离线状态
        offlinemsg_model_.Insert(toid, js.dump());
    }
}

void ChatService::AddFriend(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int userid = js[friendfield::userid];
    int friendid = js[friendfield::friendid];
    friend_model_.Insert(userid, friendid);
}

void ChatService::CreateGroup(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int userid = js[userfield::id];
    std::string groupname = js[allgroupfield::groupname];
    std::string groupdesc = js[allgroupfield::groupdesc];
    // 创建群后，将该用户设置为群创建者角色
    Group group(-1, groupname, groupdesc);
    if (group_model_.CreateGroup(group)) {
        group_model_.AddGroup(userid, group.GetId(), groupuserfield::creator);
    }
}

void ChatService::AddGroup(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int userid = js[userfield::id];
    int groupid = js[groupuserfield::groupid];
    group_model_.AddGroup(userid, groupid, groupuserfield::normal);
}

void ChatService::ChatGroup(const muduo::net::TcpConnectionPtr& conn, json& js, muduo::Timestamp time) {
    int userid = js[userfield::id];
    int groupid = js[groupuserfield::groupid];
    std::vector<int> userid_vec = group_model_.QueryGroupUsers(userid, groupid);
    std::lock_guard<std::mutex> lock(conn_mutex_);
    for (int id : userid_vec) {
        // 用户在线则直接转发，用户离线则将消息存储到离线消息表中
        auto it = conn_map_.find(id);
        User user = user_model_.Query(id);
        if (it != conn_map_.end()) {
            conn->send(js.dump());
        }
        else if (user.GetState() == userfield::online) {
            // 用户在其他机器登录，那么发布消息到通道中
            redis_.Publish(id, js.dump());
        }
        else {
            // 用户离线
            offlinemsg_model_.Insert(id, js.dump());
        }
    }
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
        // 用户已经下线，取消订阅该通道
        redis_.Unsubscribe(user.GetId());
        // 设置用户离线
        user.SetState(userfield::offline);
        user_model_.UpdateState(user);
    }
}

void ChatService::Reset() {
    user_model_.ResetState();
}

// 有可能出出现通知消息时用户下线了，对于这种情况仍然需要存储消息到离线消息表
void ChatService::HandleSubscibedMessage(int id, std::string msg) {
    std::lock_guard<std::mutex> lock(conn_mutex_);
    {
        auto it = conn_map_.find(id);
        if (it != conn_map_.end()) {
            it->second->send(msg);
            return;
        }
    }
    offlinemsg_model_.Insert(id, msg);
}