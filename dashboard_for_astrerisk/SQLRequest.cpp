#include "SQLRequest.h"
#include "Constants.h"
#include "InternalFunction.h"
#include "IVR.h"
#include <mysql/mysql.h>
#include <iterator>


SQL_REQUEST::SQL::SQL()
{	
	createMySQLConnect(this->mysql);
}

void SQL_REQUEST::SQL::createMySQLConnect(MYSQL &mysql)
{

	const char *host = CONSTANTS::cHOST.c_str();
	const char *login = CONSTANTS::cLOGIN.c_str();
	const char *pwd = CONSTANTS::cPASSWORD.c_str();
	const char *bd = CONSTANTS::cBD.c_str();

	if (mysql_init(&mysql) == nullptr)
	{
		// ���� ���������� �� ������� � ������� ��������� �� ������
		std::cerr << "Error: can't create MySQL-descriptor\n";
		return;
	}

	if (!mysql_real_connect(&mysql, host, login, pwd, bd, NULL, NULL, 0))
	{
		// ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
		showErrorBD("SQL_REQUEST::SQL::createMySQLConnect -> Error: can't connect to database", &mysql);
		return;
	};

	mysql_set_character_set(&mysql, "utf8");
}

// ���� �� ������� � ��
bool SQL_REQUEST::SQL::isConnectedBD()
{
	// status = 0 ������ ������� ����
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


	// ���������
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


// ���������� ������ � ������� IVR
void SQL_REQUEST::SQL::insertIVR(const char *phone, const char *time, std::string callerid)
{	
	if (!isConnectedBD()) {
		showErrorBD("SQL_REQUEST::SQL::insertIVR");
		return;
	}	
	
	// �������� ���� �� ����� ����� 	
	if (isExistIVRPhone(phone))	{ // ����� ����������, ��������� ������
		
		std::string id = std::to_string(getLastIDphone(phone));
		
		updateIVR(id.c_str(), phone, time);
		return;
	}
	else {		
		std::string query = "insert into ivr (phone,waiting_time,trunk) values ('" + std::string(phone) + "','" + std::string(time) + "','" + callerid + "')";
		
		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			showErrorBD("SQL_REQUEST::SQL::insertIVR -> Data (insertIVR) error -> query("+query+")", &this->mysql);
		}	
	}	

	mysql_close(&this->mysql);
}

// ���������� �� ����� ��� ����� � ������� IVR
bool SQL_REQUEST::SQL::isExistIVRPhone(const char *phone)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::isExistIVRPhone");
		return true;
	}
	
	const std::string query = "select count(phone) from ivr where phone = '" 
							  + std::string(phone) +"' and  date_time > '"
							  + getCurrentDateTimeAfterMinutes(2)+"' and to_queue = '0' order by date_time desc";

	if (mysql_query(&this->mysql, query.c_str() ) != 0)	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::isExistIVRPhone -> query(" + query + ")", &this->mysql);
		return true;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);	
	mysql_free_result(result);	


	return ( std::stoi(row[0]) == 0 ? false : true);	
}

// ��������� ���������� ID �����������
int SQL_REQUEST::SQL::getLastIDphone(const char *phone)
{	
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getLastIDphone");
		return -1;
	}

	const std::string query = "select id from ivr where phone = "
		+ std::string(phone) + " and date_time > '"
		+ getCurrentStartDay() + "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ��� ������		
		showErrorBD("SQL_REQUEST::SQL::getLastIDphone -> query(" + query + ")", &this->mysql);
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);	

	return std::stoi(row[0]);
}

// ���������� ������ � ������� IVR
void SQL_REQUEST::SQL::updateIVR(const char *id,const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateIVR");
		return;
	}

	std::string query = "update ivr set waiting_time = '" + std::string(time) + "' where phone = '" + std::string(phone) + "' and id ='"+std::string(id)+"'";
	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL_REQUEST::SQL::updateIVR -> Data (updateIVR) error -> query(" + query + ")",&this->mysql);
	};
	

	mysql_close(&this->mysql);
}

// ���������� ������ � ������� QUEUE
void SQL_REQUEST::SQL::insertQUEUE(const char *queue, const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::insertQUEUE");
		return;
	}	


	// �������� ���� �� ����� ����� 	
	if (isExistQUEUE(queue,phone))
	{ // ����� ����������, ��������� ������
	
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
			showErrorBD("SQL_REQUEST::SQL::insertQUEUE -> Data (insertQUEUE) error -> query(" + query + ")", &this->mysql);
		}		
	}

	mysql_close(&this->mysql);

}

// ���������� �� ����� ��� ����� � ������� QUEUE
bool SQL_REQUEST::SQL::isExistQUEUE(const char *queue, const char *phone)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::isExistQUEUE");
		return true;
	}	

	{ // ��� ����� ���� ���������!!!!
		// �������� �� �����������, ����� ��� ��� ����������� ����� ���� ��� ���������� ���	
		const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
								  +"' and phone = '" + std::string(phone) + "'"
								  + " and date_time > '" + getCurrentDateTimeAfterMinutes(30) + "'"
								  + " and answered = '1' and fail = '0' and sip < >'-1'"
								  + " and hash is not NULL order by date_time desc limit 1";

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			// ������ ������� ��� ���� ������		
			showErrorBD("SQL_REQUEST::SQL::isExistQUEUE -> query(" + query + ")", &this->mysql);
			return true;
		}
		// ���������
		MYSQL_RES *result = mysql_store_result(&this->mysql);
		MYSQL_ROW row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (std::stoi(row[0]) >= 1)
		{
			return false;	// ���� ���� ������, ������ ��������� ������
		}

	}



	// ���������� ��������� ������� ��������	
	const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
		+ "' and phone = '" + std::string(phone) + "'"
		+ " and date_time > '" + getCurrentDateTimeAfterMinutes(30) + "'"
		+ " and answered ='1' and fail='0' and sip<>'-1' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::isExistQUEUE -> query(" + query + ")", &this->mysql);
		return true;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	if (std::stoi(row[0]) >= 1)
	{
		return true;
	}
	else {
		// ��������� ����� � ������� ������ ��������� ������
		const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
			+ "' and phone = '" + std::string(phone) + "'"
			+ " and date_time > '" + getCurrentDateTimeAfterMinutes(30) + "'" //��� ���� ��, �� ����� �� ������������� ��������� 15 ���
			//+ " and date_time > '" + getCurrentDateTime() + "'"
			+ " and answered ='0' and fail='0' order by date_time desc limit 1";


		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			// ������ ������� ��� ���� ������		
			showErrorBD("SQL_REQUEST::SQL::isExistQUEUE -> query(" + query + ")", &this->mysql);
			return true;
		}

		// ���������
		MYSQL_RES *result = mysql_store_result(&this->mysql);
		MYSQL_ROW row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (std::stoi(row[0]) >= 1)
		{
			return true; 
		}
		else {
		
			// ��� ��������� ��������� ����������
			const std::string query = "select count(phone) from queue where number_queue = '" + std::string(queue)
				+ "' and phone = '" + std::string(phone) + "'"
				+ " and date_time > '" + getCurrentDateTimeAfterMinutes(30) + "'" //��� ���� ��, �� ����� �� ������������� ��������� 15 ���
				//+ " and date_time > '" + getCurrentDateTime() + "'"
				+ " and answered ='0' and fail='1' order by date_time desc limit 1";


			if (mysql_query(&this->mysql, query.c_str()) != 0)
			{
				// ������ ������� ��� ���� ������		
				showErrorBD("SQL_REQUEST::SQL::isExistQUEUE -> query(" + query + ")", &this->mysql);
				return true;
			}

			// ���������
			MYSQL_RES *result = mysql_store_result(&this->mysql);
			MYSQL_ROW row = mysql_fetch_row(result);
			mysql_free_result(result);

			if (std::stoi(row[0]) >= 1)
			{
				return false; // ������� ��� ����� �����!!!
			}

			return (std::stoi(row[0]) == 0 ? false : true);
		
		}
		
	}
	
}

// ���������� ������ � ������� QUEUE
void SQL_REQUEST::SQL::updateQUEUE(const char *id, const char *phone, const char *time)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE");
		return;
	}

	std::string query = "update queue set waiting_time = '" + std::string(time) + "' where phone = '" + std::string(phone) + "' and id ='" + std::string(id) + "'";;

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE -> Data (updateQUEUE) error -> query(" + query + ")", &this->mysql);
	}

	mysql_close(&this->mysql);
}

// ��������� ���������� ID �����������
int SQL_REQUEST::SQL::getLastIDQUEUE(const char *phone)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getLastIDQUEUE");
		return -1;
	}

	const std::string query = "select id from queue where phone = "
		+ std::string(phone) + " and date_time > '"
		+ getCurrentStartDay() + "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ��� ������		
		showErrorBD("SQL_REQUEST::SQL::getLastIDQUEUE -> query("+query+")",&this->mysql);
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);	

	return std::stoi(row[0]);
}

// ���������� ������ ������� QUEUE � ��� � ��� ������ ������������� ��������
void SQL_REQUEST::SQL::updateQUEUE_SIP(const char *phone, const char *sip, const char *talk_time)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_SIP");
		return;
	}

	// �������� ���� �� ����� ����� 	
	if (isExistQUEUE_SIP(phone))
	{ // ����� ����������, ��������� ������
		std::string id = std::to_string(getLastIDQUEUE(phone));

		std::string query = "update queue set sip = '" + std::string(sip) + "', talk_time = '"+ getTalkTime(talk_time) + "', answered ='1' where phone = '" + std::string(phone) + "' and id ='" + std::string(id) + "'";

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			showErrorBD("SQL_REQUEST::SQL::updateQUEUE_SIP -> Data (updateQUEUE_SIP) error -> query("+query+")", &this->mysql);
		};

		mysql_close(&this->mysql);		
	}	
}

// ���������� �� ����� ����� � ������� QUEUE ����� �������� sip ��������� ������� � �������� �����
bool SQL_REQUEST::SQL::isExistQUEUE_SIP(const char *phone)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::isExistQUEUE_SIP");
		return true;
	}
	
	const std::string query = "select count(phone) from queue where phone = '" + std::string(phone)
							+ "' and date_time > '" + getCurrentStartDay() 
							+ "' order by date_time desc limit 1";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::isExistQUEUE_SIP -> query(" + query + ")", &this->mysql);
		return true;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	return (std::stoi(row[0]) == 0 ? false : true);
}

//���������� ������ ����� ������ �� �������� ����� �������
void SQL_REQUEST::SQL::updateQUEUE_fail(const std::vector<QUEUE::Pacients> &pacient_list)
{
	
	// ������ ������� ������ ������� �� �� ����� ������� ��� ����������
	std::string list_phone;
	
	for (const auto &list : pacient_list) {
		
		if (list_phone.empty()) {
			list_phone = "'"+list.phone+"'";
		}
		else {
			list_phone = list_phone + ",'" + list.phone + "'";
		}		
	}	

	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_fail");
		return;
	}

	// ��������� ������
	std::string query = "update queue set fail = '1' where date_time > '" + getCurrentStartDay() + "' and answered = '0'"
		+ " and sip = '-1' and phone not in ("+ list_phone +")";

	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_fail -> Data (updateQUEUE_fail) error -> query(" + query + ")", &this->mysql);
	};

	mysql_close(&this->mysql);
}

// ���������� ������ ����� ������ �� �������� ����� �������
void SQL_REQUEST::SQL::updateQUEUE_fail()
{
	// ��������� ������
	std::string query = "update queue set fail = '1' where date_time > '" + getCurrentDateTimeAfter20hours() + "' and answered = '0' and sip = '-1' ";

	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_fail");
		return;
	}

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_fail -> Data (updateQUEUE_fail) error -> query(" + query + ")", &this->mysql);
	};

	mysql_close(&this->mysql);
}

// ���������� ������ ����� � ��� ������ �� IVR ����� � �������
void SQL_REQUEST::SQL::updateIVR_to_queue(const std::vector<QUEUE::Pacients> &pacient_list)
{
	// ������ ������� ������ ������� ����� ������� ��� ����������
	std::string list_phone;

	for (const auto &list : pacient_list)
	{
		if (list_phone.empty())
		{
			list_phone = "'" + list.phone + "'";
		}
		else
		{
			list_phone = list_phone + ",'" + list.phone + "'";
		}
	}

	// ��������� ������
	std::string query = "update ivr set to_queue = '1' where date_time > '" + getCurrentDateTimeAfterMinutes(5)+"' and phone in(" + list_phone + ") and to_queue = '0'";

	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateIVR_to_queue");
		return;
	}

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL_REQUEST::SQL::updateIVR_to_queue -> Data (updateIVR_to_queue) error -> query(" + query + ")", &this->mysql);
	};

	mysql_close(&this->mysql);
}


// �������� ���� �� ������ ������� ��������� ����� 20:00
bool SQL_REQUEST::SQL::isExistQueueAfter20hours()
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::isExistQueueAfter20hours");
		return true;
	}

	const std::string query = "select count(phone) from queue where date_time > '"
		+ getCurrentDateTimeAfter20hours() + "' and sip = '-1' and answered = '0' and fail = '0' order by date_time desc ";

	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::isExistQueueAfter20hours");
		return true;
	}
	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::isExistQueueAfter20hours -> query(" + query + ")", &this->mysql);
		return true;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);	

	mysql_close(&this->mysql); // �������! 01.06.2024

	return (std::stoi(row[0]) == 0 ? false : true);

}

// ���������� ���� hash ����� ������� ����������
void SQL_REQUEST::SQL::updateQUEUE_hash(const std::vector<QUEUE::Pacients> &pacient_list)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_hash");
		return;
	}	

	// ������ ������� ������ ������� ����� ������� ��� ����������
	std::string list_phone;

	for (const auto &list : pacient_list)
	{
		if (list_phone.empty())
		{
			list_phone = "'" + list.phone + "'";
		}
		else
		{
			list_phone = list_phone + ",'" + list.phone + "'";
		}
	} 

	QUEUE::QueueBD queuebd;
	
	
	const std::string query = "select id,phone,date_time from queue where date_time > '"
		+ getCurrentStartDay() + "' and answered = '1' and fail = '0' and hash is NULL and phone not in("+ list_phone+")";

	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::updateQUEUE_hash -> query(" + query + ")", &this->mysql);
		return;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		QUEUE::BD bd;
		for (int i = 0; i < mysql_num_fields(result); i++)
		{
			
			if (i == 0) {
				bd.id = row[i];
			}
			else if (i == 1) {
				bd.phone = row[i];
			}
			else if (i == 2) {
				bd.date_time = row[i];
			}			
		}

		bd.hash = std::hash<std::string>()(bd.phone+"_"+bd.date_time);
		queuebd.list.push_back(bd);		
	}	
	
	mysql_free_result(result);
	
	// ���������
	for (const auto &list : queuebd.list)
	{

		std::string query = "update queue set hash = '" + std::to_string(list.hash)
			+ "' where id ='" + list.id
			+ "' and phone ='" + list.phone
			+ "' and date_time = '" + list.date_time + "'";

		if (!isConnectedBD())
		{
			showErrorBD("SQL_REQUEST::SQL::updateQUEUE_hash");
			return;
		}

		if (mysql_query(&this->mysql, query.c_str()) != 0)
		{
			showErrorBD("SQL_REQUEST::SQL::updateQUEUE_hash -> Data (updateQUEUE_hash) error -> query(" + query + ")", &this->mysql);
		};

	};
	mysql_close(&this->mysql); 
}

// ������� ����� ��������� �� ����� IVR
int SQL_REQUEST::SQL::getIVR_totalCalls()
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getIVR_totalCalls()");
		return 0;
	}

	const std::string query = "select count(phone) from ivr where date_time > '" + getCurrentStartDay() + "'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::getIVR_totalCalls -> query(" + query + ")", &this->mysql);
		return 0;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	mysql_close(&this->mysql); // ��� ��������?

	return std::stoi(row[0]);
}

// ������� ����� ��������� �� ����� IVR (����� �� trunk)
int SQL_REQUEST::SQL::getIVR_totalCalls(const IVR::CallerID &trunk)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getIVR_totalCalls(1param)");
		return 0;
	}

	const std::string query = "select count(phone) from ivr where trunk ='" + IVR::getCallerID(trunk) + "'  and date_time > '" + getCurrentStartDay() + "'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::getIVR_totalCalls(1param) -> query(" + query + ")", &this->mysql);
		return 0;
	}

	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	mysql_close(&this->mysql); // ��� ��������?

	return std::stoi(row[0]);;
}

// ������� ����� �������� � ������� �����������
int SQL_REQUEST::SQL::getQUEUE_Calls(bool answered)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getQUEUE_Calls(1 param)");
		return 0;
	}
	
{
	std::string query;
		switch (answered)
	{
		case(true):
		{
			query = "select count(phone) from queue where date_time > '" + getCurrentStartDay() + "' and answered = '1'";
			break;
		}
		case(false):
		{
			query = "select count(phone) from queue where date_time > '" + getCurrentStartDay() + "' and answered = '0'";
			break;
		}
	}
	
	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::getQUEUE_Calls(1param) -> query(" + query + ")", &this->mysql);
		return 0;
	}
}
	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	mysql_close(&this->mysql); // ��� ��������?

	return std::stoi(row[0]);
}

// ������� ����� ���� � �������
int SQL_REQUEST::SQL::getQUEUE_Calls()
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL_REQUEST::SQL::getQUEUE_Calls");
		return 0;
	}		
	 const std::string query = "select count(phone) from queue where date_time > '" + getCurrentStartDay()+"'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ������ ������� ��� ���� ������		
		showErrorBD("SQL_REQUEST::SQL::getQUEUE_Calls -> query(" + query + ")", &this->mysql);
		return 0;
	}
	
	// ���������
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	mysql_close(&this->mysql); // ��� ��������?

	return std::stoi(row[0]);
}
