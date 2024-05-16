#include "SQLRequest.h"
#include "Constants.h"
#include "InternalFunction.h"
#include <mysql/mysql.h>


SQL_REQUEST::SQL::SQL()
{	
	createMySQLConnect(this->mysql);
}

SQL_REQUEST::SQL::~SQL()
{
}


void SQL_REQUEST::SQL::createMySQLConnect(MYSQL &mysql)
{

	const char *host = CONSTANTS::cHOST.c_str();
	const char *login = CONSTANTS::cLOGIN.c_str();
	const char *pwd = CONSTANTS::cPASSWORD.c_str();
	const char *bd = CONSTANTS::cBD.c_str();

	if (mysql_init(&mysql) == nullptr)
	{
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

// есть ли коннект с БД
bool SQL_REQUEST::SQL::isConnectedBD()
{
	// status = 0 значит коннект есть
	if (mysql_ping(&this->mysql) != 0) {
		createMySQLConnect(this->mysql);

		isConnectedBD();
	}
	else {
		return true;
	}	
}


void SQL_REQUEST::SQL::query_test()
{
	if (mysql_query(&this->mysql, "SELECT * FROM ivr")) {
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

void SQL_REQUEST::SQL::insertData_test()
{
	std::string query = "insert into ivr (phone,waiting_time) values ('+79275052333','15')";

	if (mysql_query(&this->mysql, query.c_str()) != 0) {
		std::cout << "error insert\n";
	}
	else {
		std::cout << "insert ok\n";
	}

}


// добавление данных в таблицу IVR
void SQL_REQUEST::SQL::insertIVR(const char *phone, const char *time)
{	
	if (!isConnectedBD()) {
		std::cerr << "Error: can't connect to database\n";
		return;
	}	
	
	// проверим есть ли такой номер 	
	if (isExistIVRPhone(phone))	{ // номер существует, обновляем данные
		
		std::string id = std::to_string(getLastIDphone(phone));
		
		updateIVR(id.c_str(), phone, time);
		return;
	}
	else {		
		std::string query = "insert into ivr (phone,waiting_time) values ('" + std::string(phone) + "','" + std::string(time) + "')";
		
		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			std::cout << "Data (insertIVR) error\n";
		}	
	}	

	mysql_close(&this->mysql);
}

// существует ли такой уже номер в таблице IVR
bool SQL_REQUEST::SQL::isExistIVRPhone(const char *phone)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return true;
	}
	
	const std::string query = "select count(phone) from ivr where phone = " 
							  + std::string(phone) +" and date_time > '"
							  + getCurretDateTimeAfterMinutes(3)+"' order by date_time desc";

	if (mysql_query(&this->mysql, query.c_str() ) != 0)	{
		// ошибка считаем что есть запись		
		std::cerr << mysql_error(&this->mysql);
		return true;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);	
	mysql_free_result(result);	

	return ( std::stoi(row[0]) == 0 ? false : true);	
}

// получение последнего ID актуального
int SQL_REQUEST::SQL::getLastIDphone(const char *phone)
{	
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return -1;
	}

	const std::string query = "select id from ivr where phone = "
		+ std::string(phone) + " and date_time > '"
		+ getCurrentStartDay() + "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что нет записи		
		std::cerr << mysql_error(&this->mysql);
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	return std::stoi(row[0]);
}

// обновление данных в таблице IVR
void SQL_REQUEST::SQL::updateIVR(const char *id,const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return;
	}

	std::string query = "update ivr set waiting_time = '" + std::string(time) + "' where phone = '" + std::string(phone) + "' and id ='"+std::string(id)+"'";
	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		std::cout << "Data (updateIVR) error\n";
	};
	

	mysql_close(&this->mysql);
}

// добавление данных в таблицу QUEUE
void SQL_REQUEST::SQL::insertQUEUE(const char *queue, const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return;
	}

	// проверим есть ли такой номер 	
	if (isExistQUEUE(queue,phone))
	{ // номер существует, обновляем данные
	
		std::string id = std::to_string(getLastIDQUEUE(phone));
		updateQUEUE(id.c_str(),phone, time);
		return;
	}
	else
	{
		std::string query = "insert into queue (number_queue,phone,waiting_time) values ('" 
							+ std::string(queue) + "','" 
							+ std::string(phone) + "','" 
							+ std::string(time) + "')";

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			std::cout << "Data (insertQUEUE) error\n";
		}
	}

	mysql_close(&this->mysql);

}

// существует ли такой уже номер в таблице QUEUE
bool SQL_REQUEST::SQL::isExistQUEUE(const char *queue, const char *phone)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return true;
	}

	// проверка вдруг ведется разговор
	{
		const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
			+ "' and phone = '" + std::string(phone) + "'"
			+ " and date_time > '" + getCurrentStartDay() + "'"
			+ " and answered ='1' order by date_time desc limit 1";

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			// ошибка считаем что есть запись		
			std::cerr << mysql_error(&this->mysql);
			return true;
		}

		// результат
		MYSQL_RES *result = mysql_store_result(&this->mysql);
		MYSQL_ROW row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (std::stoi(row[0]) >= 1)
		{
			return true;
		}
	}

	// нет разговора проверяем повтрность
	const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
								+ "' and phone = '" + std::string(phone) + "'"
								+ " and date_time > '" + getCurretDateTimeAfterMinutes(5) +"'"
								+ " and answered ='0' and sip ='-1' order by date_time desc limit 1";
							  

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что есть запись		
		std::cerr << mysql_error(&this->mysql);
		return true;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	return (std::stoi(row[0]) == 0 ? false : true);
}

// обновление данных в таблице QUEUE
void SQL_REQUEST::SQL::updateQUEUE(const char *id, const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return;
	}

	std::string query = "update queue set waiting_time = '" + std::string(time) + "' where phone = '" + std::string(phone) + "' and id ='" + std::string(id) + "'";;

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		std::cout << "Data (updateQUEUE) error\n";
	};

	mysql_close(&this->mysql);
}

// получение последнего ID актуального
int SQL_REQUEST::SQL::getLastIDQUEUE(const char *phone)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return -1;
	}

	const std::string query = "select id from queue where phone = "
		+ std::string(phone) + " and date_time > '"
		+ getCurrentStartDay() + "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что нет записи		
		std::cerr << mysql_error(&this->mysql);
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	return std::stoi(row[0]);
}

// обновление данных таблицы QUEUE о том с кем сейчас разговаривает оператор
void SQL_REQUEST::SQL::updateQUEUE_SIP(const char *phone, const char *sip, const char *talk_time)
{
	if (!isConnectedBD())
	{
		std::cerr << "Error: can't connect to database\n";
		return;
	}

	// проверим есть ли такой номер 	
	if (isExistQUEUE_SIP(phone))
	{ // номер существует, обновляем данные
		std::string id = std::to_string(getLastIDQUEUE(phone));

		std::string query = "update queue set sip = '" + std::string(sip) + "', talk_time = '"+ getTalkTime(talk_time) + "', answered ='1' where phone = '" + std::string(phone) + "' and id ='" + std::string(id) + "'";

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			std::cout << "Data (updateQUEUE_SIP) error\n";
		};

		mysql_close(&this->mysql);		
	}	
}

// существует ли такой номер в таблице QUEUE чтобы добавить sip оператора который с разговор ведет
bool SQL_REQUEST::SQL::isExistQUEUE_SIP(const char *phone)
{
	const std::string query = "select count(phone) from queue where phone = '" + std::string(phone)
							+ "' and date_time > '" + getCurrentStartDay() 
							+ "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что есть запись		
		std::cerr << mysql_error(&this->mysql);
		return true;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	return (std::stoi(row[0]) == 0 ? false : true);
}
