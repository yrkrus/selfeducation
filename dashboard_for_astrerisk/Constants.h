//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 15.05.2024				//
//			    константные значения				//
//													//	
//////////////////////////////////////////////////////

#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CONSTANTS 
{
// debug 
    const bool DEBUG_MODE{ false };
// WKroot#791


/*ТЕКУЩИЕ ОШИБКИ*/
/*
1. при работе getIVR, попадают звонки больше >00:00:40 разобраться

*/

// asterisk очереди  
enum AsteriskQueue
{
    main,       // основная очередь     5000
    lukoil,     // очередь лукой        5050
    COUNT = 2,
};


// шпаргалка
// IVREXT - уход на оцените обслуживание
// после IVREXT -> Spasibo - уход на спасибо что оценили

// for IVR
const std::string cIVRCommands	= "Playback|lukoil";
const std::string cIVRCommandsEx1 = "IVREXT";
const std::string cIVRCommandsEx2 = "Spasibo";
const std::string cIVRName		= "IVR.txt";
const std::string cIVRResponse	= "asterisk -rx \"core show channels verbose\" | grep -E \"" + cIVRCommands + "\" " + " | grep -v \"" + cIVRCommandsEx1 + "\" " + " | grep -v \"" + cIVRCommandsEx2 + "\" > " + cIVRName;


// for QUEUE
const std::string cQueueCommands	= "Queue";
const std::string cQueueCommandsEx	= "App";
const std::string cQueueName		= "Queue.txt";
const std::string cQueueResponse	= "asterisk -rx \"core show channels verbose\" | grep -E \"" + cQueueCommands + "\" " + " | grep -v \"" + cQueueCommandsEx + "\" > " + cQueueName;

// for ActiveSIP
const std::string cActiveSipName				= "ActiveSip.txt";
const std::string cActiveSipResponse			= "asterisk -rx \"core show channels concise\" > " + cActiveSipName;
const std::string cActiveSipOperatorsName		= "ActiveSipOperators.txt";
const std::string cActiveSipOperatorsResponse	= "asterisk -rx \"queue show %queue\" > " + cActiveSipOperatorsName;

//for MySQL Connect
const std::string cHOST       = "10.34.222.19";
const std::string cBD         = "dashboard";
const std::string cLOGIN      = "zabbix";
const std::string cPASSWORD   = "UFGq4kZMNIMwxTzV";

};



#endif //CONSTANTS_H
