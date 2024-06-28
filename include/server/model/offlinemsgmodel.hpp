#ifndef OFFLINEMSGMODEL_H
#define OFFLINEMSGMODEL_H

#include "connectionpool.hpp"
#include <vector>


// 处理离线消息
class OfflineMsgModel
{
public:
    void insert(int userid, std::string msg);

    void remove(int userid);

    std::vector<std::string> query(int userid);
};

#endif