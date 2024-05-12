#include "InternalFunction.h"
#include "Constants.h"
#include "IVR.h"
#include "Queue.h"
#include "ActiveSip.h"
#include <cmath>
#include "mysql/mysql.h"


// подключение к БД MySQL
bool connectBD() {
	MYSQL mysql;
	
	//mysql = mysql_init(nullptr);
	
	const char *host = CONSTANTS::cHOST.c_str();
	const char *login = CONSTANTS::cLOGIN.c_str();
	const char *pwd = CONSTANTS::cPASSWORD.c_str();
	const char *bd = CONSTANTS::cBD.c_str();

		
	// Получаем дескриптор соединения
		mysql_init(&mysql);		 
		if (&mysql == nullptr)
		{
		// Если дескриптор не получен — выводим сообщение об ошибке
			std::cout << "Error: can't create MySQL-descriptor\n";
			return false;
		}
	
		// Подключаемся к серверу
		//if (!mysql_real_connect(&mysql,host,login,pwd,bd,NULL, NULL, 0))
		//{
		//	// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		//	std::cout << "Error: can't connect to database " << mysql_error(&mysql) << "\n";
		//	return false;
		//}
		//else
		//{
		//	// Если соединение успешно установлено выводим фразу — "Success!"
		//	return true;
		//}
}

// парсинг номера телефона в нормальный вид
std::string phoneParsing(std::string &phone)
{
	if (phone.length() < 6)
	{
		return "null";	// для номеров которые не сотовые и не городские
	}
	else if (phone.length() == 10)
	{
		return "+7" + phone;
	}
	else if (phone.length() == 11)
	{
		return "+" + phone;
	}
	else
	{
		return "null";	// ничего не нашли возращаем null
	}
};


// создать + получить текущий IVR
void getIVR(void)
{   
	if (!CONSTANTS::DEBUG_MODE) {
		system(CONSTANTS::cIVRResponse.c_str());
	};
	  

    // разбираем
    IVR::Parsing ivr(CONSTANTS::cIVRName.c_str());
    ivr.show();     
}

// создать + получить текущую очередь
void getQueue(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cQueueResponse.c_str());
	}

    QUEUE::Parsing queue(CONSTANTS::cQueueName.c_str());

    queue.show();
}

// создать + получить кто с кем разговаривает
void getActiveSip(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cActiveSipResponse.c_str());
	}

    ACTIVE_SIP::Parsing sip(CONSTANTS::cActiveSipName.c_str());

	if (sip.isExistList()) { 
		sip.show(); 
	}
	
}

// получение номера очереди
std::string getNumberQueue(CONSTANTS::AsteriskQueue queue)
{
	switch (queue)
	{
		case CONSTANTS::main: {
			return "5000";
			break;
		}			
		case CONSTANTS::lukoil: {
			return "5050";
			break;
		}			
		default: {
			return "5000";
			break;
		}			
	}
}

// перевод общего кол-ва секунда в 00:00:00 формат
std::string getTalkTime(std::string talk)
{
	const unsigned int daysCount	= 24 * 3600;
	const unsigned short hourCount	= 3600;
	const unsigned short minCount	= 60;

	std::string resultat;

	int talk_time = std::stoi(talk);

	int days, hour, min,sec;
	std::string shour, smin, ssec;

	days = hour = min = sec = 0;

	days = static_cast<int>(std::floor((talk_time / daysCount)));		
	hour = static_cast<int>(std::floor(((talk_time - (days * daysCount)) / hourCount)));	
	min = static_cast<int>(std::floor(((talk_time - ((days * daysCount) + (hour * hourCount) )) / minCount)));
	sec = static_cast<int>(std::floor((talk_time - ((days * daysCount) + (hour * hourCount) + (min * minCount)))));
		
	(hour < 10) ? shour = "0" + std::to_string(hour) : shour = std::to_string(hour);
	(min < 10) ? smin = "0" + std::to_string(min) : smin = std::to_string(min);
	(sec < 10) ? ssec = "0" + std::to_string(sec) : ssec = std::to_string(sec);
	
	resultat = shour + ":" + smin + ":" + ssec;	
	return ((days == 0) ? resultat : resultat += std::to_string(days)+"d "+ resultat);	
}


