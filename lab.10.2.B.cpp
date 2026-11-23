#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Рівень В, варіант 2 (з поясненнями до функцій). Працює на macOS/Linux (UTF-8 термінал).
// На Windows додайте <Windows.h> та SetConsoleCP(1251) / SetConsoleOutputCP(1251).

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
        int programming;      // Комп'ютерні науки
        int numericalMethods; // Інформатика
        int pedagogy;         // решта спеціальностей
    };
};

// ---------- допоміжні функції (вирівнювання кирилиці в UTF-8) ----------
// Прототип = "анонс" функції: що вона повертає, як називається і що приймає.
// Саме тіло функції написане нижче, після main.
// Ці п'ять функцій потрібні лише для рівної таблиці: звичайний setw рахує байти,
// а кирилична літера в UTF-8 це 2 байти, тому таблиця "пливла" б.
// Рахує, скільки ЛІТЕР (а не байтів) у тексті
size_t Utf8Length(const string& s);
// Дописує пробіли СПРАВА до ширини width: текст притиснутий вліво (прізвища, назви)
string PadRight(const string& s, const int width);
// Дописує пробіли ЗЛІВА до ширини width: текст притиснутий вправо (числа)
string PadLeft(const string& s, const int width);
// Повертає ширину колонки за її номером (0 - перша колонка)
int ColumnWidth(const int col);
// Повертає загальну ширину таблиці (потрібна для ліній ==== і ----)
int TableWidth();

// ---------- введення з контролем помилок ----------
// ReadInt і ReadString перепитують користувача, поки він не введе коректне значення
int ReadInt(const string& prompt, const int minValue, const int maxValue);
string ReadString(const string& prompt);
Speciality ReadSpeciality();
Student ReadStudent();

// ---------- основні дії ----------
// p - вказівник на початок динамічного масиву студентів, N - їхня кількість,
// idx - індексний масив (номери студентів у потрібному порядку).
// const біля параметра = функція його лише читає і не змінює.
void Create(Student *p, const int N);
void Print(const Student *p, const int N);
bool IsWrongOrder(const Student& a, const Student& b);
void Sort(Student *p, const int N);
int CompareByKey(const Student& a, const Student& b);
void BuildIndex(const Student *p, int *idx, const int N);
void PrintIndexed(const Student *p, const int *idx, const int N);
int BinSearch(const Student *p, const int *idx, const int N,
              const string& surname, const int course, const Speciality speciality);

// ---------- вивід таблиці (кожна функція друкує свою частину) ----------
void PrintCell(const string& text, const int width, const bool alignLeft);
void PrintLine(const char symbol);
void PrintHeader();
void PrintRow(const Student& s, const int number);

int main()
{
    // кількість студентів вводить користувач; ReadInt не дасть ввести літери чи 0
    int N = ReadInt("Введіть кількість студентів N: ", 1, 1000);
    // new створює динамічний масив на N студентів; p - адреса його початку
    Student *p = new Student[N];
    // масив номерів для індексного впорядкування
    int *idx = new int[N];

    bool filled = false;     // чи вже введено дані
    bool indexReady = false; // чи актуальний індексний масив
    int menuItem;
    int found;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування (курс, спеціальність, прізвище за спаданням)" << endl;
        cout << " [4] - побудова індексного масиву" << endl;
        cout << " [5] - вивід даних за індексним масивом" << endl;
        cout << " [6] - бінарний пошук студента (прізвище, курс, спеціальність)" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = ReadInt("Введіть значення: ", 0, 6);
        cout << endl;

        // захист: без даних пункти 2-6 не мають сенсу
        // (continue переходить до наступного показу меню)
        if (menuItem >= 2 && !filled)
        {
            cout << "Спочатку введіть дані (пункт 1)." << endl;
            continue;
        }
        if ((menuItem == 5 || menuItem == 6) && !indexReady)
        {
            cout << "Спочатку побудуйте індексний масив (пункт 4)." << endl;
            continue;
        }

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            filled = true;
            indexReady = false;
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            indexReady = false; // позиції студентів змінились
            cout << "Масив впорядковано." << endl;
            break;
        case 4:
            BuildIndex(p, idx, N);
            indexReady = true;
            cout << "Індексний масив побудовано." << endl;
            break;
        case 5:
            PrintIndexed(p, idx, N);
            break;
        case 6:
        {
            cout << "Введіть ключі пошуку:" << endl;
            string surname = ReadString("  прізвище: ");
            int course = ReadInt("  курс (1-6): ", 1, 6);
            Speciality speciality = ReadSpeciality();
            cout << endl;
            if ((found = BinSearch(p, idx, N, surname, course, speciality)) != -1)
                cout << "Так, такий студент навчається (позиція " << found + 1
                     << " у масиві)." << endl;
            else
                cout << "Такого студента не знайдено." << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                    "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    // звільняємо пам'ять, виділену через new
    delete[] idx;
    delete[] p;
    return 0;
}

// ===================== допоміжні функції =====================
size_t Utf8Length(const string& s)
{
    size_t len = 0;
    // Кожну літеру кодує один початковий байт і, для кирилиці, ще один "продовжувальний"
    // (його біти починаються з 10). Рахуємо лише початкові байти = кількість літер.
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) len++;
    return len;
}

string PadRight(const string& s, const int width)
{
    // скільки літер уже є; недостаючу кількість доповнюємо пробілами
    int len = (int)Utf8Length(s);
    return s + string(len < width ? width - len : 0, ' ');
}

string PadLeft(const string& s, const int width)
{
    int len = (int)Utf8Length(s);
    return string(len < width ? width - len : 0, ' ') + s;
}

int ColumnWidth(const int col)
{
    // static const: масив створюється один раз і не змінюється.
    // Він лежить усередині функції, тому це не глобальна змінна.
    static const int widths[9] = { 3, 15, 4, 23, 6, 10, 13, 15, 10 };
    return widths[col];
}

int TableWidth()
{
    // 1 - остання вертикальна риска; кожна колонка = ширина + "| " + " " (3 символи)
    int total = 1;
    for (int i = 0; i < 9; i++)
        total += ColumnWidth(i) + 3;
    return total;
}

// ===================== введення =====================
int ReadInt(const string& prompt, const int minValue, const int maxValue)
{
    int value;
    while (true)
    {
        cout << prompt;
        // cin >> value дає false, якщо ввели не число (наприклад, літери)
        if (cin >> value && value >= minValue && value <= maxValue)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Помилка: введіть ціле число від " << minValue
             << " до " << maxValue << "." << endl;
        // clear знімає стан помилки cin, ignore викидає зайвий текст до кінця рядка
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string ReadString(const string& prompt)
{
    string s;
    // getline читає рядок цілком (разом із пробілами), цикл повторюється, поки рядок порожній
    do
    {
        cout << prompt;
        getline(cin, s);
        if (s.empty())
            cout << "Помилка: рядок не може бути порожнім." << endl;
    } while (s.empty());
    return s;
}

Speciality ReadSpeciality()
{
    cout << "  спеціальність: 0 - Комп'ютерні науки, 1 - Інформатика,\n"
         << "                 2 - Математика та економіка, 3 - Фізика та інформатика,\n"
         << "                 4 - Трудове навчання" << endl;
    // користувач вводить число 0-4, а (Speciality) перетворює його на значення enum
    return (Speciality)ReadInt("  введіть номер спеціальності: ", 0, 4);
}

Student ReadStudent()
{
    Student s;
    s.surname = ReadString("  прізвище: ");
    s.course = ReadInt("  курс (1-6): ", 1, 6);
    s.speciality = ReadSpeciality();
    s.physics = ReadInt("  оцінка з фізики (0-100): ", 0, 100);
    s.math = ReadInt("  оцінка з математики (0-100): ", 0, 100);

    switch (s.speciality)
    {
    case COMPUTER_SCIENCE:
        s.programming = ReadInt("  оцінка з програмування (0-100): ", 0, 100);
        break;
    case INFORMATICS:
        s.numericalMethods = ReadInt("  оцінка з чисельних методів (0-100): ", 0, 100);
        break;
    default:
        s.pedagogy = ReadInt("  оцінка з педагогіки (0-100): ", 0, 100);
        break;
    }
    return s;
}

void Create(Student *p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        p[i] = ReadStudent();
        cout << endl;
    }
}

// ===================== вивід =====================
void PrintCell(const string& text, const int width, const bool alignLeft)
{
    // alignLeft = true: текст вліво (PadRight), false: вправо (PadLeft)
    cout << "| " << (alignLeft ? PadRight(text, width) : PadLeft(text, width)) << " ";
}

void PrintLine(const char symbol)
{
    // string(n, c) створює рядок із n однакових символів c
    cout << string(TableWidth(), symbol) << endl;
}

void PrintHeader()
{
    const string titles[9] = {
        "№", "Прізвище", "Курс", "Спеціальність", "Фізика",
        "Математика", "Програмування", "Чисельні методи", "Педагогіка"
    };
    PrintLine('=');
    for (int i = 0; i < 9; i++)
        PrintCell(titles[i], ColumnWidth(i), true);
    cout << "|" << endl;
    PrintLine('-');
}

void PrintRow(const Student& s, const int number)
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

void Print(const Student *p, const int N)
{
    cout << "Список студентів групи" << endl;
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    PrintLine('=');
    cout << endl;
}

void PrintIndexed(const Student *p, const int *idx, const int N)
{
    // p[idx[i]]: беремо i-й номер з індексного масиву і за ним - студента з p
    cout << "Список студентів (індексне впорядкування; № - позиція в масиві)" << endl;
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[idx[i]], idx[i] + 1);
    PrintLine('=');
    cout << endl;
}

// ===================== впорядкування =====================
// true, якщо a і b стоять у неправильному порядку для фізичного впорядкування:
// курс - за зростанням, спеціальність (за назвою) - за зростанням,
// прізвище - за спаданням
bool IsWrongOrder(const Student& a, const Student& b)
{
    if (a.course != b.course)
        return a.course > b.course;
    int c = specialityStr[a.speciality].compare(specialityStr[b.speciality]);
    if (c != 0)
        return c > 0;
    return a.surname < b.surname;
}

// метод "бульбашки": міняємо місцями цілі структури
void Sort(Student *p, const int N)
{
    // tmp потрібна, щоб поміняти двох студентів місцями без втрати даних
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (IsWrongOrder(p[i1], p[i1 + 1]))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// порівняння за ключами: курс, назва спеціальності, прізвище (усе за зростанням)
// повертає -1, 0 або 1
int CompareByKey(const Student& a, const Student& b)
{
    if (a.course != b.course)
        return a.course < b.course ? -1 : 1;
    int c = specialityStr[a.speciality].compare(specialityStr[b.speciality]);
    if (c != 0)
        return c < 0 ? -1 : 1;
    c = a.surname.compare(b.surname);
    if (c != 0)
        return c < 0 ? -1 : 1;
    return 0;
}

// індексне впорядкування: масив p не змінюється, впорядковується масив індексів idx
void BuildIndex(const Student *p, int *idx, const int N)
{
    // спочатку індекси йдуть по порядку: 0, 1, 2, ... (масив p ще не впорядковано)
    for (int i = 0; i < N; i++)
        idx[i] = i;

    int tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (CompareByKey(p[idx[i1]], p[idx[i1 + 1]]) > 0)
            {
                tmp = idx[i1];
                idx[i1] = idx[i1 + 1];
                idx[i1 + 1] = tmp;
            }
}

// бінарний пошук по індексному масиву; повертає індекс студента в p або -1
int BinSearch(const Student *p, const int *idx, const int N,
              const string& surname, const int course, const Speciality speciality)
{
    Student key;
    key.surname = surname;
    key.course = course;
    key.speciality = speciality;

    // L, R - межі ділянки пошуку, m - її середина
    int L = 0, R = N - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;
        int c = CompareByKey(p[idx[m]], key);
        if (c == 0)
            return idx[m];
        if (c < 0)
            L = m + 1;   // середній менший за шуканого: шукаємо правіше
        else
            R = m - 1;   // середній більший: шукаємо лівіше
    }
    return -1;
}