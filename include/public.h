#ifndef PUBLIC_H
#define PUBLIC_H

#include <string>

// 消息类型
enum MsgType {
    kLoginMsg = 1,   // 登录消息
    kLoginAckMsg,    // 登录响应消息
    kRegisterMsg,    // 注册消息
    kRedisterAckMsg  // 注册响应消息
};


// 消息内容字段
const std::string kMsgId = "msgid";  // 消息类型id，对应MsgType
const std::string kErrNo = "errno";  // 错误号, 0表示成功，1表示错误
const std::string kErrMsg = "errmsg"; // 错误内容
const std::string kId = "id";  // 主键id
#endif