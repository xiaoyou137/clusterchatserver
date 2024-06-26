#ifndef GROUPUSER_H
#define GROUPUSER_H

#include <string>
#include "user.hpp"

using std::string;

class GroupUser : public User
{
public:
    GroupUser(int id = -1, string name = "", string state = "", string role = "normal")
    : User(id, name, state), grouprole(role) 
    {

    }
    void setRole(string role) { this->grouprole = role; }
    string getRole() const { return this->grouprole; }
private:
    string grouprole;
};

#endif
