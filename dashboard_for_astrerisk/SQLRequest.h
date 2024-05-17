//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 14.05.2024				//
//				   SQL �������	             		//
//													//	
//////////////////////////////////////////////////////
#include <iostream>
#include "Constants.h"
#include <mysql/mysql.h>

#ifndef SQLREQUEST_H
#define	SQLREQUEST_H

namespace SQL_REQUEST
{
	class SQL
	{
	public:
		SQL();
		~SQL();

		bool isConnectedBD();	// ���� �� ������� � ��

		void query_test();
		void insertData_test();

		//table IVR
		void insertIVR(const char *phone, const char *time); // ���������� ������ � ������� IVR
		bool isExistIVRPhone(const char *phone);			 // ���������� �� ����� ��� ����� � ������� IVR
		int getLastIDphone(const char *phone);				// ��������� ���������� ID �����������
		void updateIVR(const char *id, const char *phone, const char *time); // ���������� ������ � ������� IVR

		// table QUEUE
		void insertQUEUE(const char *queue, const char *phone, const char *time); // ���������� ������ � ������� QUEUE
		bool isExistQUEUE(const char *queue, const char *phone);				  // ���������� �� ����� ��� ����� � ������� QUEUE
		void updateQUEUE(const char *id, const char *phone, const char *time);					  // ���������� ������ � ������� QUEUE
		int getLastIDQUEUE(const char *phone);		// ��������� ���������� ID �����������
		void updateQUEUE_SIP(const char *phone, const char *sip, const char *talk_time); // ���������� ������ ������� QUEUE � ��� � ��� ������ ������������� ��������
		bool isExistQUEUE_SIP(const char *phone);   // ���������� �� ����� ����� � ������� QUEUE ����� �������� sip ��������� ������� � �������� �����


		// ����������
		int getIVR_totalCalls();			// ������� ����� ��������� �� ����� IVR
		int getQUEUE_Calls(bool answered);  // ������� ����� �������� � ������� �����������
		int getQUEUE_Calls();				// ������� ����� ���� � �������

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql); // ������������ � �� MySQL
	};

};


#endif //SQLREQUEST_H