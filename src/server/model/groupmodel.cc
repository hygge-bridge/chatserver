#include "groupmodel.h"

#include "db.h"
#include <string.h>
#include <memory>
#include <functional>

bool GroupModel::CreateGroup(Group& group) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "insert into allgroup(id, groupname, groupdesc) values(%d, '%s', '%s')",
                 group.GetId(), group.GetName().c_str(), group.GetDesc().c_str());
    MySql mysql;
    if (mysql.Connect() && mysql.Update(sql)) {
        group.SetId(mysql_insert_id(mysql.GetConnection()));
        return true;
    }
    return false;
}

bool GroupModel::AddGroup(int userid, int groupid, const std::string& role) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "insert into groupuser(groupid, userid, grouprole) values(%d, %d, %s)", groupid, userid, role.c_str());
    MySql mysql;
    return mysql.Connect() && mysql.Update(sql);
}

std::vector<Group> GroupModel::QueryGroup(int userid) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "select a.id, a.groupname, a.groupdesc from allgroup a inner join groupuser g on g.groupid=a.id where g.userid=%d", userid);
    std::vector<Group> group_vec;
    MySql mysql;
    if (mysql.Connect()) {
        std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res_ptr(
            mysql.Query(sql),
            [](MYSQL_RES* res) { mysql_free_result(res); }
        );
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res_ptr.get())) != nullptr) {
            group_vec.emplace_back(atoi(row[0]), std::string(row[1]), std::string(row[2]));
        }
    }
    for (Group& group : group_vec) {
        sprintf(sql, "select u.id, u.name, u.state, g.grouprole from user u inner join groupuser g on u.id=g.userid where g.groupid=%d", group.GetId());
        std::vector<GroupUser> groupuser_vec;
        MySql mysql;
        if (mysql.Connect()) {
            std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res_ptr(
                mysql.Query(sql),
                [](MYSQL_RES* res) { mysql_free_result(res); }
            );
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res_ptr.get())) != nullptr) {
                groupuser_vec.emplace_back(atoi(row[0]), std::string(row[1]), std::string(row[2]), std::string(row[3]));
            }
        }
        group.AddGroupUser(groupuser_vec);
    }
    return group_vec;
}

std::vector<int> GroupModel::QueryGroupUsers(int userid, int groupid) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "select userid from groupuser where groupid=%d and userid!=%d", groupid, userid);
    std::vector<int> guserid_vec;
    MySql mysql;
    if (mysql.Connect()) {
        std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res_ptr(
            mysql.Query(sql),
            [](MYSQL_RES* res) { mysql_free_result(res); }
        );
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res_ptr.get())) != nullptr) {
            guserid_vec.emplace_back(atoi(row[0]));
        }
    }
    return guserid_vec;
}