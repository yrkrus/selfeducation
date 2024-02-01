#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

#define FIND_FILES_CLASS_H
#ifdef FIND_FILES_CLASS_H

using std::vector;
using std::string;


// ��������� �� constants.cpp
extern const string LOG_FOLDER;


class FindFiles
{

private:

	// ��������� �� ����\����� � ������� ������
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

	struct FilesStruct				// ���� �� ����� + ���� ����� ��� ��������
	{
		string fileName;
		time_t unixTime;		
	};
	

	vector<FilesStruct> listFindedFiles;	// ������ ������ ���� ��������������� ������
		
	friend std::ostream &operator<<(std::ostream &os, const vector<FilesStruct> &listfiles);

	
	// ����������� �����
	string getDestFolders(DestFolders types);

	// �������� ������������� ����� � ������
	bool getIsExistFolder(DestFolders types);

	// �������� ������ ��� �����������\�������� ������ 
	void createList(ListType typelist, DestFolders types, unsigned short dayTTL);
	void createList(unsigned short dayTTL); // ��� ������������ ������ �� �������� �� LOG_FOLDER
	void createList();					    // ��� ������������ ������ �� �������� �� LOG_FOLDER ������ �����

	// �������� ������
	void Backup();
	
	// ������� �� ������ ������ ������
	void Delete();

	// ����������� � unix datetime
	time_t getTimeToUnix(const std::filesystem::file_time_type &times);
	
	// �������� ���� �� ����� ������� ����� ����������
	string getDSTFolderBackup(const string &source) const;

	// ���-�� ������ � �����
	string getCountFiles(const string &destbackup) const;

	// ������ ����� LOG_FOLDER
	string getSize(const string &path = LOG_FOLDER) const;	
	
};

#endif // !FIND_FILES_CLASS_H

