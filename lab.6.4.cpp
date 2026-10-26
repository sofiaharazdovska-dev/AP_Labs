#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utility>
using namespace std;

// виведення масиву в один рядок (рекурсивно)
void printArray(const double* a, int n, int i = 0)
{
    if (i >= n)                      // база: дійшли до кінця масиву
    {
        cout << endl;
        return;
    }
    cout << setw(9) << fixed << setprecision(2) << a[i];
    printArray(a, n, i + 1);         // наступний елемент
}

// заповнення масиву випадковими дійсними числами з діапазону [-50; 50] (рекурсивно)
void fillArray(double* a, int n, int i = 0)
{
    if (i >= n) return;              // база: елементи закінчились
    a[i] = (rand() % 10001) / 100.0 - 50.0;
    fillArray(a, n, i + 1);
}

// 1.1 сума додатних елементів (рекурсивно)
double sumPositive(const double* a, int n, int i = 0)
{
    if (i >= n) return 0;                    // база: елементів нема, сума 0
    double sum = sumPositive(a, n, i + 1);   // сума всього, що правіше за i
    if (a[i] > 0)
        sum += a[i];                         // додаємо поточний, якщо він додатний
    return sum;
}

// номер позиції елемента з найбільшим модулем (рекурсивно)
// iMax - позиція "рекордсмена" на поточний момент
int findMaxModulusIndex(const double* a, int n, int i = 1, int iMax = 0)
{
    if (i >= n) return iMax;                 // база: усе переглянули, повертаємо результат
    if (fabs(a[i]) > fabs(a[iMax])) iMax = i;   // знайшли кращого - запамʼятовуємо
    return findMaxModulusIndex(a, n, i + 1, iMax);
}

// номер позиції елемента з найменшим модулем (рекурсивно)
// iMin - позиція "рекордсмена" на поточний момент
int findMinModulusIndex(const double* a, int n, int i = 1, int iMin = 0)
{
    if (i >= n) return iMin;                 // база: усе переглянули, повертаємо результат
    if (fabs(a[i]) < fabs(a[iMin])) iMin = i;   // знайшли кращого - запамʼятовуємо
    return findMinModulusIndex(a, n, i + 1, iMin);
}

// 1.2 добуток елементів від позиції i до позиції iMin (iMin не входить)
double productBetween(const double* a, int i, int iMin)
{
    if (i >= iMin) return 1;                 // база: множити більше нічого, 1 - нейтральне для множення
    return a[i] * productBetween(a, i + 1, iMin);
}

// номер позиції найбільшого елемента серед позицій j, j+2, j+4, ...
// iMax - позиція "рекордсмена" на поточний момент
int findMaxIndexStep2(const double* a, int n, int j, int iMax)
{
    if (j >= n) return iMax;                 // база: позиції закінчились
    if (a[j] > a[iMax]) iMax = j;            // знайшли більший - запамʼятовуємо
    return findMaxIndexStep2(a, n, j + 2, iMax);   // крок 2: дивимось лише непарні позиції
}

// 2. впорядкування елементів на позиціях 0, 2, 4, ... за спаданням (рекурсивно)
void sortOddPositions(double* a, int n, int i = 0)
{
    if (i >= n) return;                             // база: позиції закінчились
    int iMax = findMaxIndexStep2(a, n, i + 2, i);   // де найбільший серед решти непарних позицій
    swap(a[i], a[iMax]);                            // ставимо його на позицію i
    sortOddPositions(a, n, i + 2);                  // те саме для наступної непарної позиції
}

int main()
{
    srand((unsigned)time(NULL));     // ініціалізація генератора випадкових чисел

    int n;
    cout << "n = ";
    cin >> n;
    if (n <= 0)                      // масив нульового або відʼємного розміру створити неможливо
    {
        cout << "n must be positive" << endl;
        return 1;
    }

    double* a = new double[n];       // динамічний масив з n дійсних елементів

    // заповнення випадковими дійсними числами з діапазону [-50; 50]
    fillArray(a, n);

    cout << "Array:" << endl;
    printArray(a, n);

    // 1.1 сума додатних елементів
    double sum = sumPositive(a, n);

    // 1.2 добуток елементів між max за модулем і min за модулем
    int iMax = findMaxModulusIndex(a, n);   // де стоїть max за модулем
    int iMin = findMinModulusIndex(a, n);   // де стоїть min за модулем
    if (iMax > iMin) swap(iMax, iMin);      // тепер iMax - це лівіша позиція (це лише назва)

    bool hasBetween = (iMin - iMax > 1);    // чи є хоча б один елемент між ними
    double prod = productBetween(a, iMax + 1, iMin);

    // 2. впорядкування елементів на непарних позиціях (індекси 0, 2, 4, ...) за спаданням
    sortOddPositions(a, n);

    // виведення результатів
    cout << "Sum of positive elements = " << fixed << setprecision(2) << sum << endl;
    if (hasBetween)
        cout << "Product between max and min by modulus = " << prod << endl;
    else
        cout << "No elements between max and min by modulus" << endl;

    cout << "Modified array:" << endl;
    printArray(a, n);

    delete[] a;                      // звільнення памʼяті, виділеної через new[]
    return 0;
}