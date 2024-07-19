#include "usermodel.h"
#include "db.h"
#include <memory>
#include <functional>
#include <iostream>

static const int kSqlBufSize = 1024;

bool UserModel::Insert(User& user) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')", 
        user.GetName().c_str(), user.GetPassword().c_str(), user.GetState().c_str());
    MySql mysql;
    if (mysql.Connect()) {
        if (mysql.Update(sql)) {
            // 回填主键id
            user.SetId(mysql_insert_id(mysql.GetConnection()));
            return true;
        }
    }
    return false;
}

User UserModel::Query(int id) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "select id, name, password, state from user where id = %d", id);
    MySql mysql;
    if (mysql.Connect()) {
        //MYSQL_RES* res = mysql.Query(sql);
        std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res_ptr(
            mysql.Query(sql),
            [](MYSQL_RES* res) { mysql_free_result(res); }
        );
        if (res_ptr) {
            MYSQL_ROW row = mysql_fetch_row(res_ptr.get());
            if (row) {
                // 对象的优化，避免额外的拷贝
                return User(atoi(row[0]), std::string(row[1]), 
                            std::string(row[2]), std::string(row[3]));
            }
        }
    }
    // 没有查询到数据
    return User();
}

bool UserModel::UpdateState(const User& user) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d", user.GetState().c_str(), user.GetId());
    MySql mysql;
    if (mysql.Connect() && mysql.Update(sql)) {
        return true;
    }
    return false;
}