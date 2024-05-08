#include <iostream>
#include <string>
#include <unistd.h>
#include "Constants.h"
#include "InternalFunction.h"


enum Commands
{
    ivr,            // кто в IVR
    queue,          // текущая очередь
    active_sip,     // какие активные sip зарегистрированы в очереди
};

// получить команду
Commands getCommand(char *ch) {
    std::string commands = static_cast<std::string> (ch);

    if (commands == "ivr")               return ivr;
    if (commands == "queue")             return queue;
    if (commands == "active_sip")        return active_sip;

    return ivr;                         // default;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

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
    }
    
    return 0;
};