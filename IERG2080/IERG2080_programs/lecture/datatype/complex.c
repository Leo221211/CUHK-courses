#include <stdio.h>
#include <complex.h>

int main()
{
    double complex x;
    x = CMPLX(1.0, -1.0);
    printf("rec: %lf + %lfJ\n pol: %lf cis %lf", creal(x), cimag(x), cabs(x), carg(x));

    return 0;
}