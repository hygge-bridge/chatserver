#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "user.h"

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