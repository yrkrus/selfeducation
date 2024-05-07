//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//    парсинг активных звонков которые в реалтайм	//
//                  ведут разговор					//
//													//	
//////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>

#ifndef ACTIVESIP_H
#define ACTIVESIP_H


namespace ACTIVE_SIP
{
	enum Currentfind
	{
		phone_find,
		internal_sip_find,
		talk_time_find,
	};

	struct Pacients
	{
		std::string phone		 { "null" };	// текущий номер телфеона с которым ведется беседа
		std::string internal_sip { "null" };	//  внутренний sip который ведет беседу
		std::string talk_time	 { "null" };    // время развговора  потом в int переделать
	};

	class Parsing
	{
	public:
		Parsing(const char *fileActiveSip);
		~Parsing();		

		void show();
		bool isExistList();

	private:
		std::string findParsing(std::string str, ACTIVE_SIP::Currentfind find); // парсинг
		std::vector<ACTIVE_SIP::Pacients> active_sip_list;
	};


	class ActiveSip : protected Parsing
	{


	};
}



#endif // ACTIVESIP_H
