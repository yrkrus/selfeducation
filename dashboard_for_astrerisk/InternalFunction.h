//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 13.05.2024				//
//		внутренние функции не вошедшие в классы 	//
//													//	
//////////////////////////////////////////////////////

#include <string>
#include "Constants.h"
//#include <mysql/mysql.h>

#ifndef INTERNALFUNCTION_H
#define INTERNALFUNCTION_H

std::string phoneParsing(std::string &phone);					// парсинг номера телефона в нормальный вид
void getIVR();												// создать + получить текущий IVR
void getQueue(void);											// создать + получить текущую очередь
void getActiveSip(void);										// создать + получить кто с кем разговаривает
std::string getNumberQueue(CONSTANTS::AsteriskQueue queue);		// получение номера очереди
std::string getTalkTime(std::string talk);						// перевод временни из сек -> 00:00:00

// функции работы со временем (формат год-месяц-день 00:00:00 )
std::string getCurrentDateTime();							// текущее время 
std::string getCurrentStartDay();							// текущее начало дня
std::string getCurretDateTimeAfterTreeMinutes();				// текущее время - 3 минута 


#endif //INTERNALFUNCTION_H