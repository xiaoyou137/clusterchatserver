#include "groupmodel.hpp"
#include "db.hpp"

// 创建群组
bool GroupModel::createGroup(Group& group)
{
    //1.组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into allgroup(groupname, groupdesc) values('%s', '%s')", group.getName().c_str(), group.getDesc().c_str());

    // 更新数据库
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            // 获取并设置group的主键id
            group.setId(mysql_insert_id(mysql.getConnection()));

            return true;
        }
    }

    return false;
}

// 添加群组
void GroupModel::addGroup(int userid, int groupid, string role)
{
    // 1.组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into groupuser(groupid, userid, grouprole) values('%d', '%d', '%s')", groupid, userid, role.c_str());

    // 更新数据库
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }    
}

// 返回用户所在群组列表
vector<Group> GroupModel::queryGroups(int userid)
{
    // 1.组装sql语句, 查询用户所在群组
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "select a.id, a.groupname, a.groupdesc from allgroup a inner join groupuser b on a.id = b.groupid where b.userid = %d",
    userid);

    vector<Group> vec;
    // 查询数据库
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {

                vec.emplace_back(atoi(row[0]), row[1], row[2]);
            }
            // 释放mysql资源
            mysql_free_result(res);
        }
    }

    // 查询群组用户信息
    for(Group& group : vec)
    {
        sprintf(sql, "select a.id, a.name, a.state, b.grouprole from user a inner join \
        groupuser b on a.id = b.userid where b.groupid = %d", group.getId());

        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                group.getUsers().emplace_back(atoi(row[0]), row[1], row[2], row[3]);
            }
            mysql_free_result(res);
        }
    }

    return vec;
}

// 返回该群组所有用户id（除了当前用户之外）
vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
{
    // 1.组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "select a.userid from groupuser where goupid = %d and userid != %d",groupid, userid);

    vector<int> vec;
    // 查询数据库
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {

                vec.push_back(atoi(row[0]));
            }
            // 释放mysql资源
            mysql_free_result(res);
        }
    }

    return vec;
}