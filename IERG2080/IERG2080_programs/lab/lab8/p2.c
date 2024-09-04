#include <stdio.h>

// return a^b mod c
unsigned find_mod(unsigned long a, unsigned long b, unsigned long c)
{
    if(b == 1)
    {
        return a % c;
    }
    return (find_mod(a % c, b - 1, c) * (a % c)) % c;
}

int main()
{
    int a = 3, b = 5, c = 3;

    printf("%u", find_mod(a, b, c));

    return 0;
}