//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//		внутренние функции не вошедшие в  классы	//
//													//	
//////////////////////////////////////////////////////

#include <string>
#include "Constants.h"

#ifndef INTERNALFUNCTION_H
#define INTERNALFUNCTION_H

std::string phoneParsing(std::string &phone);					// парсинг номера телефона в нормальный вид
void getIVR(void);												// создать + получить текущий IVR
void getQueue(void);											// создать + получить текущую очередь
void getActiveSip(void);										// создать + получить кто с кем разговаривает
std::string getNumberQueue(CONSTANTS::AsteriskQueue queue);		// получение номера очереди
std::string getTalkTime(std::string talk);						// перевод временни из сек -> 00:00:00

//from MySQL
bool connectBD();								// подключение к БД



#endif //INTERNALFUNCTION_H