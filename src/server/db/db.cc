#include "db.h"
#include <muduo/base/Logging.h>

MySql::MySql() {
    conn_ = mysql_init(nullptr);
}

MySql::~MySql() {
    if (conn_ != nullptr) {
        mysql_close(conn_);
    }
}

bool MySql::Connect() {
    MYSQL* p = mysql_real_connect(conn_, server.c_str(), user.c_str(),
                                password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr) {
        // 设置编码格式
        mysql_query(conn_, "set names gbk");
    }
    return p != nullptr;
}

bool MySql::Update(const std::string& sql) {
    if (mysql_query(conn_, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                << sql << "更新失败!";
        return false;
    }
    return true;
}

MYSQL_RES* MySql::Query(const std::string& sql) {
    if (mysql_query(conn_, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(conn_);
}
