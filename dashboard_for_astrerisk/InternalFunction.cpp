#include "InternalFunction.h"
#include "Constants.h"
#include "IVR.h"
#include "Queue.h"
#include "ActiveSip.h"
#include <cmath>

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

    //if (ivr.isExistList()) {
    //    // добавляем в mysql
    //    ivr.show();
    //}   
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

std::string getTalkTime(std::string talk)
{
	
	int talk_time = std::stoi(talk);	
	int days{ 0 }, hour{ 0 }, min{ 0 }, sec{ 0 };
	days = static_cast<int>(std::floor((talk_time / (24 * 3600))));
	hour = static_cast<int>(std::floor((talk_time / 3600)));
	min = static_cast<int>(std::floor((talk_time / 60)));
	
	

			//days: = Trunc(CurrentSec / (24 * 3600));
			//	dec(CurrentSec, days * 24 * 3600);

			//hour: = Trunc(CurrentSec / 3600);
			//hourtmp: = IntToStr(hour);
			//	if Length(hourtmp) = 1 then hourtmp : = '0' + hourtmp;
			//	dec(CurrentSec, hour * 3600);


			//min: = Trunc(CurrentSec / 60);
			//mintmp: = IntToStr(min);
			//	if Length(mintmp) = 1 then mintmp : = '0' + mintmp;
			//	dec(CurrentSec, min * 60);

			//sec: = CurrentSec;
			//sectmp: = IntToStr(sec);
			//	if Length(sectmp) = 1 then sectmp : = '0' + sectmp;

	//if days < >0 then WorkingHours : = IntToStr(days) + ' дн ' + hourtmp + ':' + mintmp + ':' + sectmp
	//else
	//	begin
	//	if hour < >0 then  WorkingHours : = hourtmp + ':' + mintmp + ':' + sectmp
	//	else
	//		begin
	//		if min < >0 then WorkingHours : = '00:' + mintmp + ':' + sectmp
	//		else WorkingHours: = '00:00:' + sectmp;
	//end;
	//end;

	return "00:00:00";
}




