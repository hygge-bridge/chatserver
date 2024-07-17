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
    std::cout << "do login()" << std::endl;
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