#ifndef GROUP_MODEL_H
#define GROUP_MODEL_H

#include "group.h"

// allgroup表相关字段
namespace allgroupfield{
    const std::string id = "id";
    const std::string groupname = "groupname";
    const std::string groupdesc = "groupdesc";
}
// groupuser表相关字段
namespace groupuserfield {
    const std::string groupid = "groupid";
    const std::string userid = "userid";
    const std::string grouprole = "grouprole";
    const std::string creator = "creator"; // 群创建者
    const std::string normal = "normal";  // 普通用户
}


// 组的数据操作类，包含allgroup和groupuser两张表的数据
class GroupModel {
public:
    // 创建群组
    bool CreateGroup(Group& group);

    // 添加到群组
    bool AddGroup(int userid, int groupid, const std::string& role);

    // 查询用户所在的群组信息
    std::vector<Group> QueryGroup(int userid);

    // 查询群组内除本用户之外的其他用户id
    std::vector<int> QueryGroupUsers(int userid, int groupid);
};

#endif