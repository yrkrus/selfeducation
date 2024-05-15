#include "Queue.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include "InternalFunction.h"
#include "SQLRequest.h"


// ����������
QUEUE::Parsing::Parsing(const char *fileQueue)
{
	std::ifstream filequeue;

	filequeue.open(fileQueue);

	if (filequeue.is_open())
	{
		//std::cout << "open file... OK\n";

		std::string line;

		// ��������
		while (std::getline(filequeue, line))
		{
			Pacients pacient;

			pacient.phone	= findParsing(line, QUEUE::Currentfind::phone_find);
			pacient.waiting = findParsing(line, QUEUE::Currentfind::waiting_find);
			pacient.queue	= findParsing(line, QUEUE::Currentfind::queue_find);

			// ���������
			if (pacient.phone	!= "null" && 
				pacient.waiting != "null" && 
				pacient.queue	!= "null")
			{
				pacient_list.push_back(pacient);
			}
		}
	}

	filequeue.close();
	
}

// ����������
QUEUE::Parsing::~Parsing()
{
	if (!pacient_list.empty())
	{
		pacient_list.clear();
	}
}

// �������� ������ �� ������ � ��������
bool QUEUE::Parsing::isExistList()
{
	return (pacient_list.empty() ? false : true);
}


void QUEUE::Parsing::show()
{
	if (isExistList())
	{
		std::cout << "Line QUEUE is (" << pacient_list.size() << ")\n\n";

		for (std::vector<QUEUE::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it) {
			std::cout << it->queue << " | " << it->phone << " >> " << it->waiting << "\n";
		}		
	}
	else
	{
		std::cout << "QUEUE is empty!\n";
	}
}


//���������� ������ � ��
void QUEUE::Parsing::insertData() 
{
	if (this->isExistList())
	{
		SQL_REQUEST::SQL base;

		for (std::vector<QUEUE::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it)
		{
			if (base.isConnectedBD())
			{
				base.insertQUEUE(it->queue.c_str(), it->phone.c_str(), it->waiting.c_str());
			}
		}
	}
}

// ������� ������
std::string QUEUE::Parsing::findParsing(std::string str, Currentfind find)
{
	std::vector<std::string> lines;
	std::string current_str;

	bool isNewLine{ false };

	for (size_t i = 0; i != str.length(); ++i)
	{

		if (isNewLine)
		{
			if (!current_str.empty())
			{
				lines.push_back(current_str);
				current_str.clear();
			}
		}

		if (str[i] != ' ') // ���� ��������� (��������� ������ ������)
		{
			current_str += str[i];
			isNewLine = false;
		}
		else
		{
			isNewLine = true;
		}
	}

	if (!lines.empty())
	{
		switch (find)
		{
		case QUEUE::Currentfind::phone_find:
		{
			return phoneParsing(lines[7]);	
			break;
		}
		case QUEUE::Currentfind::waiting_find:
		{
			return lines[8];
			break;
		}
		case QUEUE::Currentfind::queue_find: {
			return lines[2];
			break;
		}
		default:
		{
			return "null";
			break;
		}
		}
	}
	else {
		return "null";
	}
}
