// Лабораторна робота № 5.4
#include <iostream>
#include <cmath>
using namespace std;

const int UP = 19; // upper bound of the sum

// the term of the sum: sqrt( sin^2(k) + cos^2(N/k) )
double f(const int k, const int N)
{
    return sqrt(pow(sin(1. * k), 2) + pow(cos(1. * N / k), 2));
}

// iterative
double S0(const int N)
{
    double s = 0;
    for (int k = N; k <= UP; k++)
        s += f(k, N);
    return s;
}

// recursion: going up, k++
double S1(const int N, const int k)
{
    if (k > UP)
        return 0;
    else
        return f(k, N) + S1(N, k + 1);
}

// recursion: going down, k--
double S2(const int N, const int k)
{
    if (k < N)
        return 0;
    else
        return f(k, N) + S2(N, k - 1);
}

// recursion with accumulator, k++
double S3(const int N, const int k, double t)
{
    t = t + f(k, N);
    if (k >= UP)
        return t;
    else
        return S3(N, k + 1, t);
}

// recursion with accumulator, k--
double S4(const int N, const int k, double t)
{
    t = t + f(k, N);
    if (k <= N)
        return t;
    else
        return S4(N, k - 1, t);
}

int main()
{
    int N;
    cout << "N = "; cin >> N;

    cout << "(iter)        S0 = " << S0(N) << endl;
    cout << "(rec up ++)   S1 = " << S1(N, N) << endl;
    cout << "(rec up --)   S2 = " << S2(N, UP) << endl;
    cout << "(rec down ++) S3 = " << S3(N, N, 0) << endl;
    cout << "(rec down --) S4 = " << S4(N, UP, 0) << endl;

    return 0;
}
