#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "user.h"
#include <string>

// user表的字段
const std::string kUserId = "id";
const std::string kUserName = "name";
const std::string kUserPwd = "password";
const std::string kUserState = "state";  // 取值只有online和offline
const std::string kUserOnline = "online";
const std::string kUserOffline = "offline";


// user表的数据操作类
class UserModel {
public:
    // 插入数据
    bool Insert(User& user);

    // 查询数据
    User Query(int id);

    // 更新状态
    bool UpdateState(const User& user);

    // 重置所有用户的状态
    bool ResetState();
};


#endif