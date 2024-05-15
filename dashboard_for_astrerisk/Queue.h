//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 14.05.2024				//
//	      парсинг звонков попадающих в ќчередь		//
//													//	
//////////////////////////////////////////////////////


#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>
#include <iostream>

namespace QUEUE
{
	enum Currentfind
	{
		phone_find,
		waiting_find,
		queue_find,
	};

	struct Pacients
	{
		std::string phone	{ "null" };		// текущий номер телефона который в очереди сейчас
		std::string waiting { "null" };		// врем€ в (сек) которое сейчас в очереди находитс€
		std::string queue	{ "null" };		// номер очереди
	};

	class Parsing
	{
	public:
		Parsing(const char *fileQueue);
		~Parsing();

		bool isExistList();					// есть ли очередь	
		void show();

		void insertData();					//добавление данных в Ѕƒ

	private:
		std::string findParsing(std::string str, QUEUE::Currentfind find); // парсинг  
		std::vector<QUEUE::Pacients> pacient_list;
	};
}

#endif //QUEUE_H
