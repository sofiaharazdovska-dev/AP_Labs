// Lab_7_2_2.cpp
// < прізвище, ім’я автора >
// Лабораторна робота № 7.2.2)
// Опрацювання багатовимірних масивів рекурсивними способами.
// Варіант 2
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

// Заповнює випадковими числами один рядок rowNo (рекурсія по стовпцях)
void CreateRow(int** a, const int rowNo, const int n, const int Low,
    const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < n - 1)
        CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

// Заповнює всю матрицю (рекурсія по рядках)
void CreateRows(int** a, const int k, const int n, const int Low,
    const int High, int rowNo)
{
    CreateRow(a, rowNo, n, Low, High, 0);
    if (rowNo < k - 1)
        CreateRows(a, k, n, Low, High, rowNo + 1);
}

// Виводить один рядок rowNo (рекурсія по стовпцях)
void PrintRow(int** a, const int rowNo, const int n, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < n - 1)
        PrintRow(a, rowNo, n, colNo + 1);
    else
        cout << endl;
}

// Виводить усю матрицю (рекурсія по рядках)
void PrintRows(int** a, const int k, const int n, int rowNo)
{
    PrintRow(a, rowNo, n, 0);
    if (rowNo < k - 1)
        PrintRows(a, k, n, rowNo + 1);
    else
        cout << endl;
}

// Повертає максимальний елемент рядка rowNo, починаючи зі стовпця colNo
int MaxInRow(int** a, const int rowNo, const int n, int colNo)
{
    if (colNo == n - 1)                               // база рекурсії
        return a[rowNo][colNo];
    int maxRest = MaxInRow(a, rowNo, n, colNo + 1);   // максимум решти рядка
    if (a[rowNo][colNo] > maxRest)
        return a[rowNo][colNo];
    return maxRest;
}

// Повертає суму максимальних елементів рядків, починаючи з рядка rowNo
int SumRowMaxes(int** a, const int k, const int n, int rowNo)
{
    int sum = MaxInRow(a, rowNo, n, 0);               // максимум поточного рядка
    if (rowNo < k - 1)
        sum += SumRowMaxes(a, k, n, rowNo + 1);       // плюс наступні рядки
    return sum;
}

int main()
{
    srand((unsigned)time(NULL));

    int k, n;
    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;
    cout << endl;

    int** a = new int*[k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    int Low = -9, High = 9;

    CreateRows(a, k, n, Low, High, 0);
    PrintRows(a, k, n, 0);

    cout << "S = " << SumRowMaxes(a, k, n, 0) << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}