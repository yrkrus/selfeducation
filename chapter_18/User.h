#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>

using std::string;
using std::ostream;
using std::fstream;

class User
{
private:
    string _name;
    string _login;
    string _pass;

public:
    User();
    User(string name, string login, string pass);
    ~User();

    friend ostream &operator<< (ostream &out, const User &user);
    friend fstream &operator>> (fstream &in, User &user);

    void saveFile(std::string file) const;
    void loadFile(std::string file, User &user);


};

#endif // !USER_H

