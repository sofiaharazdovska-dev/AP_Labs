#include <iostream>
#include <string>
using namespace std;

int Count(const string s)
{
    int k = 0;

    // size_t — беззнаковий цілий тип для розмірів і позицій (індексів)
    // у рядку. Саме його повертає s.find.
    size_t pos = 0;

    // s.find(символи, pos) — шукає в рядку s, починаючи з позиції pos.
    // Тут find_first_of("+-=") шукає перший символ, який є в наборі "+-=".
    // Повертає індекс знайденого символа, а якщо нічого немає — string::npos.
    //
    // != -1 — перевірка "знайшли?". string::npos — це максимальне
    // значення size_t, яке дорівнює -1, перетвореному в беззнаковий тип.
    // Тому "!= -1" працює, але зрозуміліше й надійніше писати "!= string::npos".
    while ((pos = s.find_first_of("+-=", pos)) != string::npos)
    {
        k++;      // знайшли ще один знак
        pos++;    // переходимо до наступного символа, щоб не знайти той самий
    }
    return k;
}

string Change(string& s)
{
    size_t pos = 0;

    while ((pos = s.find_first_of("+-=", pos)) != string::npos)
    {
        // s.replace(pos, 1, "**") — замінює 1 символ, що стоїть на позиції pos,
        // на рядок "**".
        s.replace(pos, 1, "**");

        pos += 2;  // перестрибуємо вставлені зірочки
    }
    return s;
}

int main()
{
    string str;
    cout << "Enter string:" << endl;

    // getline(cin, str) — зчитує з клавіатури цілий рядок разом із пробілами
    // до натискання Enter і записує його в str.
    // (cin >> str зупинився б на першому пробілі.)
    getline(cin, str);

    cout << "String contained " << Count(str) << " symbols '+', '-', '='" << endl;

    string dest = Change(str);
    cout << "Modified string (param) : " << str << endl;
    cout << "Modified string (result): " << dest << endl;

    return 0;
}