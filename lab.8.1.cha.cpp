#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int Count(char* s)
{
    int k = 0;
    char* t;
    int pos = 0;

    // strpbrk(рядок, набір) — шукає в рядку ПЕРШИЙ символ, який є
    // в наборі "+-=". Повертає вказівник на нього, а якщо таких
    // символів більше немає — повертає nullptr (цикл закінчується).
    while (t = strpbrk(s + pos, "+-="))
    {
        k++;
        pos = t - s + 1;   // t - s = індекс знайденого символа; +1 = йдемо далі
    }
    return k;
}

char* Change(char* s)
{
    // strlen(рядок) — повертає довжину рядка (кількість символів
    // до '\0', сам '\0' не рахується).
    // Беремо 2*довжина + 1: кожен знак стає "**" (довше вдвічі),
    // +1 — місце під '\0'.
    char* t = new char[2 * strlen(s) + 1];
    char* p;
    int pos1 = 0;
    *t = 0;   // робимо t порожнім рядком (перший символ '\0')

    while (p = strpbrk(s + pos1, "+-="))
    {
        int pos2 = p - s;   // індекс знайденого знака

        // strncat(куди, звідки, n) — дописує в кінець рядка "куди"
        // перші n символів із "звідки". Тут копіюємо шматок тексту
        // ДО знака (від pos1 до pos2) і не чіпаємо сам знак.
        strncat(t, s + pos1, pos2 - pos1);

        // strcat(куди, звідки) — дописує в кінець "куди" весь
        // рядок "звідки". Тут додаємо "**" замість знака.
        strcat(t, "**");

        pos1 = pos2 + 1;    // пропускаємо сам знак, йдемо далі
    }

    strcat(t, s + pos1);    // дописуємо залишок рядка після останнього знака

    // strcpy(куди, звідки) — копіює весь рядок "звідки" в "куди"
    // (разом із '\0'), затираючи те, що було. Тут результат
    // потрапляє назад у s, щоб він був і в параметрі.
    strcpy(s, t);

    return t;
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