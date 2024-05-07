//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//	      парсинг звонков попадающих в Очередь		//
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
		std::string waiting { "null" };		// время в (сек) которое сейчас в очереди находится
		std::string queue	{ "null" };		// номер очереди
	};

	class Parsing
	{
	public:
		Parsing(const char *fileQueue);
		~Parsing();

		bool isExistList();					// есть ли очередь	

		void show();

	private:
		std::string findParsing(std::string str, QUEUE::Currentfind find); // парсинг  

		std::vector<QUEUE::Pacients> pacient_list;
	};
}

#endif //QUEUE_H
