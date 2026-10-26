#include <iostream>   // cout, endl
#include <iomanip>    // setw для форматного виведення
#include <cstdlib>    // rand, srand
#include <ctime>      // time
using namespace std;

// Прототип звичайної рекурсивної функції (для масиву int)
int MaxEvenIndex(int* a, const int size, int i, int best);

// Прототип шаблонної рекурсивної функції (для масиву будь-якого цілого типу T)
template <typename T>
int MaxEvenIndex(T* a, const int size, int i, int best);

int main()
{
    srand((unsigned)time(NULL));                 // запуск генератора випадкових чисел

    const int n = 10;                            // розмір масивів

    // ---- Формування масивів ----
    int a[n];
    short b[n];
    long long c[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 41 - 20;                 // від -20 до 20
        b[i] = rand() % 2001 - 1000;             // від -1000 до 1000
        c[i] = rand() % 2001 - 1000;             // від -1000 до 1000
    }

    // ---- Виведення масивів (по одному рядку, форматне виведення) ----
    cout << "a: ";
    for (int i = 0; i < n; i++)
        cout << setw(6) << a[i];
    cout << endl;

    cout << "b: ";
    for (int i = 0; i < n; i++)
        cout << setw(6) << b[i];
    cout << endl;

    cout << "c: ";
    for (int i = 0; i < n; i++)
        cout << setw(6) << c[i];
    cout << endl << endl;

    // ---- Результати, по одному рядку на виклик ----
    int idx1 = MaxEvenIndex(a, n, 0, -1);        // звичайна функція
    cout << "MaxEvenIndex(a, n) = ";
    if (idx1 == -1) cout << "парних немає" << endl;
    else cout << a[idx1] << endl;

    int idx2 = MaxEvenIndex<int>(a, n, 0, -1);   // шаблон, T = int
    cout << "MaxEvenIndex<int>(a, n) = ";
    if (idx2 == -1) cout << "парних немає" << endl;
    else cout << a[idx2] << endl;

    int idx3 = MaxEvenIndex<short>(b, n, 0, -1); // шаблон, T = short
    cout << "MaxEvenIndex<short>(b, n) = ";
    if (idx3 == -1) cout << "парних немає" << endl;
    else cout << b[idx3] << endl;

    int idx4 = MaxEvenIndex<long long>(c, n, 0, -1); // шаблон, T = long long
    cout << "MaxEvenIndex<long long>(c, n) = ";
    if (idx4 == -1) cout << "парних немає" << endl;
    else cout << c[idx4] << endl;

    // Масиви не змінювались, тому повторно їх виводити не потрібно
    return 0;
}

// Звичайна рекурсивна функція: повертає індекс найбільшого парного елемента
int MaxEvenIndex(int* a, const int size, int i, int best)
{
    if (i >= size)                               // умова зупинки: масив закінчився
        return best;

    if (a[i] % 2 == 0 && (best == -1 || a[i] > a[best]))
        best = i;                                // запам'ятовуємо позицію найбільшого парного

    return MaxEvenIndex(a, size, i + 1, best);   // рекурсивний виклик
}

// Шаблонна рекурсивна функція: те саме, але для будь-якого цілого типу T
template <typename T>
int MaxEvenIndex(T* a, const int size, int i, int best)
{
    if (i >= size)
        return best;

    if (a[i] % 2 == 0 && (best == -1 || a[i] > a[best]))
        best = i;

    return MaxEvenIndex<T>(a, size, i + 1, best);
}