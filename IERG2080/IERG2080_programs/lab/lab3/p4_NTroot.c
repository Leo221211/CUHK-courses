#include <stdio.h>
#include <math.h>

#define SML_NUM 1e-7
#define ITR_NUM 1e7     // number of iteration
#define GEUSS 0         // initial geuss num

double fcubed(double x, double a, double b, double c, double d)
{
    return a * x * x * x + b * x * x + c * x + d;
}

double fprime(double x, double a, double b, double c)
{
    return 3*a*x*x + 2*b*x + c;
}

double delta(double a, double b, double c)
{
    return b*b - 4*a*c;
}

int main()
{
    // Newtown method find root1
    double a, b, c, d;
    double x1, x0;

    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

    x0 = x1 = GEUSS;

    for(int i = 0; i < ITR_NUM; i ++)
    {
        x0 = x1;

        if(fprime(x0, a, b, c) == 0)
        {
            printf("unale to solve: error 1");
            return 0;
        }

        x1 = x0 - fcubed(x0, a, b, c, d) / fprime(x0, a, b, c);

        if(fabs(x0 - x1) < SML_NUM)
        {
            break;
        }
    }

    if(fabs(fcubed(x1, a, b, c, d)) > SML_NUM)  // not precise enough
    {
        printf("unale to solve: error 2");
        return 0;
    }

    // quadratic equation
    double A, B, C;
    double x2, x3;
    double delta;

    A = a;
    B = b + a*x1;
    C = c + (b + a*x1) * x1;

    delta = B*B - 4*A*C;

    if(delta > SML_NUM)
    {
        x2 = (-B + sqrt(delta)) / (2*A);
        x3 = (-B - sqrt(delta)) / (2*A);
        printf("3 real roots: x1 = %lf, x2 = %lf, x3 = %lf", x1, x2, x3);
    }
    else if(delta < 0)
    {
        printf("2 complex roots and 1 real root: x1 = %lf", x1);
    }
    else
    {
        x2 = (-B + sqrt(delta)) / (2*A);
        printf("3 real roots: x1 = %lf, x2 = x3 = %lf", x1, x2);
    }

    return 0;
}