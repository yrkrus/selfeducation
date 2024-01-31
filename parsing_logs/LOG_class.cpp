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

extern const string LOG_FILES; // константа из constants.cpp


Logging::Logging()
{
	namespace fs = std::filesystem;
	
	// тут проверяем есть ли файл лога и если его нет - создаем
	if (!fs::exists(LOG_FILES)) {
		// создаем файл
		ofstream file(LOG_FILES);		
	}	
}

Logging::~Logging()
{
	// закрываем файл который был в записи
}

void Logging::setLog(string message, bool isError)
{
	
	// текущее время
	SYSTEMTIME t;
	GetLocalTime(&t);	
	string datetime,Day,Month,Hour,Minute,Second;

	// добавим 0 т.к. при выводе он пропадает
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
	file.open(LOG_FILES, std::ios::app); // открываем на дозапись файла
	if (!isError) {
		file << datetime + " <font color = 'black'> " + message << "</font><br>";
	}
	else {
		file << datetime + " <font color = 'red'> " + message << "</font><br>";
	}
	
	file.close();		
}
