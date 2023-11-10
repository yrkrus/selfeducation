#include <iostream>
//#include <cstring>

/*

OK! 1) Напишите короткую программу, которая просит пользователя ввести два целых числа и выбрать математическую операцию: +, -, * или /. 
Убедитесь, что пользователь ввел корректный символ математической операции (используйте проверку).

OK! 2) Напишите функции add(), subtract(), multiply() и divide(). 
Они должны принимать два целочисленных параметра и возвращать целочисленное значение. 

OK! 3) Создайте typedef с именем arithmeticFcn для указателя на функцию, 
которая принимает два целочисленных параметра и возвращает целочисленное значение.

OK! 4) Напишите функцию с именем getArithmeticFcn(), которая принимает символ выбранного 
математического оператора и возвращает соответствующую функцию в качестве указателя на функцию.

OK! 5) Добавьте в функцию main() вызов функции getArithmeticFcn().

OK! 6) Соедините все части вместе.

*/

using std::cout;
using std::cin;
//using std::string;

enum Operation
{
    addition        =1,    // сложение
    subtraction     =2,    // вычетание
    multiplication  =3,    // умножение
    division        =4,    // деление
    COUNT           =5
};


int add(int value1, int value2)
{
    return value1 + value2;
}

int subtract(int value1, int value2)
{
    return value1 - value2;
}

int multiply(int value1, int value2)
{
    return  value1 * value2;
}

int divide(int value1, int value2)
{
    return value1 / value2;
}

typedef int (*arithmeticFcn)(int, int);

// вызов функции
arithmeticFcn getArithmeticFcn(int choise) {
    switch (choise)
    {
        case 1: return add;
        case 2: return subtract; 
        case 3: return multiply;
        case 4: return divide;        
    }
}
 

void getClear() {
    system("cls");
}


// выбор операции
int choiseOperation() {   
   
    getClear();
    cout << "Выбор операции:\n" <<
        "1 - сложение\n" <<
        "2 - вычетание\n" <<
        "3 - умножение\n" <<
        "4 - деление\n";

    cout << "> ";
    int choise;
    cin >> choise;

    bool cheakchoise{ false };
    // проверка ввода
    for (int i = 1; i < (int)Operation::COUNT; ++i) {
       
        const auto enum_item = static_cast<Operation>(i);
        if (choise == enum_item)
        {
            cheakchoise = true;
        };       
    }

    if (cheakchoise) {
        return choise;
    }
    else {
        cout << "нет такого значения\n\n";
        system("pause");
        choiseOperation();
    }       
}

int main()
{
    setlocale(LC_ALL, "");
    
    int value1{ 0 };
    int value2{ 0 };
    int choise;
    int resultat;

    choise = choiseOperation();
    
    getClear();

    cout << "Первое значение: ";
    cin >> value1;
    cout << "Второе значение: ";
    cin >> value2;

    arithmeticFcn operation = getArithmeticFcn(choise);
    cout << "Математический результат: "<< operation(value1, value2);

    return 0;
}


