#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int Count(char* str)
{
    int k = 0;

    // проходимо по всьому рядку до '\0'
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == '+' || str[i] == '-' || str[i] == '=')
            k++;

    return k;
}

char* Change(char* str)
{
    size_t len = strlen(str);

    // найгірший випадок: кожен символ стає "**", тому 2 * len + 1
    char* tmp = new char[2 * len + 1];
    char* t = tmp;
    tmp[0] = '\0';

    size_t i = 0;
    while (str[i] != 0)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '=')
        {
            *t++ = '*';   // замість знака записуємо дві зірочки
            *t++ = '*';
            *t = '\0';
            i++;
        }
        else
        {
            *t++ = str[i++];   // звичайний символ копіюємо без змін
            *t = '\0';
        }
    }

    strcpy(str, tmp);   // результат також у параметрі str
    return tmp;
}

int main()
{
    char str[101];
    cout << "Enter string:" << endl;
    cin.getline(str, 101);

    cout << "String contained " << Count(str) << " symbols '+', '-', '='" << endl;

    char* dest = Change(str);
    cout << "Modified string (param) : " << str << endl;
    cout << "Modified string (result): " << dest << endl;

    delete[] dest;
    return 0;
}