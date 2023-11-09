#include <iostream>
#include <vector>
#include <cstring>
#include <windows.h>

/*
Объявить переменные с помощью которых можно будет посчитать общую сумму покупки нескольких товаров. 
Например плитки шоколада, кофе и пакеты молока.
*/

using std::cout;
using std::cin;
using std::vector;
using std::string;

struct Tovar
{
    Tovar();
    Tovar(string name,int cost, int count);
    
    int _cost;
    int _count;
    string _name;

};

Tovar::Tovar()
{
}

Tovar::Tovar(string name, int cost, int count)
{
    _name = name;
    _cost = cost;
    _count = count;
};

Tovar *createTovar(string name, int cost, int count) {
   Tovar *array = new Tovar;

   array->_name = name;
   array->_cost = cost;
   array->_count = count;

   return array;
}

void showSumTovars(vector<Tovar> &array) {
    int size = array.size();
    int summa{ 0 };

    for (size_t i = 0; i < size; ++i) {
        summa = summa+(array[i]._count * array[i]._count);
    }

    cout << "Сумма товаров: " << summa;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    vector<Tovar> listTovars;

    int sum{ 0 };

    int size{ 0 };
    cout << "размерность массива товаров: ";
    cin >> size;      

    for (size_t i = 0; i < size; ++i)
    {
        
        system("cls");
        
        string name;
        cout << "Название товара: ";
        cin >> name;

        int count{ 0 };
        cout << "Кол-во " << name << ": ";
        cin >> count;

        int price{ 0 };
        cout << "Стоимость " << name << ": ";
        cin >> price; 

        Tovar *listtovar = createTovar(name, count, price);

        listTovars.push_back(*listtovar);      
    }
    
    system("cls");
    showSumTovars(listTovars);     

   
    return 0;   

}

