#include <iostream>
#include "Message.h"
#include "User.h"
#include <ostream>
#include <iostream>
#include <string>
#include <filesystem>


/*
Напишите программу, которая сможет считывать из файла при своей загрузке
и записывать в файл состояния объектов классов User и Message (для каждого класса свой файл)

class User {
    string _name;
    string _login;
    string _pass;
};

class Message {
    string _text;
    string _sender;
    string _receiver;
};

*/

using std::cout;
using std::string;
using std::cin;
using std::ifstream;
using std::ofstream;

namespace fs = std::filesystem;


const string FILEUSERSNAME = "users.txt";
const string FILEMESSAGE = "message.txt";

enum TypeProgram 
{
    UserType,
    MessageType
};

TypeProgram setchoise()
{
    int choise{ 0 };

    do
    {
        system("cls");

        cout << "Варианты выбора: \n";
        cout << " 1. User\n";
        cout << " 2. Message\n";

        cin >> choise;

        if (choise == 1)
        {
            return UserType;
        }
        else if (choise == 2) {
            return MessageType;                 
        }
    } while (choise != 1 || choise != 2);   
   
}

int main()
{
	setlocale(LC_ALL, "");  
    
    TypeProgram choise;
    choise = setchoise();
    system("cls");

    switch (choise)
    {
    case UserType:
        {

            // проверяем файл
            if (!fs::exists(FILEUSERSNAME))
            {

                // файла нет, создаем и записываем
                User user;
                user.saveFile(FILEUSERSNAME);
                cout << "данные записаны!";
            }
            else
            {
                // проверяем размер 
                if (fs::file_size(FILEUSERSNAME) == 0)
                {

                    // записываем данные
                    User user;
                    user.saveFile(FILEUSERSNAME);
                    cout << "данные записаны!";
                }
                else
                {
                    cout << "загружаем данные \n";
                    User user("", "", "");
                    user.loadFile(FILEUSERSNAME, user);

                    cout << user;
                }
            }
        
        break;
         };
        
    case MessageType: 
        {
        // проверяем файл
        if (!fs::exists(FILEMESSAGE))
        {

            // файла нет, создаем и записываем
            Message message;
            message.saveFile(FILEMESSAGE);
            cout << "данные записаны!";
        }
        else
        {
            // проверяем размер 
            if (fs::file_size(FILEMESSAGE) == 0)
            {

                // записываем данные
                Message message;
                message.saveFile(FILEMESSAGE);
                cout << "данные записаны!";
            }
            else
            {
                cout << "загружаем данные \n";
                Message message("", "", "");
                message.loadFile(FILEMESSAGE, message);

                cout << message;
            }
        }
        break;
        }
        
    }        
    


	return 0;
}

