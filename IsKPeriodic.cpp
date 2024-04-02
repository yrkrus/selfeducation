#include <iostream>
#include <string>


using std::cout;
using std::cin;

bool IsKPeriodic(const std::string &str, int kratnost) {
    
    int lenght = str.length();

    if (lenght % kratnost != 0) {
        return true;
    }

    for (int i = 0; i < lenght - kratnost; ++i)
    {
        if (str[i] != str[i % kratnost])
        {
            return false; 
        }
    }

    return true;        
}


int main()
{    
    setlocale(LC_ALL, "");
   
    // ввод строки
    std::string stroka;
    cout << "ввод строки \n >> ";
    std::getline(cin, stroka);

   
    cout << "\n\nввод крастности \n >> ";
    unsigned short kratnost{ 0 };

    cin >> kratnost;
    if (!kratnost || kratnost == 0) {
        cout << "разрешен ввод только целочисленной кратности отличной от 0";
        return -1;
    }

    (IsKPeriodic(stroka, kratnost)) ? cout << "Строка кратна " << kratnost : cout << "Строка не кратна " << kratnost;
            
    return 0;

}

