#include "User.h"
#include <iostream>
#include <string>
#include <filesystem>

using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

//namespace fs = std::filesystem;

// default
User::User()
{
	string name, login, pass;

	cout << "ИМЯ:\n > ";
	cin >> name;
	_name = name;

	cout << "ЛОГИН:\n > ";
	cin >> login;
	_login = login;

	cout << "ПАРОЛЬ:\n > ";
	cin >> pass;
	_pass = pass;	

	system("cls");
}

User::User(string name, string login, string pass)
	: _name(name),_login(login),_pass(pass){
	
}

User::~User()
{
}

// сохранение файла
void User::saveFile(std::string file) const
{
	// создаем файл
	ofstream filesafe(file);

	if (!filesafe.is_open()) {
		cout << "Ошибка, не удается открыть файл " << file;
		return;
	}

	filesafe << User::_name<< "\n";
	filesafe << User::_login << "\n";
	filesafe << User::_pass << "\n";

	filesafe.close();
}


void User::loadFile(std::string file, User &user)
{
	
	string name, login, pwd;
	
	ifstream fileload(file);

	if (fileload.is_open())
	{
		while (fileload >> name >> login >> pwd)
		{
			user._name = name;
			user._login = login;
			user._pass = pwd;
		};

		fileload.close();
	}
	else
	{
		cout << "Ошибка, не удается открыть файл " << file;
		return;
	}		
}

ostream &operator<<(ostream &out, const User &user)
{
	out << user._name << "\n";
	out << user._login << "\n";
	out << user._pass << "\n";

	return out;
}


fstream &operator>>(fstream &in, User &user)
{
	in >> user._name;
	in >> user._login;
	in >> user._pass;

	return in;
}
