#include "Queue.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "InternalFunction.h"

using std::vector;

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
	else
	{
		//std::cout << "open file ... ERROR\n";
	}
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
	if (!pacient_list.empty())
	{

		std::cout << "Line QUEUE is (" << pacient_list.size() << ")\n\n";

		for (const auto &list : pacient_list)
		{
			std::cout << list.queue << " | " << list.phone << " >> " << list.waiting << "\n";
		}
	}
	else
	{
		std::cout << "QUEUE is empty!\n";
	}
}

// ������� ������
std::string QUEUE::Parsing::findParsing(std::string str, Currentfind find)
{
	std::vector<std::string> lines;
	std::string current_str;

	bool isNewLine{ false };

	for (int i = 0; i != str.length(); ++i)
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
}
