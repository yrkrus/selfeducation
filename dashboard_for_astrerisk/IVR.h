//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 14.05.2024				//
//	      парсинг звонков попадающих в IVR			//
//													//	
//////////////////////////////////////////////////////


#include <string>
#include <vector>
#include <iostream>

#ifndef IVR_H
#define IVR_H

namespace IVR 
{		
	enum Currentfind
	{
		phone_find,
		waiting_find,
	};
	
	struct Pacients
	{
		std::string phone	{"null"};		// текущий номер телефона который в IVR слушает
		std::string waiting {"null"};		// время в (сек) которое он слушает		
	};

	class Parsing 
	{
	public:
		Parsing(const char *fileIVR);
		~Parsing();		
	
		bool isExistList();						// существет ли очередь IVR		
		void show();

		void insertData();						//добавление данных в БД

	private:	
		std::string findParsing(std::string str, IVR::Currentfind find); // парсинг  
		
		std::vector<IVR::Pacients> pacient_list;				
	};
}


#endif //IVR_H
