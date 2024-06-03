//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 03.06.2024				//
//				   SQL �������	             		//
//													//	
//////////////////////////////////////////////////////
#include <iostream>
#include "Constants.h"
#include <mysql/mysql.h>
#include "IVR.h"
#include "Queue.h"

#ifndef SQLREQUEST_H
#define	SQLREQUEST_H

namespace SQL_REQUEST
{
	class SQL
	{
	public:
		SQL();
		~SQL() = default;

		bool isConnectedBD();	// ���� �� ������� � ��

		void query_test();
		void insertData_test();

		//table IVR
		void insertIVR(const char *phone, const char *time, std::string callerid ); // ���������� ������ � ������� IVR
		bool isExistIVRPhone(const char *phone);					// ���������� �� ����� ��� ����� � ������� IVR
		int getLastIDphone(const char *phone);				// ��������� ���������� ID �����������
		void updateIVR(const char *id, const char *phone, const char *time); // ���������� ������ � ������� IVR
		


		// table QUEUE
		void insertQUEUE(const char *queue, const char *phone, const char *time); // ���������� ������ � ������� QUEUE
		bool isExistQUEUE(const char *queue, const char *phone);				  // ���������� �� ����� ��� ����� � ������� QUEUE
		void updateQUEUE(const char *id, const char *phone, const char *time);					  // ���������� ������ � ������� QUEUE
		int getLastIDQUEUE(const char *phone);		// ��������� ���������� ID �����������
		void updateQUEUE_SIP(const char *phone, const char *sip, const char *talk_time); // ���������� ������ ������� QUEUE � ��� � ��� ������ ������������� ��������
		bool isExistQUEUE_SIP(const char *phone);   // ���������� �� ����� ����� � ������� QUEUE ����� �������� sip ��������� ������� � �������� �����
		void updateQUEUE_fail(const std::vector<QUEUE::Pacients> &pacient_list); // ���������� ������ ����� ������ �� �������� ����� ������� 
		void updateQUEUE_fail();				// ���������� ������ ����� ������ �� �������� ����� ������� 
		void updateIVR_to_queue(const std::vector<QUEUE::Pacients> &pacient_list); // ���������� ������ ����� � ��� ������ �� IVR ����� � �������
		bool isExistQueueAfter20hours(); // �������� ���� �� ������ ������� ��������� ����� 20:00
		void updateQUEUE_hash(const std::vector<QUEUE::Pacients> &pacient_list); // ���������� ���� hash ����� ������� ����������


		// ����������
		int getIVR_totalCalls();			// ������� ����� ��������� �� ����� IVR
		int getIVR_totalCalls(const IVR::CallerID &trunk);			// ������� ����� ��������� �� ����� IVR (����� �� trunk)
		int getQUEUE_Calls(bool answered);  // ������� ����� �������� � ������� �����������
		int getQUEUE_Calls();				// ������� ����� ���� � �������

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql); // ������������ � �� MySQL
	};

};


#endif //SQLREQUEST_H