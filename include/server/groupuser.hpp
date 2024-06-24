#ifndef GROUPUSER_H
#define GROUPUSER_H

#include <string>
#include "user.hpp"

using std::string;

class GroupUser : public User
{
public:
    GroupUser(int id, string name, string state, string role)
    : User(id, name, state), grouprole(role) 
    {

    }
    void setRole(string role) { this->grouprole = role; }
    string getRole() { return this->grouprole; }
private:
    string grouprole;
};

#endif
