// FIND  :     Поиск и ротация всех логов
//             которые располагаются в разных местах 
//             данный код собирает все логи в единое место
//             а так же ведет ротацию логов на основе unixtime времени создания
//             
//             На будущее: переписать код чтобы уйти от CONSTANTS.CPP 

#include <iostream>
#include <string>
#include "FIND_FILES_class.h"
#include "LOG_class.h"

// константы из constants.cpp
extern const string LOG_FOLDER;
extern const string LOG_FILES;


using std::cout;
using std::string;

string getTimeExecute(time_t start, time_t stop) {
    
    double execute_time = difftime(stop, start);

    std::ostringstream strm;
    strm << execute_time;

    return strm.str()+"s";
}

void clearOldLog() {
    namespace fs = std::filesystem;
    if (fs::exists(LOG_FILES)) { fs::remove(LOG_FILES); }    
}

int main()
{
    setlocale(LC_ALL,"");     
    
    // очистка от предидущего лога
    clearOldLog();
        
    Logging log;
    log.setLog("<font color = 'green'><b>##### Старт задачи сбора логов #####</b></font>", false);    
    time_t startexecute = time(0);

    FindFiles files;
    
    // создаем бэкапы (т.е. копируем из папок в папку !LOG_ALL)
    files.Backup();
      

    time_t stopexecute = time(0);


    log.setLog("<font color = 'green'><b>##### Окончание задачи сбора логов. Заняло времени: " + 
               getTimeExecute(startexecute,stopexecute)+
               " #####</b></font>", false);


     ///////////////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////////////// 
     ///////////////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////////////


    /// очищаем от старых бэкапов
    log.setLog("<font color = 'red'><b>##### Старт задачи очистки старых логов #####</b></font>", false);
    startexecute = time(0);

    files.Delete();

    stopexecute = time(0);

    log.setLog("<font color = 'red'><b>##### Окончание задачи очистки старых логов. Заняло времени: " +
        getTimeExecute(startexecute, stopexecute) +
        " #####</b></font>", false);

    // подсчитаем размер 
    log.setLog("<b>##### Размер папки логов: " +files.getSize()+ " #####</b>", false);  

    return 0;
    
}

