#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Works on macOS/Linux (UTF-8 terminal). On Windows, add <Windows.h>
// and SetConsoleCP(1251) / SetConsoleOutputCP(1251) as in your template.

enum Speciality
{
    COMPUTER_SCIENCE,    // Комп'ютерні науки
    INFORMATICS,         // Інформатика
    MATH_ECONOMICS,      // Математика та економіка
    PHYSICS_INFORMATICS, // Фізика та інформатика
    LABOR_TRAINING       // Трудове навчання
};

const string specialityStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та економіка",
    "Фізика та інформатика",
    "Трудове навчання"
};

struct Student
{
    string surname;
    int course;
    Speciality speciality;
    int physics;
    int math;
    int informatics;
};

// ---------- допоміжні функції для рівного виводу кирилиці (UTF-8) ----------
size_t Utf8Length(const string& s)
{
    size_t len = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) len++;
    return len;
}

string PadRight(const string& s, int width)
{
    int len = (int)Utf8Length(s);
    return s + string(len < width ? width - len : 0, ' ');
}

string PadLeft(const string& s, int width)
{
    int len = (int)Utf8Length(s);
    return string(len < width ? width - len : 0, ' ') + s;
}

// ---------- ширини колонок (без глобальних змінних) ----------
const int COLUMNS = 7;

int ColumnWidth(int col)
{
    static const int widths[COLUMNS] = { 3, 15, 4, 23, 6, 10, 11 };
    return widths[col];
}

int TableWidth()
{
    int total = 1;
    for (int i = 0; i < COLUMNS; i++)
        total += ColumnWidth(i) + 3;
    return total;
}

// ---------- введення ----------
Speciality ReadSpeciality()
{
    int s;
    do
    {
        cout << "  спеціальність (0 - Комп'ютерні науки, 1 - Інформатика,\n"
             << "                 2 - Математика та економіка, 3 - Фізика та інформатика,\n"
             << "                 4 - Трудове навчання): ";
        cin >> s;
    } while (s < 0 || s > 4);
    return (Speciality)s;
}

// оцінка за 5-бальною шкалою
int ReadGrade(const string& subject)
{
    int g;
    do
    {
        cout << "  оцінка з " << subject << " (1-5): ";
        cin >> g;
    } while (g < 1 || g > 5);
    return g;
}

Student ReadStudent()
{
    Student s;
    cout << "  прізвище: ";
    cin >> ws;
    getline(cin, s.surname);
    cout << "  курс: ";
    cin >> s.course;
    s.speciality = ReadSpeciality();
    s.physics = ReadGrade("фізики");
    s.math = ReadGrade("математики");
    s.informatics = ReadGrade("інформатики");
    return s;
}

void Create(Student* students, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        students[i] = ReadStudent();
        cout << endl;
    }
}

// ---------- вивід ----------
void PrintCell(const string& text, int width, bool alignLeft)
{
    cout << "| " << (alignLeft ? PadRight(text, width) : PadLeft(text, width)) << " ";
}

void PrintLine(char symbol)
{
    cout << string(TableWidth(), symbol) << endl;
}

void PrintHeader()
{
    const string titles[COLUMNS] = {
        "№", "Прізвище", "Курс", "Спеціальність", "Фізика", "Математика", "Інформатика"
    };
    PrintLine('=');
    for (int i = 0; i < COLUMNS; i++)
        PrintCell(titles[i], ColumnWidth(i), true);
    cout << "|" << endl;
    PrintLine('-');
}

void PrintRow(const Student& s, int number)
{
    PrintCell(to_string(number), ColumnWidth(0), false);
    PrintCell(s.surname, ColumnWidth(1), true);
    PrintCell(to_string(s.course), ColumnWidth(2), false);
    PrintCell(specialityStr[s.speciality], ColumnWidth(3), true);
    PrintCell(to_string(s.physics), ColumnWidth(4), false);
    PrintCell(to_string(s.math), ColumnWidth(5), false);
    PrintCell(to_string(s.informatics), ColumnWidth(6), false);
    cout << "|" << endl;
}

void Print(const Student* students, const int N)
{
    cout << "Список студентів групи" << endl;
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(students[i], i + 1);
    PrintLine('=');
    cout << endl;
}

// ---------- обчислення ----------

// середній бал студента за трьома предметами
double AverageGrade(const Student& s)
{
    return (s.physics + s.math + s.informatics) / 3.0;
}

// 1. кількість студентів, які вчаться без трійок (тільки 4 і 5)
int CountWithoutThrees(const Student* students, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
        if (students[i].physics >= 4 &&
            students[i].math >= 4 &&
            students[i].informatics >= 4)
            count++;
    return count;
}

// 2. відсоток студентів, у яких середній бал менший 4
double PercentAverageBelow4(const Student* students, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
        if (AverageGrade(students[i]) < 4)
            count++;
    return 100.0 * count / N;
}

int main()
{
    int N;
    do
    {
        cout << "Введіть кількість студентів N: ";
        cin >> N;
    } while (N <= 0);

    Student* students = new Student[N];
    Create(students, N);
    Print(students, N);

    cout << "Кількість студентів, які вчаться без трійок: "
         << CountWithoutThrees(students, N) << endl;
    cout << "Відсоток студентів із середнім балом менше 4: "
         << fixed << setprecision(2) << PercentAverageBelow4(students, N) << "%" << endl;

    delete[] students;
    return 0;
}