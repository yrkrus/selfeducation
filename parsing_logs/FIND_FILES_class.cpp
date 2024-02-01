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


// ��������� �� constants.cpp
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


// ������� �������
void getClear()
{
	system("cls");
}

// ���� ������
void showInfoVersion()
{
	getClear();

	cout << "\t************************************************************** \n";
	cout << "\t           ������� ����� v." << version_programm << "\n";
	cout << "\t************************************************************** \n\n";
}


std::ostream &operator<<(std::ostream &os, const vector<FindFiles::FilesStruct> &listfiles)
{
	for (const auto &list : listfiles) {
		os << "file: " << list.fileName << "\t unixtime: " << list.unixTime << "\n";
	}

	return os;
}


// �������� �� time_t -> unixtime
time_t FindFiles::getTimeToUnix(const std::filesystem::file_time_type &times)
{
	//namespace fs = std::filesystem;	
	using namespace std::chrono_literals;

	time_t time = duration_cast<std::chrono::seconds>(times.time_since_epoch() - 11644473600s).count();

	return time;
}

// �������� ���� �� ����� ������� ����� ����������
string FindFiles::getDSTFolderBackup(const string &source) const
{
	string backupSource = source;
	string backupDST = backupSource.substr(3, backupSource.length() - 3);

	return LOG_FOLDER + "\\" + backupDST;
}

// ���-�� ������ � �����
string FindFiles::getCountFiles(const string &destbackup) const
{
	namespace fs = std::filesystem;

	int count{ 0 };

	for (const auto &entry : fs::directory_iterator(destbackup)) {
		count++;
	}
	
	return to_string(count);
}

// ������ ����� LOG_FOLDER 
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

// ��������� �� ����\����� � ������� ������
bool FindFiles::IsExistBackup(const string &pathbackup, const string &pathoriginal)
{
	namespace fs = std::filesystem;	
	
	// �������� ��� �����
	if (!fs::is_directory(pathbackup)) {
		return (fs::exists(pathbackup) ? true : false);
	}
	else {
		// �������� ���-�� ������ � �����
		unsigned int countoriginal, countbackup;
		std::istringstream(getCountFiles(pathoriginal)) >> countoriginal;
		std::istringstream(getCountFiles(pathbackup)) >> countbackup;

		return (countbackup != countoriginal ? false : true);
	}	
}

// ����������� �����
std::string FindFiles::getDestFolders(DestFolders types) 
{
	switch (types)
	{
		case Analis_Service:		return ANALIS_SERVICE;			break;	// ������� �� �������� ������ ����-��-�� (2023-12-08) | *.txt
		case MailServer0:			return MAILSERVER0;				break;	// *.txt
		case MailServer1:			return MAILSERVER1;				break;	// *.txt	
		case MailServer2:			return MAILSERVER2;				break;	// *.txt
		case MailServer3:			return MAILSERVER3;				break;	// ������� �� �������� ������ ��-��-�� (23-12-01) | *.eml	
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
		case reportserver0:			return REPORTSERVER0;			break;	// ������� �� �������� ������ Service_log_��-��-�� (Service_log_23-12-08) | *.log
		case reportserver1:			return REPORTSERVER1;			break;	// ������� �� �������� ������ ����-��-�� (2023-12-08) | *.log
		case reportServer_WEB_LP0:	return REPORTSERVER_WEB_LP0;	break;	// ������� �� �������� ������ Service_log_��-��-�� (Service_log_23-12-08) | *.log
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
		case Analis_Service:	// ������� �� �������� ������ ����-��-�� (2023-12-08) | *.txt
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
		case MailServer3:	// ������� �� �������� ������ ��-��-�� (23-12-01) | *.eml
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
		case reportserver0:	// ������� �� �������� ������ Service_log_��-��-�� (Service_log_23-12-08) | *.log
		{	
		
			return (fs::exists(REPORTSERVER0) ? true : false);
			break;	

		}
		case reportserver1:	// ������� �� �������� ������ ����-��-�� (2023-12-08) | *.log
		{	
		
			return (fs::exists(REPORTSERVER1) ? true : false);
			break;	

		}
		case reportServer_WEB_LP0:	// ������� �� �������� ������ Service_log_��-��-�� (Service_log_23-12-08) | *.log
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

// �������� ������ ��� �����������\�������� ������ 
void FindFiles::createList(ListType typelist, DestFolders types, unsigned short dayTTL)
{
	Logging log;
	namespace fs = std::filesystem;
	
	// ������� ������ � �������
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	log.setLog("<i>������������� ���������� �����: " + getDestFolders(types) + "</i>", false);

	cout << "������������� ���������� �����: " << getDestFolders(types) << "\n";

	if (!getIsExistFolder(types))
	{
		log.setLog("������! ����������� �����: " + getDestFolders(types), true);
		cout << "������! ����������� �����: " << getDestFolders(types) << "\n";
		return;
	}

	// ������� ���������� � �����
	fs::path path = (getDestFolders(types));

	FilesStruct list;	

	for (const auto &entry : fs::directory_iterator(path))
	{

		// ������� �����
		time_t currentTime = time(0);		
		time_t fileTime = getTimeToUnix(entry.last_write_time());

		switch (typelist)
		{
		case FindFiles::backup:  // ������ ������ ������� ������ � �����
		{
			// �������� �����
			if (currentTime - fileTime < dayTTL * 86400)
			{

				// ������� 
				list.fileName = entry.path().filename().generic_string();
				list.unixTime = fileTime;

				listFindedFiles.push_back(list);

				break;
			}

			break;
		}
		case FindFiles::del:	// ������ ������ ��� �������� �� ������������ ����� � ������
		{
			// �������� �����
			if (currentTime - fileTime > dayTTL * 86400)
			{
				// ������� 
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

// ��� ������������ ������ �� �������� �� LOG_FOLDER
void FindFiles::createList(unsigned short dayTTL)
{
	Logging log;
	namespace fs = std::filesystem;

	// ������� ������ � �������
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	FilesStruct list;

	for (const auto &entry : fs::recursive_directory_iterator(LOG_FOLDER)) {
		
		if (entry.is_directory()) {
			
			log.setLog("<i>������������� ���������� �����: " + entry.path().generic_string() + "</i>", false);			
			cout << "������������� ���������� �����: " << entry.path() << "\n";
			
		}
		
		// ������������� ������ �����, ����� ����� ������� �����
		if (entry.is_regular_file()) {
			// ������� �����
			time_t currentTime = time(0);
			time_t fileTime = getTimeToUnix(entry.last_write_time());

			if (currentTime - fileTime > dayTTL * 86400)
			{
				// ������� 
				list.fileName = entry.path().generic_string();
				list.unixTime = fileTime;

				listFindedFiles.push_back(list);				
			}
		}
	}	
}

// ��� ������������ ������ �� �������� �� LOG_FOLDER ������ �����
void FindFiles::createList()
{
	Logging log;
	namespace fs = std::filesystem;

	// ������� ������ � �������
	if (!listFindedFiles.empty()) listFindedFiles.clear();

	FilesStruct list;

	for (const auto &entry : fs::recursive_directory_iterator(LOG_FOLDER))
	{
		if (entry.is_directory())
		{			
			if (fs::is_empty(entry.path())) {
				
				// ������� 
				list.fileName = entry.path().generic_string();
				list.unixTime = 0;

				listFindedFiles.push_back(list);
			
			}			
		}		
	}
}


// �������� ������
void FindFiles::Backup()
{	
	Logging log;
	namespace fs = std::filesystem;	

	// ������� ������
	for (int i = 0; i<DESTFOLDERS_COUNT; ++i) {
		
		showInfoVersion();

		createList(backup, static_cast<DestFolders>(i), FILES_TTL);
	
		// ������ �� �����, ����� ������ �� ������
		if (listFindedFiles.empty()) { continue; }

		// ��� �� ���� � ������, ����� ��������
		for (auto it{ listFindedFiles.begin()}; it != listFindedFiles.end(); it++) {	

			const string destbackup = getDestFolders(static_cast<DestFolders>(i)) + "\\" + it->fileName;

			// ���� �� ������
			string backup = getDSTFolderBackup(destbackup);

			// ���������� �� ����� ? 
			if (IsExistBackup(backup,destbackup)) { continue; }

			if (fs::is_directory(destbackup)) {		// �����
				
				try {
					cout << "����������� ����� " + destbackup << " (������: " << getCountFiles(destbackup) << ") \n";
					
					fs::copy(destbackup, backup, /*fs::copy_options::recursive |*/ fs::copy_options::update_existing);
					
					log.setLog("����������� ����� " + destbackup + " (������: " + getCountFiles(destbackup) + ")", false);
				}
				catch (std::exception &error_message) {			
					
					log.setLog("������! �� ������� ����������� " + destbackup + " � " + backup +
							   ". " + error_message.what(), true);
				}
			}
			else {							        // ����
				try
				{
					cout << "����������� ����� " + destbackup << "\n";
					
					fs::copy_file(destbackup, backup, /*fs::copy_options::recursive | */ fs::copy_options::update_existing);

					
					log.setLog("���������� ���� " + destbackup, false);
				}
				catch (std::exception &error_message)
				{

					log.setLog("������! �� ������� ����������� " + destbackup + " � " + backup +
						". " + error_message.what(), true);
				}
			}			
		}
	}
}



// ������� �� ������ ������ ������
void FindFiles::Delete()
{
	Logging log;
	namespace fs = std::filesystem;

	// ������� ������ (�� ������ �� ������ ����)
	for (int i = 0; i < DESTFOLDERS_COUNT; ++i) {
		showInfoVersion();

		createList(del, static_cast<DestFolders>(i), FILES_ORIGINAL_TTL);
	
		if (listFindedFiles.empty()) { continue; }

		// ������� 
		for (auto it{ listFindedFiles.begin() }; it != listFindedFiles.end(); it++)	{
			
			const string destbackup = getDestFolders(static_cast<DestFolders>(i)) + "\\" + it->fileName;					

			if (fs::is_directory(destbackup))
			{		// �����
				try
				{
					string count_files = getCountFiles(destbackup); // ������� ������, �.� ����� ������� ��� �� ����� ��������

					cout << "�������� ����� " + destbackup << " (������: " << count_files << ") \n";
					
					fs::permissions(destbackup, fs::perms::all);
					fs::remove_all(destbackup);

					log.setLog("������� ����� " + destbackup + " (������: " + count_files + ")", false);
				}
				catch (std::exception &error_message)				{

					log.setLog("������! �� ������� ������� ����� " + destbackup +" " + error_message.what(), true);
				}
			}
			else
			{							        // ����
				try
				{
					cout << "�������� ����� " + destbackup << "\n";

					fs::permissions(destbackup, fs::perms::all);
					fs::remove(destbackup);

					log.setLog("������ ���� " + destbackup, false);
				}
				catch (std::exception &error_message)
				{
					log.setLog("������! �� ������� ������� ���� " + destbackup + " " + error_message.what(), true);
				}
			}		
		}	
	}

	// ������ �� ������ �������������� ���� (LOG_FOLDER)
	showInfoVersion();
	createList(FILES_TTL);
	
	// �������  
	for (auto it{ listFindedFiles.begin()}; it != listFindedFiles.end(); it++) {
		
		try
		{
			cout << "�������� ����� " + it->fileName << "\n";

			fs::permissions(it->fileName, fs::perms::all);
			fs::remove(it->fileName);

			log.setLog("������ ���� " + it->fileName, false);
		}
		catch (std::exception &error_message)
		{
			log.setLog("������! �� ������� ������� ���� " + it->fileName + " " + error_message.what(), true);
		}
	}
	
	createList();

	for (auto it{ listFindedFiles.begin() }; it != listFindedFiles.end(); it++)
	{
		try
		{
			cout << "�������� ������ ����� " + it->fileName << "\n";

			fs::permissions(it->fileName, fs::perms::all);
			fs::remove(it->fileName);

			log.setLog("������� ������ ����� " + it->fileName, false);
		}
		catch (std::exception &error_message)
		{
			log.setLog("������! �� ������� ������ ����� " + it->fileName + " " + error_message.what(), true);
		}
	}
}


