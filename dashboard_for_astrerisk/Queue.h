//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 03.06.2024				//
//	      ������� ������� ���������� � �������		//
//													//	
//////////////////////////////////////////////////////


#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

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
		~Parsing() = default;

		bool isExistList();					// ���� �� �������	
		void show();				
		
		void insertData();					// ���������� ������ � ��
		bool isExistQueueAfter20hours();	// �������� ���� �� �� ���������� ������ ����� 20:00
		void updateQueueAfter20hours();		// ���������� ������ ���� ������ ������ ���� ��� ��� �������� ���������� �� �����
		

	private:
		std::string findParsing(std::string str, QUEUE::Currentfind find); // �������  
		std::vector<QUEUE::Pacients> pacient_list;			
	};


	struct BD 
	{
		std::string id;
		std::string phone;
		std::string date_time;
		size_t hash{0};
	};

	class QueueBD 
	{
		public:
			QueueBD()	= default;
			~QueueBD()	= default;
			std::vector<QUEUE::BD> list;
	};
}

#endif //QUEUE_H
