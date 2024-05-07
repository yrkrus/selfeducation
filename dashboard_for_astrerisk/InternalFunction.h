//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 07.05.2024				//
//		внутренние функции не вошедшие в  классы	//
//													//	
//////////////////////////////////////////////////////

#include <string>

#ifndef INTERNALFUNCTION_H
#define INTERNALFUNCTION_H

std::string phoneParsing(std::string &phone);	// парсинг номера телефона в нормальный вид
void getIVR(void);								// создать + получить текущий IVR
void getQueue(void);							// создать + получить текущую очередь
void getActiveSip(void);						// создать + получить кто с кем разговаривает


#endif //INTERNALFUNCTION_H