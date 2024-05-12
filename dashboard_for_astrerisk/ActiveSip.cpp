#include "ActiveSip.h"
#include "InternalFunction.h"
#include "Constants.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

// коструктор
ACTIVE_SIP::Parsing::Parsing(const char *fileActiveSip)
{
	// найдем активных операторов в линии
	createListActiveOperators();
	
	// есть ли активные SIP операторы в линии 
	if (!isExistListActiveOperators()) {
		std::cout << "Active SIP operators is empty!\n";
		return;
	}

	std::ifstream sip;

	sip.open(fileActiveSip);

	if (sip.is_open())
	{
		// разберем  ТУТ ПОКА в 1 потоке все происходит потом сделать многопочную!!!  и сразу в БД!!
		if (!list_operators.empty()) {		
			
			std::string line;
			while (std::getline(sip, line))
			{
				for (std::vector<Operators>::iterator it = list_operators.begin(); it != list_operators.end(); ++it) {					
				
					// найдем текущий нужный sip 
					if (line.find("Local/" + it->sip_number) != std::string::npos) {
						if (line.find("Outgoing") == std::string::npos) {
							
							Pacients pacient;

							pacient.internal_sip = findParsing(line, ACTIVE_SIP::Currentfind::internal_sip_find, it->sip_number);
							pacient.phone = findParsing(line, ACTIVE_SIP::Currentfind::phone_find, it->sip_number);
							pacient.talk_time = findParsing(line, ACTIVE_SIP::Currentfind::talk_time_find, it->sip_number);							

							// добавляем
							if (pacient.internal_sip != "null" &&
								pacient.phone != "null" &&
								pacient.talk_time != "null")
							{
								active_sip_list.push_back(pacient);
								break; // нет смысла дальше while т.к. нашли нужные данные
							}
						}
					}					
				}				
			}
		}		
	}
	else
	{
		//std::cout << "open file ... ERROR\n";
	}
}

// деструткор
ACTIVE_SIP::Parsing::~Parsing()
{
	if (!active_sip_list.empty()) { active_sip_list.clear(); }
}

// проверка пустой ли список в номерами
bool ACTIVE_SIP::Parsing::isExistList()
{
	return (active_sip_list.empty() ? false : true);
}

// получаем активный лист операторов которые у нас сейчас в линии находятся
void ACTIVE_SIP::Parsing::createListActiveOperators()
{		
	for (size_t i = 0; i != CONSTANTS::AsteriskQueue::COUNT; ++i) {
	
		std::string responce = CONSTANTS::cActiveSipOperatorsResponse;

		// заменяем %queue на номер очереди
		std::string repl = "%queue";
		size_t position = responce.find(repl);
		responce.replace(position, repl.length(), getNumberQueue(static_cast<CONSTANTS::AsteriskQueue>(i)));

		if (!CONSTANTS::DEBUG_MODE) {
			system(responce.c_str());
		}			

		findActiveOperators(CONSTANTS::cActiveSipOperatorsName.c_str(), getNumberQueue(static_cast<CONSTANTS::AsteriskQueue>(i)));
	}
}


void ACTIVE_SIP::Parsing::show()
{
	if (!active_sip_list.empty())
	{

		std::cout << "Line Active SIP is (" << active_sip_list.size() << ")\n\n";

		for (const auto &list : active_sip_list)
		{
			std::cout << list.internal_sip << " >> " << list.phone << " (" << getTalkTime(list.talk_time) << ")\n";
		}
	}
	else
	{
		std::cout << "Active SIP is empty!\n";
	}
}

// парсинг строки
std::string ACTIVE_SIP::Parsing::findParsing(std::string str, ACTIVE_SIP::Currentfind find, const std::string number_operator)
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

		if (str[i] != '!') // ищем разделить (разделить !)
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
		case ACTIVE_SIP::Currentfind::internal_sip_find:	// внутренний номер SIP (мы его и так знаем из функции)
		{
			return number_operator;
			break;
		}
		case ACTIVE_SIP::Currentfind::talk_time_find:		// время разговора
		{
			return lines[9];
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


// парсинг нахождения активного sip оператора
std::string ACTIVE_SIP::Parsing::findNumberSip(std::string &str)
{
	// 6 т.к. lenght("Local/) = 6	
	return str.substr( str.find_first_of("Local/") + 6,  str.find_first_of("@") - str.find_first_of("Local/") - 6);	
}



// // парсинг #2 (для activeoperaots) 
void ACTIVE_SIP::Parsing::findActiveOperators(const char *fileOperators, std::string queue)
{
	
	std::ifstream file;
	file.open(fileOperators);

	if (!file.is_open()) {
		// не получается открыть файл уходим из функции
		return;		
	}

	std::string line;

	// разберем
	while (std::getline(file, line))
	{
		// заносить активные CAllers не требуется
		if (line.find("Callers") != std::string::npos) {
			break;
		}
		
		// проверим есть ли активный sip
		if (line.find("Local/") != std::string::npos) {
			// найдем активный sip
			
			Operators active_operator;
			active_operator.sip_number = findNumberSip(line);
			active_operator.queue.push_back(queue);
			
			// проверим есть ли уже такой sip чтобы добавить ему только очередь
			bool isExistOperator{ false };
			for (std::vector<Operators>::iterator it = list_operators.begin(); it != list_operators.end(); ++it) {
				
				if (it->sip_number == active_operator.sip_number) {
					isExistOperator = true;
					it->queue.push_back(queue);
					break;
				}
			}
			
			if (!isExistOperator) {
				list_operators.push_back(active_operator);
			}			
		}
	}	
}


bool ACTIVE_SIP::Parsing::isExistListActiveOperators()
{
	return (!list_operators.empty() ? true : false );
}

