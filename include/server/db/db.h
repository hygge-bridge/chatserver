#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>
#include <string>

// sql缓冲区的最大尺寸
static const int kSqlBufSize = 1024;

// 数据库配置信息
static const std::string server = "127.0.0.1";
static const std::string user = "root";
static const std::string password = "letusmove8";
static const std::string dbname = "chat";

// 数据库操作类
class MySql
{
public:
    // 初始化数据库连接
    MySql();

    // 释放数据库连接资源
    ~MySql();

    // 连接数据库
    bool Connect();

    // 更新操作
    bool Update(const std::string& sql);

    // 查询操作
    MYSQL_RES* Query(const std::string& sql);

    // 获取连接
    MYSQL* GetConnection() { return conn_; }

private:
    MYSQL* conn_;  // mysql连接
};

#endif