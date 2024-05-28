//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 15.05.2024				//
//		���������� ������� �� �������� � ������ 	//
//													//	
//////////////////////////////////////////////////////

#include <string>
#include "Constants.h"
//#include <mysql/mysql.h>

#ifndef INTERNALFUNCTION_H
#define INTERNALFUNCTION_H

std::string phoneParsing(std::string &phone);					// ������� ������ �������� � ���������� ���
void getIVR();												// ������� + �������� ������� IVR
void getQueue(void);											// ������� + �������� ������� �������
void getActiveSip(void);										// ������� + �������� ��� � ��� �������������
std::string getNumberQueue(CONSTANTS::AsteriskQueue queue);		// ��������� ������ �������
std::string getTalkTime(std::string talk);						// ������� �������� �� ��� -> 00:00:00

// ������� ������ �� �������� (������ ���-�����-���� 00:00:00 )
std::string getCurrentDateTime();							// ������� ����� 
std::string getCurrentStartDay();							// ������� ������ ���
std::string getCurrentDateTimeAfterMinutes(int minutes);			// ������� ����� - 3 ������ 

// ���������� // ���� ��� ������, ����� ����� � ��������� ����� �������
void getStatistics();

#endif //INTERNALFUNCTION_H