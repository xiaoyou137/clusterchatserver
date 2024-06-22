#ifndef USER_H
#define USER_H

#include <string>

// User表对应的ORM映射类，用于将数据层与业务层解耦
class User
{
public:
    User(int id = -1, std::string name = "", std::string passwd = "", std::string state = "offline")
        : id_(id), name_(name), passwd_(passwd), state_(state)
    {
    }

    void setId(int id)
    {
        id_ = id;
    }

    void setName(std::string name)
    {
        name_ = name;
    }

    void setPasswd(std::string passwd)
    {
        passwd_ = passwd;
    }

    void setState(std::string state)
    {
        state_= state;
    }

    int getId()
    {
        return id_;
    }

    std::string getName()
    {
        return name_;
    }

    std::string getPasswd()
    {
        return passwd_;
    }

    std::string getState()
    {
        return state_;
    }

private:
    int id_; // 用户id， 由插入数据库时，作为主键自动分配
    std::string name_;
    std::string passwd_;
    std::string state_;
};

#endif