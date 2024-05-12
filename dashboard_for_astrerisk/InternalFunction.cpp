#include "InternalFunction.h"
#include "Constants.h"
#include "IVR.h"
#include "Queue.h"
#include "ActiveSip.h"
#include <cmath>
#include "mysql/mysql.h"


// ����������� � �� MySQL
bool connectBD() {
	MYSQL mysql;
	
	//mysql = mysql_init(nullptr);
	
	const char *host = CONSTANTS::cHOST.c_str();
	const char *login = CONSTANTS::cLOGIN.c_str();
	const char *pwd = CONSTANTS::cPASSWORD.c_str();
	const char *bd = CONSTANTS::cBD.c_str();

		
	// �������� ���������� ����������
		mysql_init(&mysql);		 
		if (&mysql == nullptr)
		{
		// ���� ���������� �� ������� � ������� ��������� �� ������
			std::cout << "Error: can't create MySQL-descriptor\n";
			return false;
		}
	
		// ������������ � �������
		//if (!mysql_real_connect(&mysql,host,login,pwd,bd,NULL, NULL, 0))
		//{
		//	// ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
		//	std::cout << "Error: can't connect to database " << mysql_error(&mysql) << "\n";
		//	return false;
		//}
		//else
		//{
		//	// ���� ���������� ������� ����������� ������� ����� � "Success!"
		//	return true;
		//}
}

// ������� ������ �������� � ���������� ���
std::string phoneParsing(std::string &phone)
{
	if (phone.length() < 6)
	{
		return "null";	// ��� ������� ������� �� ������� � �� ���������
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
		return "null";	// ������ �� ����� ��������� null
	}
};


// ������� + �������� ������� IVR
void getIVR(void)
{   
	if (!CONSTANTS::DEBUG_MODE) {
		system(CONSTANTS::cIVRResponse.c_str());
	};
	  

    // ���������
    IVR::Parsing ivr(CONSTANTS::cIVRName.c_str());
    ivr.show();     
}

// ������� + �������� ������� �������
void getQueue(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cQueueResponse.c_str());
	}

    QUEUE::Parsing queue(CONSTANTS::cQueueName.c_str());

    queue.show();
}

// ������� + �������� ��� � ��� �������������
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

// ��������� ������ �������
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

// ������� ������ ���-�� ������� � 00:00:00 ������
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


