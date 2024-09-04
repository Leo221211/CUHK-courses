#include <stdio.h>
#include <math.h>

int main()
{
    float a = 1 / (float)0;
    printf("%d", INFINITY == a);

    return 0;
}