#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <iomanip>

const int N = 22; // кількість елементів у масиві
int mas[N];

// критерій: додатні, крім кратних 3
bool isSuitable(int x)
{
    return x > 0 && x % 3 != 0;
}

// формування масиву
void fillArray(int arr[], int size, int i = 0)
{
    if (i == size) return;               // умова виходу
    arr[i] = rand() % 46 - 10;           // min = -10, max = 35
    fillArray(arr, size, i + 1);
}

// виведення масиву одним рядком
void printArray(int arr[], int size, int i = 0)
{
    if (i == size)
    {
        cout << endl;                    // перенос рядка в самому кінці
        return;
    }
    cout << setw(4) << arr[i] << " ";
    printArray(arr, size, i + 1);
}

// кількість елементів, що задовольняють критерій
int countElements(int arr[], int size, int i = 0)
{
    if (i == size) return 0;
    return (isSuitable(arr[i]) ? 1 : 0) + countElements(arr, size, i + 1);
}

// сума елементів, що задовольняють критерій
int sumElements(int arr[], int size, int i = 0)
{
    if (i == size) return 0;
    return (isSuitable(arr[i]) ? arr[i] : 0) + sumElements(arr, size, i + 1);
}

// заміна цих елементів нулями
void replaceWithZero(int arr[], int size, int i = 0)
{
    if (i == size) return;
    if (isSuitable(arr[i]))
        arr[i] = 0;
    replaceWithZero(arr, size, i + 1);
}

int main()
{
    srand(time(0));

    fillArray(mas, N);
    cout << "Початковий масив:" << endl;
    printArray(mas, N);

    cout << "Кількість елементів: " << countElements(mas, N) << endl;
    cout << "Сума елементів: " << sumElements(mas, N) << endl;

    replaceWithZero(mas, N); // тільки ПІСЛЯ підрахунку
    cout << "Модифікований масив:" << endl;
    printArray(mas, N);

    return 0;
}