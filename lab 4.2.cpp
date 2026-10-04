#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double x, xp, xk, dx, R, y;

    // Введення параметрів
    std::cout << "R = "; std::cin >> R;
    std::cout << "xp = "; std::cin >> xp;
    std::cout << "xk = "; std::cin >> xk;
    std::cout << "dx = "; std::cin >> dx;

    std::cout << std::fixed;
    std::cout << "---------------------------" << std::endl;
    std::cout << "|" << std::setw(5) << "x" << "     |"
              << std::setw(7) << "y" << "       |" << std::endl;
    std::cout << "---------------------------" << std::endl;

    x = xp;
    while (x <= xk)
    {
        if (x <= -8)
        {
            y = -R;
        }
        else if (x > -8 && x < -R)
        {
            y = R * (x + R) / (8 - R);
        }
        else if (x >= -R && x <= R)
        {
            y = -std::sqrt(R * R - x * x);
        }
        else if (x > R && x < 5)
        {
            y = 2 * (x - R) / (5 - R);
        }
        else
        {
            y = 3;
        }

        std::cout << "|" << std::setw(7) << std::setprecision(2) << x
                  << "   |" << std::setw(10) << std::setprecision(3) << y
                  << "    |" << std::endl;

        x += dx; // Важливо: всередині циклу while
    }

    std::cout << "---------------------------" << std::endl;

    return 0;
}
