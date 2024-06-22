#include "db.hpp"
#include <muduo/base/Logging.h>

using namespace muduo;

// 初始化数据库连接
MySql::MySql()
{
    _conn = mysql_init(nullptr);
}

// 释放连接资源
MySql::~MySql()
{
    if(_conn != nullptr)
    {
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySql::connect()
{
    MYSQL* p = mysql_real_connect(_conn, server.c_str(), user.c_str(), passwd.c_str(), db.c_str(), 3306, nullptr, 0);
    if(p != nullptr)
    {
        // C++默认字符编码是ASCII，如果不修改则中文乱码
        mysql_query(_conn, "set name gbk");
    }
    return p;
}

// 更新数据库
bool MySql::update(std::string sql)
{
    if(mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败！";
        return false;
    }   
    return true;
}

// 查询数据库
MYSQL_RES* MySql::query(std::string sql)
{
    if(mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败！";
        return nullptr;
    }

    return mysql_use_result(_conn);
}