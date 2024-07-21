#ifndef FRIEND_MODEL_H
#define FRIEND_MODEL_H

#include "usermodel.h"
#include <vector>
#include <string>

// friend表字段
const std::string kFriUserId = "userid";
const std::string kFriendId = "friendid";

class FriendModel {
public:
    // 将好友关系插入好友表
    bool Insert(int userid, int friendid);

    // 查询好友列表
    std::vector<User> Query (int userid) const;
};

#endif