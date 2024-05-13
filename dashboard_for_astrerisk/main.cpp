#include <iostream>
#include <string>
#include <unistd.h>
#include "Constants.h"
#include "InternalFunction.h"
#include "SQLRequest.h"
//#include <mysql/mysql.h>


// эти include потом убрать, они нужны для отладки только
#include <stdio.h>
#include <time.h>
#include <chrono>






enum Commands
{
    ivr,            // кто в IVR
    queue,          // текущая очередь
    active_sip,     // какие активные sip зарегистрированы в очереди
    connect_bd,     // проверка подключения к БД
    test,           // убрать потом, это для теста
    test2,          // убрать потом, это для теста
};

// получить команду
Commands getCommand(char *ch) {
    std::string commands = static_cast<std::string> (ch);

    if (commands == "ivr")               return ivr;
    if (commands == "queue")             return queue;
    if (commands == "active_sip")        return active_sip;
    if (commands == "connect_bd")        return connect_bd;
    if (commands == "test")              return test;
    if (commands == "test2")             return test2;

    return ivr;                         // default;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "RUS");

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
        case(connect_bd):
        {      
            SQL_REQUEST::SQL base;
            if (base.isConnectedBD()) {
                std::cout << "Connect UP\n";
                base.query_test();
            }
            else {
                std::cout << "Connect DOWN!\n";
                
            }

            

            
           
            

            


            /*MYSQL *mysql = createConnectionBD();
            if (mysql != nullptr) {
                std::cout << "SUCESS\n";
            }
            else {
                std::cout << "ERROR\n";
            }*/
            

            
            break;
        }        
        case(test):
        {        
            
            int TIK = 600;
            int avg;
            int all{0};
            int min{1000};
            int max{0};

            for (size_t i = 1; i <= TIK; ++i) {
                auto start = std::chrono::steady_clock::now();        

                getActiveSip();
                
                auto stop = std::chrono::steady_clock::now();                
               

                auto execute_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                std::cout << "\ntime execute code: " << execute_ms.count() << " ms\n";
                all += execute_ms.count();

                if (execute_ms.count() < min) { min = execute_ms.count(); }
                if (execute_ms.count() > max) { max = execute_ms.count(); }

                //std::cout << "time average execute code: " << static_cast<double>(all / i) << " ms\n";
                std::cout << "min execute = " << min << " ms | max execute = " << max << " ms\n";

                sleep(1);
            }
            
            
            break;
        }
        case(test2):
        {

            int TIK = 600;
            int avg;
            int all{ 0 };
            int min{ 1000 };
            int max{ 0 };

            for (size_t i = 1; i <= TIK; ++i)
            {
                auto start = std::chrono::steady_clock::now();

                getIVR();

                auto stop = std::chrono::steady_clock::now();


                auto execute_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                std::cout << "\ntime execute code: " << execute_ms.count() << " ms\n";
                all += execute_ms.count();

                if (execute_ms.count() < min) { min = execute_ms.count(); }
                if (execute_ms.count() > max) { max = execute_ms.count(); }

                //std::cout << "time average execute code: " << static_cast<double>(all / i) << " ms\n";
                std::cout << "min execute = " << min << " ms | max execute = " << max << " ms\n";

                sleep(1);
            }


            break;
        }

    }
    
    return 0;
};