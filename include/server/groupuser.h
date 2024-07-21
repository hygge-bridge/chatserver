#ifndef GROUP_USER_H
#define GROUP_USER_H

#include "user.h"
#include <string>

// 组内的成员描述的orm类，继承自User
class GroupUser : public User {
public:
    GroupUser(int id = -1, const std::string& name = "",
            const std::string& state = "offline", const std::string& role = "normal")
        : User(id, name, "", state)
        , role_(role) {}

    void SetRole(const std::string& role) { role_ = role; }
    std::string GetRole() const { return role_; }

private:
    std::string role_;
};

#endif