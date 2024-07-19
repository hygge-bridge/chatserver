#ifndef PUBLIC_H
#define PUBLIC_H

#include <string>

// 消息类型
enum MsgType {
    kLoginMsg = 1,        // 登录消息
    kLoginAckMsg = 2,     // 登录响应消息
    kRegisterMsg = 3,     // 注册消息
    kRedisterAckMsg = 4,  // 注册响应消息
    kOneToOneChatMsg = 5, // 一对一聊天消息
};


// 消息内容字段
const std::string kMsgId = "msgid";  // 消息类型id，对应MsgType
const std::string kErrNo = "errno";  // 错误号, 只有0表示成功
const std::string kErrMsg = "errmsg"; // 错误内容
const std::string kId = "id";  // 主键id
const std::string kToId = "toid";  // 对方的id
const std::string kMsg = "msg";  // 消息内容
#endif