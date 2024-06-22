#ifndef DB_H
#define DB_H

#include <string>
#include <mysql/mysql.h>

// 连接数据库用到的参数字符串
static std::string server = "127.0.0.1";
static std::string db = "chat";
static std::string user = "root";
static std::string passwd = "123456";


// 数据库类，封装了数据库操作
class MySQL
{
public:
    // 初始化数据库连接
    MySQL();
    // 释放连接资源
    ~MySQL();
    // 连接数据库
    bool connect();
    // 更新数据库
    bool update(std::string sql);
    // 查询数据库
    MYSQL_RES* query(std::string sql);
    // 获取数据库连接
    MYSQL* getConnection();
private:
    MYSQL* _conn;
};

#endif