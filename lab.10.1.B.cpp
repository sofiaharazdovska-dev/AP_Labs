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
    union
    {
        int programming;     // Комп'ютерні науки
        int numericalMethods; // Інформатика
        int pedagogy;        // решта спеціальностей
    };
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
const int COLUMNS = 9;

int ColumnWidth(int col)
{
    static const int widths[COLUMNS] = { 3, 15, 4, 23, 6, 10, 13, 15, 10 };
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
    cin >> ws; //ws - пропусти пробіли та переноси рядка
    getline(cin, s.surname);
    cout << "  курс: ";
    cin >> s.course;
    s.speciality = ReadSpeciality();
    s.physics = ReadGrade("фізики");
    s.math = ReadGrade("математики");

    switch (s.speciality)
    {
    case COMPUTER_SCIENCE:
        s.programming = ReadGrade("програмування");
        break;
    case INFORMATICS:
        s.numericalMethods = ReadGrade("чисельних методів");
        break;
    default:
        s.pedagogy = ReadGrade("педагогіки");
        break;
    }
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
        "№", "Прізвище", "Курс", "Спеціальність", "Фізика",
        "Математика", "Програмування", "Чисельні методи", "Педагогіка"
    };
    PrintLine('=');
    for (int i = 0; i < COLUMNS; i++)
        PrintCell(titles[i], ColumnWidth(i), true);
    cout << "|" << endl;
    PrintLine('-');
}

void PrintRow(const Student& s, int number)
{
    string programming, numerical, pedagogy;
    switch (s.speciality)
    {
    case COMPUTER_SCIENCE:
        programming = to_string(s.programming);
        break;
    case INFORMATICS:
        numerical = to_string(s.numericalMethods);
        break;
    default:
        pedagogy = to_string(s.pedagogy);
        break;
    }

    PrintCell(to_string(number), ColumnWidth(0), false);
    PrintCell(s.surname, ColumnWidth(1), true);
    PrintCell(to_string(s.course), ColumnWidth(2), false);
    PrintCell(specialityStr[s.speciality], ColumnWidth(3), true);
    PrintCell(to_string(s.physics), ColumnWidth(4), false);
    PrintCell(to_string(s.math), ColumnWidth(5), false);
    PrintCell(programming, ColumnWidth(6), false);
    PrintCell(numerical, ColumnWidth(7), false);
    PrintCell(pedagogy, ColumnWidth(8), false);
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

// третя оцінка студента (залежить від спеціальності)
int ThirdGrade(const Student& s)
{
    switch (s.speciality)
    {
    case COMPUTER_SCIENCE: return s.programming;
    case INFORMATICS:      return s.numericalMethods;
    default:               return s.pedagogy;
    }
}

// середній бал студента за трьома предметами
double AverageGrade(const Student& s)
{
    return (s.physics + s.math + ThirdGrade(s)) / 3.0;
}

// 1. кількість студентів, які вчаться без трійок (тільки 4 і 5)
int CountWithoutThrees(const Student* students, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
        if (students[i].physics >= 4 &&
            students[i].math >= 4 &&
            ThirdGrade(students[i]) >= 4)
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