#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

#define FIND_FILES_CLASS_H
#ifdef FIND_FILES_CLASS_H

using std::vector;
using std::string;


// константы из constants.cpp
extern const string LOG_FOLDER;


class FindFiles
{

private:

	// сущестует ли файл\папка в готовом бэкапе
	bool IsExistBackup(const string &pathbackup, const string &pathoriginal);

public:
	FindFiles() {};
	~FindFiles() {};


	enum DestFolders
	{
		Analis_Service,			// C:\Analis_Service\log
		MailServer0,			// C:\MailServer\log\analis
		MailServer1,			// C:\MailServer\log\analis\IN
		MailServer2,			// C:\MailServer\log2
		MailServer3,			// C:\MailServer\Messages2
		repl0,					// C:\repl\log\repl\autorun
		repl1,					// C:\repl\log\repl\web
		repl2,					// C:\repl\log\repl\web_lp
		repl3,					// C:\repl\log\repl\web_lp\dbproxy
		repl4,					// C:\repl\bin\log
		repl_main0,				// C:\repl_main\log
		repl_main1,				// C:\repl_main\log\call_tracking
		repl_main2,				// C:\repl_main\log\scripts
		repl_main3,				// C:\repl_main\log\oper
		repl_main4,				// C:\repl_main\log\covid_rpn
		repl_main5,				// C:\repl_main\log\iemk
		repl_main6,				// C:\repl_main\log\remd
		reportserver0,			// C:\reportserver\log
		reportserver1,			// C:\reportserver\log\Build_log
		reportServer_WEB_LP0,	// C:\ReportServer_WEB_LP\log
		sms0,					// C:\Sms\Win64\log
		sync0,					// C:\SyncService\log		
		DESTFOLDERS_COUNT =	22 	
	};

	enum ListType
	{
		backup,
		del,
		del_backup
	};

	struct FilesStruct				// путь до файла + дата время его создания
	{
		string fileName;
		time_t unixTime;		
	};
	

	vector<FilesStruct> listFindedFiles;	// список файлов всех рассматриваемых файлов
		
	friend std::ostream &operator<<(std::ostream &os, const vector<FilesStruct> &listfiles);

	
	// отображение папок
	string getDestFolders(DestFolders types);

	// проверка существования папки с логами
	bool getIsExistFolder(DestFolders types);

	// создание списка для копирования\удаления файлов 
	void createList(ListType typelist, DestFolders types, unsigned short dayTTL);
	void createList(unsigned short dayTTL); // для формирования списка на удаление из LOG_FOLDER
	void createList();					    // для формирования списка на удаление из LOG_FOLDER пустых папок

	// создание бэкапа
	void Backup();
	
	// очистка от старых файлов бэкапа
	void Delete();

	// конвертация в unix datetime
	time_t getTimeToUnix(const std::filesystem::file_time_type &times);
	
	// получить путь до папки которая будет бэкапиться
	string getDSTFolderBackup(const string &source) const;

	// кол-во файлов в папке
	string getCountFiles(const string &destbackup) const;

	// размер папки LOG_FOLDER
	string getSize(const string &path = LOG_FOLDER) const;	
	
};

#endif // !FIND_FILES_CLASS_H

