#define _CRT_SECURE_NO_WARNINGS

#include "LOG_class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>

using std::cout;
using std::string;
using std::ofstream;
using std::string;
using std::endl;
using std::to_string;

extern const string LOG_FILES; // ��������� �� constants.cpp


Logging::Logging()
{
	namespace fs = std::filesystem;
	
	// ��� ��������� ���� �� ���� ���� � ���� ��� ��� - �������
	if (!fs::exists(LOG_FILES)) {
		// ������� ����
		ofstream file(LOG_FILES);		
	}	
}

Logging::~Logging()
{
	// ��������� ���� ������� ��� � ������
}

void Logging::setLog(string message, bool isError)
{
	
	// ������� �����
	SYSTEMTIME t;
	GetLocalTime(&t);	
	string datetime,Day,Month,Hour,Minute,Second;

	// ������� 0 �.�. ��� ������ �� ���������
	Day = to_string(t.wDay);
	if (Day.length() == 1) { Day = "0" + Day; }

	Month = to_string(t.wMonth);
	if (Month.length() == 1) { Month = "0" + Month; }

	Hour = to_string(t.wHour);
	if (Hour.length() == 1) { Hour = "0" + Hour; }

	Minute = to_string(t.wMinute);
	if (Minute.length() == 1) { Minute = "0" + Minute; }

	Second = to_string(t.wSecond);
	if (Second.length() == 1) { Second = "0" + Second; }

	datetime = Day + '.' + Month + '.' + to_string(t.wYear) + ' ' + Hour + ':' + Minute + ':' + Second;

	ofstream file; 
	file.open(LOG_FILES, std::ios::app); // ��������� �� �������� �����
	if (!isError) {
		file << datetime + " <font color = 'black'> " + message << "</font><br>";
	}
	else {
		file << datetime + " <font color = 'red'> " + message << "</font><br>";
	}
	
	file.close();		
}
