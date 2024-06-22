#include "json.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>

using json = nlohmann::json;
using namespace std;


string demo1()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "zhang san";
    js["Message"]["zhang san"] = "hello world!";
    js["Message"]["li si"] = "hello China!";

    return js.dump();
}

string demo2()
{
    vector<int> vec{1,2,3,4,5,6,7};
    json jvec = vec;
    cout << jvec << endl;

    map<int, string> m{{1,"黄山"}, {2,"华山"}, {3,"泰山"}};
    json jm = m;
    
    return jm.dump();
}

int main()
{
    json js1 = json::parse(demo1());
    cout << js1 << endl;

    json js2 = json::parse(demo2());
    map<int,string> m = js2;
    for(auto& v : m)
    {
        cout << v.first << ":" << v.second << endl;
    }
    
    return 0;
}
