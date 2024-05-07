//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//    ������� �������� ������� ������� � ��������	//
//                  ����� ��������					//
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
		std::string phone		 { "null" };	// ������� ����� �������� � ������� ������� ������
		std::string internal_sip { "null" };	//  ���������� sip ������� ����� ������
		std::string talk_time	 { "null" };    // ����� ����������  ����� � int ����������
	};

	class Parsing
	{
	public:
		Parsing(const char *fileActiveSip);
		~Parsing();		

		void show();
		bool isExistList();

	private:
		std::string findParsing(std::string str, ACTIVE_SIP::Currentfind find); // �������
		std::vector<ACTIVE_SIP::Pacients> active_sip_list;
	};


	class ActiveSip : protected Parsing
	{


	};
}



#endif // ACTIVESIP_H
