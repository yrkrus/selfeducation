#include "Message.h"
#include <iostream>
#include <string>
#include <filesystem>

using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

//namespace fs = std::filesystem;

// default
Message::Message()
{
	string text, sender, receiver;

	cout << "�����:\n > ";
	cin >> text;
	_text = text;

	cout << "�����������:\n > ";
	cin >> sender;
	_sender = sender;

	cout << "����������:\n > ";
	cin >> receiver;
	_receiver = receiver;

	system("cls");
}

Message::Message(string text, string sender, string receiver)
	: _text(text), _sender(sender), _receiver(receiver)
{

}

Message::~Message()
{
}

// ���������� �����
void Message::saveFile(std::string file) const
{
	// ������� ����
	ofstream filesafe(file);

	if (!filesafe.is_open())
	{
		cout << "������, �� ������� ������� ���� " << file;
		return;
	}

	filesafe << Message::_text << "\n";
	filesafe << Message::_sender << "\n";
	filesafe << Message::_receiver << "\n";

	filesafe.close();
}


void Message::loadFile(std::string file, Message &message)
{

	string text, sender, receiver;

	ifstream fileload(file);

	if (fileload.is_open())
	{
		while (fileload >> text >> sender >> receiver)
		{
			message._text = text;
			message._sender = sender;
			message._receiver = receiver;
		};

		fileload.close();
	}
	else
	{
		cout << "������, �� ������� ������� ���� " << file;
		return;
	}
}

ostream &operator<<(ostream &out, const Message &message)
{
	out << message._text << "\n";
	out << message._sender << "\n";
	out << message._receiver << "\n";

	return out;
}


fstream &operator>>(fstream &in, Message &message)
{
	in >> message._text;
	in >> message._sender;
	in >> message._receiver;

	return in;
}
