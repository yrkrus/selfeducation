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
const bool DEBUG_MODE{ true };

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
const std::string cActiveSipName	 = "ActiveSip.txt";
const std::string cActiveSipResponse = "asterisk -rx \"core show channels concise\" > " + cActiveSipName;

};



#endif //CONSTANTS_H
