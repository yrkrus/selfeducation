#include <iostream>
#include <string>
#include <unistd.h>
#include "Constants.h"
#include "InternalFunction.h"
#include "SQLRequest.h"
//#include <thread>

// эти include потом убрать, они нужны для отладки только
#include <stdio.h>
#include <time.h>
#include <chrono>


enum Commands
{
    ivr,            // кто в IVR
    queue,          // текущая очередь
    active_sip,     // какие активные sip зарегистрированы в очереди
    connect_bd,     // убрать потом, это для теста
    start,          // сбор данных в БД   
    statistics,     // отобразить статистику
};

// получить команду
Commands getCommand(char *ch) {
    std::string commands = static_cast<std::string> (ch);

    if (commands == "ivr")               return ivr;
    if (commands == "queue")             return queue;
    if (commands == "active_sip")        return active_sip;
    if (commands == "connect_bd")        return connect_bd;
    if (commands == "start")             return start;
    if (commands == "statistics")        return statistics;

    return ivr;                         // default;
}


void stat() {
    int TIK = 6000;
    // int avg{0};
    size_t all{ 0 };
    int min{ 1000 };
    int max{ 0 };

    for (size_t i = 1; /*i <= TIK*/; ++i)
    {

        showVersionCore();
        
        auto start = std::chrono::steady_clock::now();

        std::cout << getCurrentDateTime() + "\t\titeration: \t" << i << "\n\n";

        getStatistics();

        auto stop = std::chrono::steady_clock::now();

        auto execute_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "\ntime execute code: " << execute_ms.count() << " ms\n";
        all += execute_ms.count();

        if (execute_ms.count() < min) { min = execute_ms.count(); }
        if (execute_ms.count() > max) { max = execute_ms.count(); }

        std::cout << "avg execute = " << all / i << " ms | min execute = " << min << " ms | max execute = " << max << " ms\n";
               
        sleep(5);
        system("clear");

        if (i >= 10800)
        {
            all = 0;
            i = 1;
            int min = 1000;
            int max = 0;
        }
    }
}

void collect() {
    int TIK = 6000;
   // int avg{0};
    size_t all{ 0 };
    int min{ 1000 };
    int max{ 0 };    

    for (size_t i = 1; /*i <= TIK*/; ++i)
    {          

        showVersionCore();

        auto start = std::chrono::steady_clock::now();

        std::cout << getCurrentDateTime() + "\t\titeration: \t" << i << "\n\n";

        getIVR();
        getQueue();
        getActiveSip();          

        auto stop = std::chrono::steady_clock::now();

        auto execute_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout  << "\ntime execute code: " << execute_ms.count() << " ms\n";
        all += execute_ms.count();

        if (execute_ms.count() < min) { min = execute_ms.count(); }
        if (execute_ms.count() > max) { max = execute_ms.count(); }

        std::cout  << "avg execute = " << all / i << " ms | min execute = " << min << " ms | max execute = " << max << " ms\n";

        if (execute_ms.count() < 1000) {        
        sleep(1);       
        } 

        system("clear");

        if (i >= 10800)
        {
            all = 0;
            i = 1;
            int min = 1000;
            int max = 0;
        }        
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); 


    if (argc == 1)
    {
        std::cout << "no arguments!\n";
        return -1;
    }
    else if (argc > 2)
    {
        std::cout << "too mony arguments\n";
        return -1;
    }

    Commands ch = getCommand(argv[1]);

    // пошли запросики
    switch (ch)
    {
        case(ivr): {                // запись в БД кто сейчас слушает IVR 
            // запрос
            getIVR();   
            break;
        }
        case(queue): {              // запись в БД кто ушел из IVR в очередь
            // запрос
            getQueue();
            break;
        } 
        case(active_sip): {         // запись в БД кто сейчас с кем разговариваети сколько по времени
            // запрос
            getActiveSip();
            break;
        }
        case(connect_bd): {      
            SQL_REQUEST::SQL base;
            if (base.isConnectedBD()) {
                std::cout << "Connect UP\n";
            }
            else {
                std::cout << "Connect DOWN!\n";                
            }             
            break;
        }        
        case(start):      {         
            collect();
            break;
        }   
        case(statistics): {
            stat();
            break;
        }
    }
     return 0;
};