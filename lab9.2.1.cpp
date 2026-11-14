#include <stdio.h>
#include <math.h>

#define Z 3     // змінюй: 3 -> перша гілка, 0 або 15 -> друга

#define SQR(a)    ((a)*(a))
#define MAX(a,b)  (((a)>(b))?(a):(b))
#define MIN(a,b)  (((a)<(b))?(a):(b))
#define ABS(a)    (((a)<0)?-(a):(a))
#define PRINTR(w) printf(#w " = %f\n", (double)(w))

int main()
{
    double x, y, w;
    char ch;

    do
    {
        printf("x = "); scanf("%lf", &x);
        printf("y = "); scanf("%lf", &y);

#if Z >= 1 && Z < 10
        puts("Branch 1: max^2(x+y, x+z)");
        w = SQR(MAX(x + y, x + Z));
#else
        puts("Branch 2: min(x^2, 5|y-z|)");
        w = MIN(SQR(x), 5 * ABS(y - Z));
#endif
        PRINTR(w);

        puts("Repeat? y/n");
        scanf(" %c", &ch);
    } while (ch == 'y');

    return 0;
}