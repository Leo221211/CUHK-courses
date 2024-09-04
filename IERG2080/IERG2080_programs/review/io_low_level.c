#include <stdio.h>

int main()
{
    printf("%d", fileno(stdout));
    return 0;
}