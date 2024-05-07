//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
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
		bool isQueue		{ false };		// ушел в очередь по умолчанию false
	};

	class Parsing 
	{
	public:
		Parsing(const char *fileIVR);
		~Parsing();		
	
		bool isExistList();						// ушел ли в очередь	
		
		void show();

	private:	
		std::string findParsing(std::string str, IVR::Currentfind find); // парсинг  
		
		std::vector<IVR::Pacients> pacient_list;				
	};
}


#endif //IVR_H
