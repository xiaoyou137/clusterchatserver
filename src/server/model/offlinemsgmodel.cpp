#include "offlinemsgmodel.hpp"

void OfflineMsgModel::insert(int userid, std::string msg)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into offlinemessage(userid, message) values('%d', '%s')", userid, msg.c_str());

    // 使用MySQL对象，执行sql语句
    auto mysql = ConnectionPool::getInstance()->getConnection();
    if (mysql != nullptr)
    {
        mysql->update(sql);
    }

    return;
}

void OfflineMsgModel::remove(int userid)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "delete from offlinemessage where userid = %d", userid);

    // 使用MySQL对象，执行sql语句
    auto mysql = ConnectionPool::getInstance()->getConnection();
    if (mysql != nullptr)
    {
        mysql->update(sql);
    }

    return;
}

std::vector<std::string> OfflineMsgModel::query(int userid)
{
    std::vector<std::string> vec;
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);

    auto mysql = ConnectionPool::getInstance()->getConnection();
    if(mysql != nullptr)
    {
        MYSQL_RES* res = mysql->query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
        }
    }

    return vec;
}