#include "friendmodel.h"
#include "db.h"
#include <memory>
#include <functional>

bool FriendModel::Insert(int userid, int friendid) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "insert into friend(userid, friendid) values(%d, %d)", userid, friendid);
    MySql mysql;
    if (mysql.Connect() && mysql.Update(sql)) {
        return true;
    }
    return false;
}


std::vector<User> FriendModel::Query (int userid) const {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "select u.id, u.name, u.state from user u inner join friend f on f.friendid = u.id where f.userid = %d", userid);
    std::vector<User> user_vec;
    MySql mysql;
    if (mysql.Connect()) {
        std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res_ptr(
            mysql.Query(sql),
            [](MYSQL_RES* res) { mysql_free_result(res); }
        );
        if (res_ptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res_ptr.get())) != nullptr) {
                user_vec.emplace_back(atoi(row[0]), row[1], "", row[2]);
            }
        }
    }
    return user_vec;
}