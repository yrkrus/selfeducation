//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 16.05.2024				//
//			    константные значения				//
//													//	
//////////////////////////////////////////////////////

#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CONSTANTS 
{
    // DEBUG MODE 
    static bool DEBUG_MODE{ false };
    // WKroot#791
   
// для будущей интеграции с телефонами!!!    
/*   
    // перезагрузка
    https://admin:asz741@10.34.42.47/servlet?key=Reboot
    // набор номера
    http://admin:asz741@10.34.42.47/number=xxx&outgoing_uri=y 	Набор номера xxx
    // завершить вызов
    http://admin:asz741@10.34.42.47/servlet?key=CALLEND 
    // скриншот
    https://admin:asz741@10.34.42.47/servlet?m=mod_action&command=screenshot
    // регистрация
    https://admin:asz741@10.34.42.47/servlet?phonecfg=set[&account.1.label=64197][&account.1.display_name=64197][&account.1.auth_name=64197][&account.1.user_name=64197][&account.1.password=1240]
 	
	Лейбл 			 = &account.1.label=XXX
	Отображаемое имя = &account.1.display_name=XXX
	Имя регистрации  = &account.1.auth_name=XXX
	Имя пользователя = &account.1.user_name=XXX
	Пароль 			 = &account.1.password=XXX
    
    */ 


 // версия ядра
 static std::string core_version = {"CORE DASHBOARD | version 2.5 bild 20240607 "};


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
const std::string cIVRCommands	= "Playback|lukoil|ivr-3";
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
static std::string cHOST       = "10.34.222.19";
static std::string cBD         = "dashboard";
static std::string cLOGIN      = "zabbix";
static std::string cPASSWORD   = "UFGq4kZMNIMwxTzV";

};



#endif //CONSTANTS_H
