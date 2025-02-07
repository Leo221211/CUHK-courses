#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // function test
    puts("hello world 1\n");

    char str[20];
    scanf("%s", str);
    printf("%ld\n", strtol(str, NULL, 0));

    return 0;
}