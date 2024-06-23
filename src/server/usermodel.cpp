#include "usermodel.hpp"
#include "db.hpp"
#include <iostream>


bool UserModel::insert(User &user)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')",
            user.getName().c_str(), user.getPasswd().c_str(), user.getState().c_str());

    // 使用MySQL对象，执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 插入成功，获取主键id作为User id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }

    return false;
}

// 用id查询用户信息
User UserModel::query(int id)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    // 使用MySQL对象，执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPasswd(row[2]);
                user.setState(row[3]);

                mysql_free_result(res);
                return user;
            }
        }
    }

    return User();
}

// 更新用户状态
bool UserModel::updatestate(User user)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d",user.getState().c_str(), user.getId());

    // 使用MySQL对象，执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 更新成功
            return true;
        }
    }

    return false;
}