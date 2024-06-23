#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

// User表的操作类，用于解耦数据层和业务层
class UserModel
{
public:
    bool insert(User& user);
    // 用id查询用户信息
    User query(int id);
    // 更新用户状态
    bool updatestate(User user);
};

#endif