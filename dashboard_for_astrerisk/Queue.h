//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 01.06.2024				//
//	      ������� ������� ���������� � �������		//
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
		std::string phone	{ "null" };		// ������� ����� �������� ������� � ������� ������
		std::string waiting { "null" };		// ����� � (���) ������� ������ � ������� ���������
		std::string queue	{ "null" };		// ����� �������
	};

	class Parsing
	{
	public:
		Parsing(const char *fileQueue);
		~Parsing();

		bool isExistList();					// ���� �� �������	
		void show();
		void insertData();					// ���������� ������ � ��
		bool isExistQueueAfter20hours();	// �������� ���� �� �� ���������� ������ ����� 20:00
		void updateQueueAfter20hours();		// ���������� ������ ���� ������ ������ ���� ��� ��� �������� ���������� �� �����

	private:
		std::string findParsing(std::string str, QUEUE::Currentfind find); // �������  
		std::vector<QUEUE::Pacients> pacient_list;	
		
	};
}

#endif //QUEUE_H
