#include "IVR.h"
#include "InternalFunction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "SQLRequest.h"
#include <iterator>


// ����������
IVR::Parsing::Parsing(const char *fileIVR)
{
	std::ifstream fileivr;
	
	fileivr.open(fileIVR);

	if (fileivr.is_open()) {
		//std::cout << "open file... OK\n";
		
		std::string line;				

		// ��������
		while (std::getline(fileivr, line)) {
			Pacients pacient;						

			pacient.phone	= findParsing(line, IVR::Currentfind::phone_find);
			pacient.waiting = findParsing(line, IVR::Currentfind::waiting_find);

			// ���������
			if (pacient.phone != "null" && pacient.waiting != "null") {
				pacient_list.push_back(pacient);
			}				
		}		
	}

	fileivr.close();
}

// ����������
IVR::Parsing::~Parsing()
{
		
}

// �������� ������ �� ������ � ��������
bool IVR::Parsing::isExistList()
{
	return (pacient_list.empty() ? false : true);
}


void IVR::Parsing::show()
{	
	if (this->isExistList()) {
		std::cout << "Line IVR is (" << pacient_list.size() << ")\n\n";

		for (std::vector<IVR::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it) {
			
			std::cout << it->phone << " >> " << it->waiting << "\n";
					 
			{ // test
				std::string subString1 = "00:00:4";
				std::string subString2 = "00:00:5";
				std::string subString3 = "00:03:";
				std::string subString4 = "00:04:";
				std::string subString5 = "00:05:";


				size_t found1 = it->waiting.find(subString1);
				size_t found2 = it->waiting.find(subString2);
				size_t found3 = it->waiting.find(subString3);
				size_t found4 = it->waiting.find(subString4);
				size_t found5 = it->waiting.find(subString5);

				if (found1 != std::string::npos)
				{
					std::cout << "�������";
				}
				if (found2 != std::string::npos)
				{
					std::cout << "�������";
				}
				if (found3 != std::string::npos)
				{
					std::cout << "�������";
				}
				if (found4 != std::string::npos)
				{
					std::cout << "�������";
				}
				if (found5 != std::string::npos)
				{
					std::cout << "�������";
				}
			}		
			

		}			
	}
	else {
		std::cout << "IVR is empty!\n";
	}	
}

// ���������� ������ � ��
void IVR::Parsing::insertData()
{
	if (this->isExistList()) {
		SQL_REQUEST::SQL base;

		for (std::vector<IVR::Pacients>::iterator it = pacient_list.begin(); it != pacient_list.end(); ++it)
		{
			if (base.isConnectedBD())
			{
				base.insertIVR(it->phone.c_str(), it->waiting.c_str());
			}
		}
	}	
}

// ������� ������
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
	else {
		return "null";
	}	
}


