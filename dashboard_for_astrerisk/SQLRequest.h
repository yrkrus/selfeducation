//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 13.05.2024				//
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

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql); // ������������ � �� MySQL
	};

};


#endif //SQLREQUEST_H