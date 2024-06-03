//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 01.06.2024				//
//		внутренние функции не вошедшие в классы 	//
//													//	
//////////////////////////////////////////////////////

#include <string>
#include "Constants.h"
#include "SQLRequest.h"
#include "Queue.h"
#include <mysql/mysql.h>


#ifndef INTERNALFUNCTION_H
#define INTERNALFUNCTION_H

std::string phoneParsing(std::string &phone);					// парсинг номера телефона в нормальный вид
void getIVR();												    // создать + получить текущий IVR
void getQueue(void);											// создать + получить текущую очередь
void getActiveSip(void);										// создать + получить кто с кем разговаривает
std::string getNumberQueue(CONSTANTS::AsteriskQueue queue);		// получение номера очереди
std::string getTalkTime(std::string talk);						// перевод временни из сек -> 00:00:00

// функции работы со временем (формат год-мес€ц-день 00:00:00 )
std::string getCurrentDateTime();							// текущее врем€ 
std::string getCurrentStartDay();							// текущее начало дн€
std::string getCurrentDateTimeAfterMinutes(int minutes);	// текущее врем€ -(ћ»Ќ”—) указанна€ минута 
std::string getCurrentDateTimeAfter20hours();				// текущее врем€ после 20:00 

// статистика // пока без класса, может потом в отдельный класс сделать
void getStatistics();

void showErrorBD(const std::string str); // отображжение инфо что не возможно подключитьс€ к бд
void showErrorBD(const std::string str, MYSQL *mysql); // отображение инфо что пошла кака€ то ошибка


#endif //INTERNALFUNCTION_H