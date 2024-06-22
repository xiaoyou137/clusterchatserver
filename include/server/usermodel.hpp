#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

// User表的操作类，用于解耦数据层和业务层
class UserModel
{
public:
    bool insert(User& user);
};

#endif