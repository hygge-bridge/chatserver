#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "user.h"
#include <string>

// user表的字段
namespace userfield {
    const std::string id = "id";
    const std::string name = "name";
    const std::string password = "password";
    const std::string state = "state";  // 取值只有online和offline
    const std::string online = "online";
    const std::string offline = "offline";
}


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