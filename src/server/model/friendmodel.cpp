#include "friendmodel.hpp"
#include "json.hpp"

using json = nlohmann::json;

// 添加好友
void FriendModel::insert(int userid, int friendid)
{
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "insert into friend(userid, friendid) values('%d', '%d')", userid, friendid);

    // 使用MySQL对象，执行sql语句
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }

    return;
}

// 返回好友列表
std::vector<std::string> FriendModel::query(int userid)
{
    std::vector<std::string> vec;
    // 1. 组装sql语句
    char sql[SQL_LENTH] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid = %d", userid);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                json js;
                js["id"] = atoi(row[0]);
                js["name"] = row[1];
                js["state"] = row[2];
                vec.push_back(js.dump());
            }
            mysql_free_result(res);
        }
    }
    return vec;
}