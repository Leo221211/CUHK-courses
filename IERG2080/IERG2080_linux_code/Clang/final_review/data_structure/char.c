#include <stdio.h>

int main()
{
    unsigned char a = 1;

    scanf("%c", &a);
    printf("%02x\n", (char)EOF);
    printf("%02x\n", (signed char)EOF);
    printf("%02x\n", (unsigned char)EOF);
    
    scanf("%hhd", &a);
    printf("%X\n", a);
    scanf("%hhu", &a);
    printf("%X\n", a);

    return 0;

    pack(1)
    a:4
    b:5
    v:4
    char d;
    d:4
}