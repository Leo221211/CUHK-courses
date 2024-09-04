#include <stdio.h>
#include "_bitsprint.c"

int main()
{
    unsigned long long a = -1;
    bitsprint(&a, sizeof(a));
    hexprint(&a, sizeof(a));

    return 0;
}