#include "offlinemsgmodel.h"
#include "db.h"
#include <memory>
#include <functional>

bool OfflineMsgModel::Insert(int id, const std::string& msg) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "insert into offlinemessage(userid, message) values(%d, '%s')", id, msg.c_str());
    MySql mysql;
    if (mysql.Connect() && mysql.Update(sql)) {
        return true;
    }
    return false;
}

bool OfflineMsgModel::Erase(int id) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "delete from offlinemessage where userid = %d", id);
    MySql mysql;
    if (mysql.Connect() && mysql.Update(sql)) {
        return true;
    }
    return false;
}

std::vector<std::string> OfflineMsgModel::Query(int id) {
    char sql[kSqlBufSize] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", id);
    std::vector<std::string> msg_vec;
    MySql mysql;
    if (mysql.Connect()) {
        std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> res(
            mysql.Query(sql),
            [](MYSQL_RES* p) { mysql_free_result(p); }
        );
        if (res) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res.get())) != nullptr) {
                msg_vec.push_back(row[0]);
            }
        }
    }
    return msg_vec;
}