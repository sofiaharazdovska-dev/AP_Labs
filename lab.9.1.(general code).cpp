//////////////////////////////////////////////////////////////////////////////
// Lab_9_1.cpp
// Обчислення e^(-x) за допомогою ряду Тейлора (варіант 2)
// Усе зібрано в один файл (без розділення на модулі)
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Глобальні змінні (раніше var.h + var.cpp)
namespace nsVar {
    int n;                                  // кількість доданків
    double x, x_p, x_k, dx, e, a, s;        // аргумент, межі, крок, точність, доданок, сума
}

//////////////////////////////////////////////////////////////////////////////
// Обчислення доданка (раніше dod.h + dod.cpp)
namespace nsDod {
    void dod() {
        using namespace nsVar;
        a *= -x / n;    // доданок домножується на коефіцієнт рекурентності (-x/n)
    }
}

//////////////////////////////////////////////////////////////////////////////
// Обчислення суми ряду (раніше sum.h + sum.cpp)
namespace nsSum {
    void sum() {
        using namespace nsVar;
        n = 0;              // кількість доданків
        a = 1;              // перший доданок (при n = 0)
        s = a;              // початкова сума
        do {
            n++;
            nsDod::dod();   // виклик процедури обчислення доданку
            s += a;
        } while (fabs(a) > e);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Головна функція
using namespace nsDod;
using namespace nsSum;
using namespace nsVar;

int main()
{
    cout << "x_p = "; cin >> x_p;
    cout << "x_k = "; cin >> x_k;
    cout << "dx  = "; cin >> dx;
    cout << "e   = "; cin >> e;
    cout << endl;

    // заголовок і шапка таблиці
    cout << "Taylor series: exp(-x)" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << setw(8)  << "x"
         << setw(15) << "Sum"
         << setw(15) << "exp(-x)"
         << setw(8)  << "n" << endl;
    cout << "-------------------------------------------------" << endl;

    x = x_p;
    while (x <= x_k) {
        sum();          // виклик процедури обчислення суми

        cout << fixed << setprecision(6)
             << setw(8)  << x
             << setw(15) << s
             << setw(15) << exp(-x)
             << setw(8)  << n << endl;

        x += dx;
    }

    cin.ignore();
    cin.get();
    return 0;
}