#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(int a[], const int n, const int Low, const int High, int i);
void Print(const int a[], const int n, int i);
int MinOddIndex(const int a[], const int n, int i);

int main()
{
    srand((unsigned)time(NULL));

    const int n = 10;                  // кількість елементів
    const int Low = -10;               // межі діапазону значень
    const int High = 35;
    int a[n];

    Create(a, n, Low, High, 0);

    cout << "a = ";
    Print(a, n, 0);
    cout << endl;

    int idx = MinOddIndex(a, n, 0);

    if (idx == -1)
        cout << "Непарних елементів немає" << endl;
    else
        cout << "Індекс найменшого непарного елемента: " << idx
             << " (a[" << idx << "] = " << a[idx] << ")" << endl;

    // масив не змінювався, тому другий раз його не виводимо
    return 0;
}

// рекурсивне заповнення масиву випадковими числами з діапазону [Low; High]
void Create(int a[], const int n, const int Low, const int High, int i)
{
    if (i >= n)
        return;
    a[i] = Low + rand() % (High - Low + 1);
    Create(a, n, Low, High, i + 1);
}

// рекурсивне виведення масиву в один рядок (формат setw(4))
void Print(const int a[], const int n, int i)
{
    if (i >= n)
        return;
    cout << setw(4) << a[i];
    Print(a, n, i + 1);
}

// рекурсивний пошук індексу найменшого непарного елемента;
// повертає -1, якщо непарних елементів немає
int MinOddIndex(const int a[], const int n, int i)
{
    if (i >= n)
        return -1;

    int rest = MinOddIndex(a, n, i + 1);   // найкращий індекс серед a[i+1..n-1]

    if (a[i] % 2 != 0 && (rest == -1 || a[i] <= a[rest]))
        return i;                          // <= щоб при рівних значеннях був перший індекс, як в циклі
    return rest;
}