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
    kAddFriendMsg = 6,    // 添加好友消息
};


// 消息内容字段
const std::string kMsgId = "msgid";             // 消息类型id，对应MsgType
const std::string kMsgErrNo = "errno";          // 错误号, 只有0表示成功
const std::string kMsgErr = "errmsg";           // 错误内容
const std::string kMsgUserId = "id";                // 主键id
const std::string kMsgToId = "toid";            // 对方的id
const std::string kMsg = "msg";                 // 消息内容
const std::string kMsgFriId = "friendid";       // 将要添加为好友的好友id
const std::string kMsgFriendList = "friend";    // 好友列表
#endif