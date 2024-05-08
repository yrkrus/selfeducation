//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
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


// asterisk очереди  
enum AsteriskQueue
{
    main,       // основная очередь     5000
    lukoil,     // очередь лукой        5050
    COUNT = 2,
};



// for IVR
const std::string cIVRCommands	= "Playback|lukoil";
const std::string cIVRName		= "IVR.txt";
const std::string cIVRResponse	= "asterisk -rx \"core show channels verbose\" | grep -E \"" + cIVRCommands + "\" > " + cIVRName;

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
};



#endif //CONSTANTS_H
