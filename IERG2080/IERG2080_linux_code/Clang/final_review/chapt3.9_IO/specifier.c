#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("%.3d\n", 8);
    printf("%+d\n", 0);
    printf("%03d %-3d\n", 3, 1);
    printf("%e\n", 12312321.132313);
    printf("\v");
    printf("%d\n", atoi("1000"));
    printf("hello\012");


    return 0;
}