#include "IVR.h"
#include "InternalFunction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "SQLRequest.h"
#include <iterator>


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

			pacient.phone		= findParsing(line, IVR::Currentfind::phone_find);
			pacient.waiting		= findParsing(line, IVR::Currentfind::waiting_find);
			pacient.callerID	= getCallerID(findParsing(line, IVR::Currentfind::caller_id));

			// добавляем
			if (pacient.phone != "null" && 
				pacient.waiting != "null" &&
				pacient.callerID != null_caller) {
				pacient_list.push_back(pacient);
			}				
		}		
	}

	fileivr.close();
}


IVR::CallerID IVR::getCallerID(std::string str)
{
	if (str.find("ivr-13")		 != std::string::npos)	return domru_220000;
	if (str.find("druOUT220220") != std::string::npos)	return domru_220220;
	if (str.find("sts_")		 != std::string::npos)	return sts;
	if (str.find("221122")		 != std::string::npos)	return comagic;
	return null_caller;
}

std::string IVR::getCallerID(const CallerID &callerID)
{
	switch (callerID)
	{
		case(domru_220220): {
			return "220220";
			break;
		}
		case(domru_220000): {
			return "220000";
			break;
		}
		case(sts):
		{
			return "STS";
			break;
		}
		case(comagic):
		{
			return "COMAGIC";
			break;
		}
		case(null_caller):
		{
			return "null_caller";
			break;
		}	
	}
}



// проверка пустой ли список в номерами
bool IVR::Parsing::isExistList()
{
	return (pacient_list.empty() ? false : true);
}


void IVR::Parsing::show()
{	
	if (this->isExistList()) {
		std::cout << "Line IVR is (" << pacient_list.size() << ")\n";
		std::cout << "trunk" << "\t    \t" << "phone" << "\t \t" << " wait time" << "\n";

		for (std::vector<IVR::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it) {
				
			std::cout << getCallerID(it->callerID) << "\t >> \t" << it->phone << "\t (" << it->waiting << ")\n";

			{ // test
				
				std::string subString3 = "00:01:";
				std::string subString4 = "00:02:";
				std::string subString5 = "00:03:";
				std::string subString6 = "00:04:";
				std::string subString7 = "00:05:";


				
				size_t found3 = it->waiting.find(subString3);
				size_t found4 = it->waiting.find(subString4);
				size_t found5 = it->waiting.find(subString5);
				size_t found6 = it->waiting.find(subString6);
				size_t found7 = it->waiting.find(subString7);
				

				
				if (found3 != std::string::npos)
				{
					std::cout << "найдено";
				}
				if (found4 != std::string::npos)
				{
					std::cout << "найдено";
				}
				if (found5 != std::string::npos)
				{
					std::cout << "найдено";
				}
				if (found6 != std::string::npos)
				{
					std::cout << "найдено";
				}
				if (found7 != std::string::npos)
				{
					std::cout << "найдено";
				}				
			}		

		}			
	}
	else {
		std::cout << "IVR is empty!\n";
	}	
}

// добавление данных в БД
void IVR::Parsing::insertData()
{
	if (this->isExistList()) {
		SQL_REQUEST::SQL base;

		for (std::vector<IVR::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it)
		{
			if (base.isConnectedBD())
			{
				base.insertIVR(it->phone.c_str(), it->waiting.c_str(), getCallerID(it->callerID));
			}
		}
	}	
}

// парсинг строки
std::string IVR::Parsing::findParsing(std::string str, Currentfind find)
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
		case IVR::Currentfind::caller_id:
		{
			return lines[0]+","+ lines[1];
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


