#include "usermodel.h"
#include "db.h"

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