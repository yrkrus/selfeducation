#define _CRT_SECURE_NO_WARNINGS

#include "FIND_FILES_class.h"
#include "LOG_class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <format>
#include <iterator>
#include <exception>


// константы из constants.cpp
extern const string version_programm;
extern const unsigned short FILES_TTL;
extern const unsigned short FILES_ORIGINAL_TTL;

extern const string ANALIS_SERVICE;
extern const string MAILSERVER0;
extern const string MAILSERVER1;
extern const string MAILSERVER2;
extern const string MAILSERVER3;
extern const string REPL0;
extern const string REPL1;
extern const string REPL2;
extern const string REPL3;
extern const string REPL4;
extern const string REPL_MAIN0;
extern const string REPL_MAIN1;
extern const string REPL_MAIN2;
extern const string REPL_MAIN3;
extern const string REPL_MAIN4;
extern const string REPL_MAIN5;
extern const string REPL_MAIN6;
extern const string REPORTSERVER0;
extern const string REPORTSERVER1;
extern const string REPORTSERVER_WEB_LP0;
extern const string SMS0;
extern const string SYNC0;
extern const string LOG_FOLDER;



using std::cout;
using std::string;
using std::to_string;
using std::ofstream;
using std::ifstream;


// очистка консоли
void getClear()
{
	system("cls");
}

// инфо версии
void showInfoVersion()
{
	getClear();

	cout << "\t************************************************************** \n";
	cout << "\t           парсинг логов v." << version_programm << "\n";
	cout << "\t************************************************************** \n\n";
}


std::ostream &operator<<(std::ostream &os, const vector<FindFiles::FilesStruct> &listfiles)
{
	for (const auto &list : listfiles) {
		os << "file: " << list.fileName << "\t unixtime: " << list.unixTime << "\n";
	}

	return os;
}


// ковертер из time_t -> unixtime
time_t FindFiles::getTimeToUnix(const std::filesystem::file_time_type &times)
{
	//namespace fs = std::filesystem;	
	using namespace std::chrono_literals;

	time_t time = duration_cast<std::chrono::seconds>(times.time_since_epoch() - 11644473600s).count();

	return time;
}

// получить путь до папки которая будет бэкапиться
string FindFiles::getDSTFolderBackup(const string &source) const
{
	string backupSource = source;
	string backupDST = backupSource.substr(3, backupSource.length() - 3);

	return LOG_FOLDER + "\\" + backupDST;
}

// кол-во файлов в папке
string FindFiles::getCountFiles(const string &destbackup) const
{
	namespace fs = std::filesystem;

	int count{ 0 };

	for (const auto &entry : fs::directory_iterator(destbackup)) {
		count++;
	}
	
	return to_string(count);
}

// размер папки LOG_FOLDER 
string FindFiles::getSize(const string &path) const
{
	namespace fs = std::filesystem;

	size_t size{ 0 };
	
	for (const auto &entry : fs::recursive_directory_iterator(path)) {
		if (entry.is_regular_file()) {
			size += entry.file_size();
		}
	} 
	
	return to_string(size / 1024 / 1024 ) + " Mb";
}

// сущестует ли файл\папка в готовом бэкапе
bool FindFiles::IsExistBackup(const string &pathbackup, const string &pathoriginal)
{
	namespace fs = std::filesystem;	
	
	// проверим для папки
	if (!fs::is_directory(pathbackup)) {
		return (fs::exists(pathbackup) ? true : false);
	}
	else {
		// проверим кол-во файлов в папке
		unsigned int countoriginal, countbackup;
		std::istringstream(getCountFiles(pathoriginal)) >> countoriginal;
		std::istringstream(getCountFiles(pathbackup)) >> countbackup;

		return (countbackup != countoriginal ? false : true);
	}	
}

// отображение папок
std::string FindFiles::getDestFolders(DestFolders types) 
{
	switch (types)
	{
		case Analis_Service:		return ANALIS_SERVICE;			break;	// делится на подпапки формат ГГГГ-ММ-ДД (2023-12-08) | *.txt
		case MailServer0:			return MAILSERVER0;				break;	// *.txt
		case MailServer1:			return MAILSERVER1;				break;	// *.txt	
		case MailServer2:			return MAILSERVER2;				break;	// *.txt
		case MailServer3:			return MAILSERVER3;				break;	// делится на подпапки формат ГГ-ММ-ДД (23-12-01) | *.eml	
		case repl0:					return REPL0;					break;	// *.log	
		case repl1:					return REPL1;					break;	// *.txt	
		case repl2:					return REPL2;					break;	// *.txt	
		case repl3:					return REPL3;					break;	// *.txt
		case repl4:					return REPL4;					break;	// *.txt
		case repl_main0:			return REPL_MAIN0;				break;	// *.txt	
		case repl_main1:			return REPL_MAIN1;				break;	// *.txt
		case repl_main2:			return REPL_MAIN2;				break;	// *.txt
		case repl_main3:			return REPL_MAIN3;				break;	// *.txt
		case repl_main4:			return REPL_MAIN4;				break;	// *.txt
		case repl_main5:			return REPL_MAIN5;				break;	// *.txt
		case repl_main6:			return REPL_MAIN6;				break;	// *.txt	
		case reportserver0:			return REPORTSERVER0;			break;	// делится на подпапки формат Service_log_ГГ-ММ-ДД (Service_log_23-12-08) | *.log
		case reportserver1:			return REPORTSERVER1;			break;	// делится на подпапки формат ГГГГ-ММ-ДД (2023-12-08) | *.log
		case reportServer_WEB_LP0:	return REPORTSERVER_WEB_LP0;	break;	// делится на подпапки формат Service_log_ГГ-ММ-ДД (Service_log_23-12-08) | *.log
		case sms0:					return SMS0;					break;	// *.txt
		case sync0:					return SYNC0;					break;	// *.txt
	}
	
	return "no types";
}


bool FindFiles::getIsExistFolder(DestFolders types)
{
	namespace fs = std::filesystem;

	switch (types)
	{
		case Analis_Service:	// делится на подпапки формат ГГГГ-ММ-ДД (2023-12-08) | *.txt
		{		
		
			return (fs::exists(ANALIS_SERVICE) ? true : false);
			break;

		}
		case MailServer0:	// *.txt
		{		  
		
			return (fs::exists(MAILSERVER0) ? true : false);
			break;

		}
		case MailServer1:	// *.txt
		{		  
		
			return (fs::exists(MAILSERVER1) ? true : false);
			break;	

		}
		case MailServer2:	// *.txt
		{		  
		
			return (fs::exists(MAILSERVER2) ? true : false);
			break;

		}
		case MailServer3:	// делится на подпапки формат ГГ-ММ-ДД (23-12-01) | *.eml
		{		
		
			return (fs::exists(MAILSERVER3) ? true : false);
			break;

		}
		case repl0:	// *.log
		{	
		
			return (fs::exists(REPL0) ? true : false);
			break;

		}
		case repl1:	// *.txt
		{	
		
			return (fs::exists(REPL1) ? true : false);
			break;

		}
		case repl2:	// *.txt
		{	
		
			return (fs::exists(REPL2) ? true : false);
			break;	

		}
		case repl3:	// *.txt
		{	
		
			return (fs::exists(REPL3) ? true : false);
			break;

		}
		case repl4:	// *.txt
		{

			return (fs::exists(REPL4) ? true : false);
			break;

		}
		case repl_main0:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN0) ? true : false);
			break;

		}
		case repl_main1:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN1) ? true : false);
			break;	

		}
		case repl_main2:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN2) ? true : false);
			break;

		}
		case repl_main3:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN3) ? true : false);
			break;	

		}
		case repl_main4:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN4) ? true : false);
			break;

		}
		case repl_main5:	// *.txt
		{	
		
			return (fs::exists(REPL_MAIN5) ? true : false);
			break;

		}
		case repl_main6: // *.txt
		{	
		
			return (fs::exists(REPL_MAIN6) ? true : false);
			break;

		}
		case reportserver0:	// делится на подпапки формат Service_log_ГГ-ММ-ДД (Service_log_23-12-08) | *.log
		{	
		
			return (fs::exists(REPORTSERVER0) ? true : false);
			break;	

		}
		case reportserver1:	// делится на подпапки формат ГГГГ-ММ-ДД (2023-12-08) | *.log
		{	
		
			return (fs::exists(REPORTSERVER1) ? true : false);
			break;	

		}
		case reportServer_WEB_LP0:	// делится на подпапки формат Service_log_ГГ-ММ-ДД (Service_log_23-12-08) | *.log
		{	
		
			return (fs::exists(REPORTSERVER_WEB_LP0) ? true : false);
			break;	

		}
		case sms0:	// *.txt
		{	
			return (fs::exists(SMS0) ? true : false);
			break;		
		}
		case sync0:	// *.txt
		{
			return (fs::exists(SYNC0) ? true : false);
			break;
		}
	}

	return false;
}

// создание списка для копирования\удаления файлов 
void FindFiles::createList(ListType typelist, DestFolders types, unsigned short dayTTL)
{
	Logging log;
	namespace fs = std::filesystem;
	
	// очищаем список с файлами
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	log.setLog("<i>Просматриваем содержимое папки: " + getDestFolders(types) + "</i>", false);

	cout << "Просматриваем содержимое папки: " << getDestFolders(types) << "\n";

	if (!getIsExistFolder(types))
	{
		log.setLog("ОШИБКА! Отсутствует папка: " + getDestFolders(types), true);
		cout << "ОШИБКА! Отсутствует папка: " << getDestFolders(types) << "\n";
		return;
	}

	// находим содержимое в папке
	fs::path path = (getDestFolders(types));

	FilesStruct list;	

	for (const auto &entry : fs::directory_iterator(path))
	{

		// текущее время
		time_t currentTime = time(0);		
		time_t fileTime = getTimeToUnix(entry.last_write_time());

		switch (typelist)
		{
		case FindFiles::backup:  // список файлов которые пойдут в бэкап
		{
			// проверим время
			if (currentTime - fileTime < dayTTL * 86400)
			{

				// запишем 
				list.fileName = entry.path().filename().generic_string();
				list.unixTime = fileTime;

				listFindedFiles.push_back(list);

				break;
			}

			break;
		}
		case FindFiles::del:	// список файлов для удаления из оригинальных папок с логами
		{
			// проверим время
			if (currentTime - fileTime > dayTTL * 86400)
			{
				// запишем 
				list.fileName = entry.path().filename().generic_string();
				list.unixTime = fileTime;

				listFindedFiles.push_back(list);

				break;
			}

			break;
		}
		}
	}
	//cout << listFindedFiles; debug 	
}

// для формирования списка на удаление из LOG_FOLDER
void FindFiles::createList(unsigned short dayTTL)
{
	Logging log;
	namespace fs = std::filesystem;

	// очищаем список с файлами
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	FilesStruct list;

	for (const auto &entry : fs::recursive_directory_iterator(LOG_FOLDER)) {
		
		if (entry.is_directory()) {
			
			log.setLog("<i>Просматриваем содержимое папки: " + entry.path().generic_string() + "</i>", false);			
			cout << "Просматриваем содержимое папки: " << entry.path() << "\n";
			
		}
		
		// просматриваем только файлы, папки потом удалять будем
		if (entry.is_regular_file()) {
			// текущее время
			time_t currentTime = time(0);
			time_t fileTime = getTimeToUnix(entry.last_write_time());

			if (currentTime - fileTime > dayTTL * 86400)
			{
				// запишем 
				list.fileName = entry.path().generic_string();
				list.unixTime = fileTime;

				listFindedFiles.push_back(list);				
			}
		}
	}	
}

// для формирования списка на удаление из LOG_FOLDER пустых папок
void FindFiles::createList()
{
	Logging log;
	namespace fs = std::filesystem;

	// очищаем список с файлами
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	FilesStruct list;

	for (const auto &entry : fs::recursive_directory_iterator(LOG_FOLDER))
	{
		if (entry.is_directory())
		{			
			if (fs::is_empty(entry.path())) {
				
				// запишем 
				list.fileName = entry.path().generic_string();
				list.unixTime = 0;

				listFindedFiles.push_back(list);
			
			}			
		}		
	}
}


// создание бэкапа
void FindFiles::Backup()
{	
	Logging log;
	namespace fs = std::filesystem;	

	// создаем список
	for (int i = 0; i<DESTFOLDERS_COUNT; ++i) {
		
		showInfoVersion();

		createList(backup, static_cast<DestFolders>(i), FILES_TTL);
	
		// ничего не нашли, пошли дальше по списку
		if (listFindedFiles.empty()) { continue; }

		// что то есть в списке, пошли бэкапить
		for (auto it{ listFindedFiles.begin()}; it != listFindedFiles.end(); it++) {	

			const string destbackup = getDestFolders(static_cast<DestFolders>(i)) + "\\" + it->fileName;

			// путь до бэкапа
			string backup = getDSTFolderBackup(destbackup);

			// забэкапили ли ранее ? 
			if (IsExistBackup(backup,destbackup)) { continue; }

			if (fs::is_directory(destbackup)) {		// папка
				
				try {
					cout << "Копирование папки " + destbackup << " (файлов: " << getCountFiles(destbackup) << ") \n";
					
					fs::copy(destbackup, backup, /*fs::copy_options::recursive |*/ fs::copy_options::update_existing);
					
					log.setLog("Скопирована папка " + destbackup + " (файлов: " + getCountFiles(destbackup) + ")", false);
				}
				catch (std::exception &error_message) {			
					
					log.setLog("ОШИБКА! Не удается скопировать " + destbackup + " в " + backup +
							   ". " + error_message.what(), true);
				}
			}
			else {							        // файл
				try
				{
					cout << "Копирование файла " + destbackup << "\n";
					
					fs::copy_file(destbackup, backup, /*fs::copy_options::recursive | */ fs::copy_options::update_existing);

					
					log.setLog("Скопирован файл " + destbackup, false);
				}
				catch (std::exception &error_message)
				{

					log.setLog("ОШИБКА! Не удается скопировать " + destbackup + " в " + backup +
						". " + error_message.what(), true);
				}
			}			
		}
	}
}



// очистка от старых файлов бэкапа
void FindFiles::Delete()
{
	Logging log;
	namespace fs = std::filesystem;

	// создаем список (из данных по папкам лога)
	for (int i = 0; i < DESTFOLDERS_COUNT; ++i) {
		showInfoVersion();

		createList(del, static_cast<DestFolders>(i), FILES_ORIGINAL_TTL);
	
		if (listFindedFiles.empty()) { continue; }

		// очищаем 
		for (auto it{ listFindedFiles.begin() }; it != listFindedFiles.end(); it++)	{
			
			const string destbackup = getDestFolders(static_cast<DestFolders>(i)) + "\\" + it->fileName;					

			if (fs::is_directory(destbackup))
			{		// папка
				try
				{
					string count_files = getCountFiles(destbackup); // подсчет файлов, т.к после уделния они не будут доступны

					cout << "Удаление папки " + destbackup << " (файлов: " << count_files << ") \n";
					
					fs::permissions(destbackup, fs::perms::all);
					fs::remove_all(destbackup);

					log.setLog("Удалена папка " + destbackup + " (файлов: " + count_files + ")", false);
				}
				catch (std::exception &error_message)				{

					log.setLog("ОШИБКА! Не удается удалить папку " + destbackup +" " + error_message.what(), true);
				}
			}
			else
			{							        // файл
				try
				{
					cout << "Удаление файла " + destbackup << "\n";

					fs::permissions(destbackup, fs::perms::all);
					fs::remove(destbackup);

					log.setLog("Удален файл " + destbackup, false);
				}
				catch (std::exception &error_message)
				{
					log.setLog("ОШИБКА! Не удается удалить файл " + destbackup + " " + error_message.what(), true);
				}
			}		
		}	
	}

	// список из нового местоположения лога (LOG_FOLDER)
	showInfoVersion();
	createList(FILES_TTL);
	
	// очищаем  
	for (auto it{ listFindedFiles.begin()}; it != listFindedFiles.end(); it++) {
		
		try
		{
			cout << "Удаление файла " + it->fileName << "\n";

			fs::permissions(it->fileName, fs::perms::all);
			fs::remove(it->fileName);

			log.setLog("Удален файл " + it->fileName, false);
		}
		catch (std::exception &error_message)
		{
			log.setLog("ОШИБКА! Не удается удалить файл " + it->fileName + " " + error_message.what(), true);
		}
	}
	
	createList();

	for (auto it{ listFindedFiles.begin() }; it != listFindedFiles.end(); it++)
	{
		try
		{
			cout << "Удаление пустой папки " + it->fileName << "\n";

			fs::permissions(it->fileName, fs::perms::all);
			fs::remove(it->fileName);

			log.setLog("Удалена пустая папка " + it->fileName, false);
		}
		catch (std::exception &error_message)
		{
			log.setLog("ОШИБКА! Не удается пустую папку " + it->fileName + " " + error_message.what(), true);
		}
	}
}


