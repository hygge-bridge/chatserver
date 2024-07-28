#ifndef FRIEND_MODEL_H
#define FRIEND_MODEL_H

#include "usermodel.h"
#include <vector>
#include <string>
#include <unordered_map>

// friend表字段
namespace friendfield {
    const std::string userid = "userid";
    const std::string friendid = "friendid";
}

class FriendModel {
public:
    // 将好友关系插入好友表
    bool Insert(int userid, int friendid);

    // 查询好友列表
    std::vector<User> Query (int userid) const;
};

#endif