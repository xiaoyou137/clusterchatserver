#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include "groupuser.hpp"
#include "json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;

class Group
{
public:
    Group(int id = -1, string name = "", string desc = "")
    {
        this->id = id;
        this->name = name;
        this->desc = desc;
    }

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setDesc(string desc) { this->desc = desc; }

    int getId() { return id; }
    string getName() { return name; }
    string getDesc() { return desc; }
    vector<GroupUser> &getUsers() { return users; }

    json toJson() const
    {
        string res;
        json js;
        js["id"] = id;
        js["groupname"] = name;
        js["groupdesc"] = desc;
        json jsuser;
        for(auto& user : users)
        {
                jsuser["id"] = user.getId();        
                jsuser["name"] = user.getName();        
                jsuser["state"] = user.getState();        
                jsuser["role"] = user.getRole();
                js["users"].push_back(jsuser.dump());        
        }
        return js;
    }

private:
    int id;
    string name;
    string desc;
    vector<GroupUser> users;
};

#endif
