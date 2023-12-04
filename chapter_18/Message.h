#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <fstream>

using std::string;
using std::ostream;
using std::fstream;

class Message
{
private:
    string _text;
    string _sender;
    string _receiver;

public:
    Message();
    Message(string test, string sender, string receiver);
    ~Message();

    friend ostream &operator<< (ostream &out, const Message &message);
    friend fstream &operator>> (fstream &in, Message &message);

    void saveFile(std::string file) const;
    void loadFile(std::string file, Message &message);


};


#endif // !MESSAGE_H

