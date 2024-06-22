#include "usermodel.hpp"
#include "db.hpp"
#include <iostream>

constexpr int SQL_LENTH = 1024;

bool UserModel::insert(User& user)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into User(name, passwd, state) values('%s', '%s', '%s')",
            user.getName().c_str(), user.getPasswd().c_str(), user.getState().c_str());

    // 使用MySQL对象，执行sql语句
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            //插入成功，获取主键id作为User id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }

    }
    
    return false;
}