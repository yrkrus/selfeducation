#include "ActiveSip.h"
#include "InternalFunction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using std::vector;

// ����������
ACTIVE_SIP::Parsing::Parsing(const char *fileActiveSip)
{
	std::ifstream sip;

	sip.open(fileActiveSip);

	if (sip.is_open())
	{
		//std::cout << "open file... OK\n";

		std::string line;

		// ��������
		while (std::getline(sip, line))
		{
			Pacients pacient;

			pacient.internal_sip	= findParsing(line, ACTIVE_SIP::Currentfind::internal_sip_find);
			pacient.phone			= findParsing(line, ACTIVE_SIP::Currentfind::phone_find);
			pacient.talk_time		= findParsing(line, ACTIVE_SIP::Currentfind::talk_time_find);

			// ���������
			if (pacient.internal_sip	!= "null" &&
				pacient.phone			!= "null" &&
				pacient.talk_time		!= "null")
			{
				active_sip_list.push_back(pacient);
			}
		}
	}
	else
	{
		//std::cout << "open file ... ERROR\n";
	}
}

// ����������
ACTIVE_SIP::Parsing::~Parsing()
{
	if (!active_sip_list.empty())
	{
		active_sip_list.clear();
	}
}

// �������� ������ �� ������ � ��������
bool ACTIVE_SIP::Parsing::isExistList()
{
	return (active_sip_list.empty() ? false : true);
}


void ACTIVE_SIP::Parsing::show()
{
	if (!active_sip_list.empty())
	{

		std::cout << "Line Active SIP is (" << active_sip_list.size() << ")\n\n";

		for (const auto &list : active_sip_list)
		{
			std::cout << list.internal_sip << " | " << list.phone << " talk time " << list.talk_time << "\n";
		}
	}
	else
	{
		std::cout << "Active SIP is empty!\n";
	}
}

// ������� ������
std::string ACTIVE_SIP::Parsing::findParsing(std::string str, ACTIVE_SIP::Currentfind find)
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

		if (str[i] != '!') // ���� ��������� (��������� !)
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
		case ACTIVE_SIP::Currentfind::phone_find:
		{
			return phoneParsing(lines[7]);

			break;
		}
		case ACTIVE_SIP::Currentfind::internal_sip_find:	// ���������� ����� SIP
		{
			//return lines[8];
			break;
		}
		case ACTIVE_SIP::Currentfind::talk_time_find:		// ����� ��������� � (��� -> 00:00:00)
		{
			//return lines[2];
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

