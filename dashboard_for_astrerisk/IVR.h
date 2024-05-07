//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//	      ������� ������� ���������� � IVR			//
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
		std::string phone	{"null"};		// ������� ����� �������� ������� � IVR �������
		std::string waiting {"null"};		// ����� � (���) ������� �� �������
		bool isQueue		{ false };		// ���� � ������� �� ��������� false
	};

	class Parsing 
	{
	public:
		Parsing(const char *fileIVR);
		~Parsing();		
	
		bool isExistList();						// ���� �� � �������	
		
		void show();

	private:	
		std::string findParsing(std::string str, IVR::Currentfind find); // �������  
		
		std::vector<IVR::Pacients> pacient_list;				
	};
}


#endif //IVR_H
