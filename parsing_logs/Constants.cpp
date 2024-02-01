#include <string>

using std::string;

extern const string version_programm		= "1.5 от 01.02.2024";

extern const unsigned short FILES_TTL			= 30;			// время жизни при котором сохраняем файлы от текущей даты. Например СЕГОДНЯ - FILES_TTL(дней)
extern const unsigned short FILES_ORIGINAL_TTL	= 3;			// время жизни которое оставляем в оригинальных логах

extern const string LOG_FOLDER				= "C:\\!LOG_ALL";
extern const string LOG_FILES				= LOG_FOLDER + "\\log.html";

// папки с логами
extern const string ANALIS_SERVICE			= "C:\\Analis_Service\\log";
extern const string MAILSERVER0				= "C:\\MailServer\\log\\analis";
extern const string MAILSERVER1				= "C:\\MailServer\\log\\analis\\IN";
extern const string MAILSERVER2				= "C:\\MailServer\\log2";
extern const string MAILSERVER3				= "C:\\MailServer\\Messages2";
extern const string REPL0					= "C:\\repl\\log\\repl\\autorun";
extern const string REPL1					= "C:\\repl\\log\\repl\\web";
extern const string REPL2					= "C:\\repl\\log\\repl\\web_lp";
extern const string REPL3					= "C:\\repl\\log\\repl\\web_lp\\dbproxy";
extern const string REPL4					= "C:\\!LOG_ALL\\repl\\bin\\log";
extern const string REPL_MAIN0				= "C:\\repl_main\\log";
extern const string REPL_MAIN1				= "C:\\repl_main\\log\\call_tracking";
extern const string REPL_MAIN2				= "C:\\repl_main\\log\\scripts";
extern const string REPL_MAIN3				= "C:\\repl_main\\log\\oper";
extern const string REPL_MAIN4				= "C:\\repl_main\\log\\covid_rpn";
extern const string REPL_MAIN5				= "C:\\repl_main\\log\\iemk";
extern const string REPL_MAIN6				= "C:\\repl_main\\log\\remd";
extern const string REPORTSERVER0			= "C:\\reportserver\\log";
extern const string REPORTSERVER1			= "C:\\reportserver\\log\\Build_log";
extern const string REPORTSERVER_WEB_LP0	= "C:\\ReportServer_WEB_LP\\log";
extern const string SMS0					= "C:\\Sms\\Win64\\log";
extern const string SYNC0					= "C:\\SyncService\\log";