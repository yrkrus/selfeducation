#include "IVR.h"
#include "InternalFunction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>


using std::vector;

// коструктор
IVR::Parsing::Parsing(const char *fileIVR)
{
	std::ifstream fileivr;
	
	fileivr.open(fileIVR);

	if (fileivr.is_open()) {
		//std::cout << "open file... OK\n";
		
		std::string line;				

		// разберем
		while (std::getline(fileivr, line)) {
			Pacients pacient;						

			pacient.phone	= findParsing(line, IVR::Currentfind::phone_find);
			pacient.waiting = findParsing(line, IVR::Currentfind::waiting_find);

			// добавляем
			if (pacient.phone != "null" && pacient.waiting != "null") {
				pacient_list.push_back(pacient);
			}				
		}		
	}
	else {
		//std::cout << "open file ... ERROR\n";
	}
}

// деструткор
IVR::Parsing::~Parsing()
{
	if (!pacient_list.empty()) {
		pacient_list.clear();
	}	
}

// проверка пустой ли список в номерами
bool IVR::Parsing::isExistList()
{
	return (pacient_list.empty() ? false : true);
}


void IVR::Parsing::show()
{
	if (!pacient_list.empty()) {
		
		std::cout << "Line IVR is (" << pacient_list.size() << ")\n\n";
		
		for (const auto &list : pacient_list)
		{
			std::cout << list.phone << " >> " << list.waiting << "\n";
		}
	}
	else {
		std::cout << "IVR is empty!\n";
	}	
}



// парсинг строки
std::string IVR::Parsing::findParsing(std::string str, Currentfind find)
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

		if (str[i] != ' ') // ищем разделить (разделить пустая строка)
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
		case IVR::Currentfind::phone_find:
		{
			return phoneParsing(lines[7]);			
			break;
		}
		case IVR::Currentfind::waiting_find:
		{
			return lines[8];
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


