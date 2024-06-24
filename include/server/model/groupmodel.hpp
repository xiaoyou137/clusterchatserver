#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

const string CREATOR = "creator";
const string NORMAL = "normal";

class GroupModel 
{
public:
    // 创建群组
    bool createGroup(Group& group);
    // 添加群组
    void addGroup(int userid, int groupid, string role);
    // 返回用户所在群组列表
    vector<Group> queryGroups(int userid);
    // 返回该群组所有用户id（除了当前用户之外）
    vector<int> queryGroupUsers(int userid, int groupid);

};

#endif
