#include "InternalFunction.h"
#include "Constants.h"
#include "IVR.h"
#include "Queue.h"
#include "ActiveSip.h"
#include <cmath>
#include <time.h>
#include <chrono>


//#ifdef _WIN32
//#include "mysql/mysql.h"
//#elif __linux__
#include <mysql/mysql.h>
//#endif



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
void getIVR()
{   
	if (!CONSTANTS::DEBUG_MODE) {
		system(CONSTANTS::cIVRResponse.c_str());
	};	  

    // разбираем
    IVR::Parsing ivr(CONSTANTS::cIVRName.c_str());
	if (ivr.isExistList()) {
		ivr.show();
		ivr.insertData();
	}
}

// создать + получить текущую очередь
void getQueue(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cQueueResponse.c_str());
	}

    QUEUE::Parsing queue(CONSTANTS::cQueueName.c_str());
    
	if (queue.isExistList()) {
		queue.show();
		queue.insertData();
	}	
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
		sip.updateData();
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

// текущее время 
std::string getCurrentDateTime()
{	
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	struct std::tm *now_tm = std::localtime(&now_c);		

	//формат год-месяц-день 00:00:00
	std::string year = std::to_string((now_tm->tm_year + 1900));

	std::string mon = std::to_string((now_tm->tm_mon + 1));
	if (mon.length() == 1) { mon = "0" + mon; }

	std::string day = std::to_string(now_tm->tm_mday);
	if (day.length() == 1) { day = "0" + day; }

	std::string hour = std::to_string(now_tm->tm_hour);
	if (hour.length() == 1) { hour = "0" + hour; }

	std::string min = std::to_string(now_tm->tm_min);
	if (min.length() == 1) { min = "0" + min; }

	std::string sec = std::to_string(now_tm->tm_sec);
	if (sec.length() == 1) { sec = "0" + sec; }
		
	return year + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec;
}

// текущее начало дня
std::string getCurrentStartDay()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	struct std::tm *now_tm = std::localtime(&now_c);

	//формат год-месяц-день 00:00:00
	std::string year = std::to_string((now_tm->tm_year + 1900));

	std::string mon = std::to_string((now_tm->tm_mon + 1));
	if (mon.length() == 1) { mon = "0" + mon; }

	std::string day = std::to_string(now_tm->tm_mday);
	if (day.length() == 1) { day = "0" + day; }	

	return year + "-" + mon + "-" + day + " 00:00:00" ;
}

// текущее время - 2 минута 
std::string getCurretDateTimeAfterTreeMinutes()
{
	auto now = std::chrono::system_clock::now();
	auto minutes = std::chrono::minutes(3);

	std::time_t now_c = std::chrono::system_clock::to_time_t(now-minutes);
	struct std::tm *now_tm = std::localtime(&now_c);

	//формат год-месяц-день 00:00:00
	std::string year = std::to_string((now_tm->tm_year + 1900));

	std::string mon = std::to_string((now_tm->tm_mon + 1));
	if (mon.length() == 1) { mon = "0" + mon; }

	std::string day = std::to_string(now_tm->tm_mday);
	if (day.length() == 1) { day = "0" + day; }	

	std::string hour = std::to_string(now_tm->tm_hour);
	if (hour.length() == 1) { hour = "0" + hour; }

	std::string min = std::to_string(now_tm->tm_min);
	if (min.length() == 1) { min = "0" + min; }

	std::string sec = std::to_string(now_tm->tm_sec);
	if (sec.length() == 1) { sec = "0" + sec; }

	return year + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec;
}


