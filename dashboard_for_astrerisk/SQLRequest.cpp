#include "SQLRequest.h"
#include "Constants.h"
#include <mysql/mysql.h>

SQL_REQUEST::SQL::SQL()
{
	createMySQLConnect(this->mysql);
}

SQL_REQUEST::SQL::~SQL()
{
}

// есть ли коннект с БД
bool SQL_REQUEST::SQL::isConnectedBD()
{
	// status = 0 значит коннект есть.	
	return (mysql_ping(&this->mysql) == 0 ? true : false);

}


void SQL_REQUEST::SQL::query_test()
{


	if (mysql_query(&this->mysql, "SELECT * FROM role")) {
		std::cerr << "error query\n";
		return;
	} 

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (i > 0)
			{
				std::cout << ", ";
			}
			std::cout << row[i];
		}
		std::cout << std::endl;
	}

	mysql_free_result(result);

}

void SQL_REQUEST::SQL::createMySQLConnect(MYSQL &mysql)
{
	
	const char *host = CONSTANTS::cHOST.c_str();
	const char *login = CONSTANTS::cLOGIN.c_str();
	const char *pwd = CONSTANTS::cPASSWORD.c_str();
	const char *bd = CONSTANTS::cBD.c_str();
	
	if (mysql_init(&mysql) == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		std::cout << "Error: can't create MySQL-descriptor\n";
		return;
	}

	if (!mysql_real_connect(&mysql, host, login, pwd, bd, NULL, NULL, 0))
	{
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		std::cout << "Error: can't connect to database " << bd << ". " << mysql_error(&mysql) << "\n";
		return;
	};

	mysql_set_character_set(&mysql, "utf8");
}
