#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include "db.hpp"
#include "user.hpp"
#include <vector>
#include <string>


// friend表的操作类
class FriendModel 
{
public:
    // 添加好友
    void insert(int userid, int friendid);

    // 返回好友列表
    std::vector<std::string> query(int userid);
};


#endif