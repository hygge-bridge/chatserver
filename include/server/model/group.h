#ifndef GROUP_H
#define GROUP_H

#include "groupuser.h"
#include <string>
#include <vector>

// allgroup的orm类
class Group {
public:
    // 组内默认情况下没有用户，用户可以自行通过AddGroupUser函数进行添加
    Group(int id, const std::string& name, const std::string& desc, const std::vector<GroupUser>& users = {})
        : id_(id)
        , name_(name)
        , desc_(desc) 
        , users_(users) {}

    void SetId(int id) { id_ = id; }
    void SetName(const std::string& name) { name_ = name; }
    void SetDesc(const std::string& desc) { desc_ = desc; }
    // 添加组内成员
    void AddGroupUser(const std::vector<GroupUser>& users) { users_ = users; }

    int GetId() const { return id_; }
    std::string GetName() const { return name_; }
    std::string GetDesc() const { return desc_; }
    const std::vector<GroupUser>& GetGroupUsers() const { return users_; }
private:
    int id_;
    std::string name_;  // 组名
    std::string desc_;  // 组描述
    std::vector<GroupUser> users_;  // 组内用户成员
};

#endif