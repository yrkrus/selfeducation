//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 13.05.2024				//
//				   SQL запросы	             		//
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

		bool isConnectedBD();	// есть ли коннект с БД

		void query_test();

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql); // подключаемся к БД MySQL
	};

};


#endif //SQLREQUEST_H