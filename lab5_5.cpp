#include <iostream>
using namespace std;

// Повертає кількість одиниць у двійковому записі n.
// depth — глибина рекурсії (передається за посиланням).
int f(int n, int &depth) {
    if (n == 0) {
        return 0;               // f(0) = 0
    }
    
    depth++;                    // ще один рекурсивний виклик
    return 1 + f(n & (n - 1), depth);
}

int main() 
{
    int n;
    cout << "Введіть n: ";
    cin >> n;

    int depth = 0;
    int ones = f(n, depth);

    cout << "Кількість одиниць: " << ones << endl;
    cout << "Глибина рекурсії: " << depth << endl;
    return 0;
}
