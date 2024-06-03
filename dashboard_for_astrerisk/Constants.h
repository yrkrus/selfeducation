//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 16.05.2024				//
//			    ����������� ��������				//
//													//	
//////////////////////////////////////////////////////

#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CONSTANTS 
{
// debug 
    static bool DEBUG_MODE{ true };
// WKroot#791
       

// asterisk �������  
enum AsteriskQueue
{
    main,       // �������� �������     5000
    lukoil,     // ������� �����        5050
    COUNT = 2,
};


// ���������
// IVREXT - ���� �� ������� ������������
// ����� IVREXT -> Spasibo - ���� �� ������� ��� �������

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
static std::string cHOST       = "10.34.222.19";
static std::string cBD         = "dashboard";
static std::string cLOGIN      = "zabbix";
static std::string cPASSWORD   = "UFGq4kZMNIMwxTzV";

};



#endif //CONSTANTS_H
