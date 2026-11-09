// Варіант 2.
// Дано літерний рядок, який містить послідовність символів s[0], ..., s[n], ...
// 1. Підрахувати загальне число входжень символів '+', '-', '=' у цій послідовності.
// 2. Замінити кожен із символів '+', '-', '=' парою зірочок "**".

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

bool IsSign(char c)
{
    return c == '+' || c == '-' || c == '=';
}

int Count(const char* str, int i)
{
    if (str[i] == '\0')
        return 0;

    if (IsSign(str[i]))
        return 1 + Count(str, i + 1);
    else
        return Count(str, i + 1);
}

char* Change(char* dest, const char* str, char* t, int i)
{
    if (str[i] != '\0')
    {
        if (IsSign(str[i]))
        {
            *t++ = '*';
            *t++ = '*';
            *t = '\0';
            return Change(dest, str, t, i + 1);
        }
        else
        {
            *t++ = str[i];
            *t = '\0';
            return Change(dest, str, t, i + 1);
        }
    }
    else
    {
        *t = '\0';
        return dest;
    }
}

int main()
{
    char str[101];

    cout << "Enter string:" << endl;
    cin.getline(str, 101);

    cout << "String contained " << Count(str, 0) << " symbols '+', '-', '='" << endl;

    char* dest1 = new char[201]; // у найгіршому разі кожен символ стає "**"
    dest1[0] = '\0';
    char* dest2;

    dest2 = Change(dest1, str, dest1, 0);

    cout << "Modified string (param) : " << dest1 << endl;
    cout << "Modified string (result): " << dest2 << endl;

    delete[] dest1;
    return 0;
}