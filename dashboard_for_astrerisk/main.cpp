#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

// constants (на случай быстрых изменений) | потом в отдельный *.h закинуть
const char *cIVR[] = { "asterisk -rx \"core show channels verbose\" | grep Playback" };



enum Commands
{
    ivr,            // кто в IVR
    current_queue   // текущая очередь
};

// получить команду
Commands getCommand(char *ch) {
    std::string commands = static_cast<std::string> (ch);

    if (commands == "ivr")               return ivr;
    if (commands == "current_queue")     return current_queue;

    return ivr;                         // default;
}


// создать + получить текущий IVR
void getIVR(void) {
    system(*cIVR);
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
        case(ivr): {
            // запрос
            getIVR();            
            break;
        }
        case(current_queue): {
            // запрос
            break;
        }   
    }
    
    //return 0;
};