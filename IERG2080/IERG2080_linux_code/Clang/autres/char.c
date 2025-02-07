#include <stdio.h>
#include <string.h>

void bitsprint(void *ptr, int bytes)
{
    for(int i = 0; i < bytes; i ++)
    {
        for(int j = 0; j < 8; j ++)
        {
            printf("%d", ( (*((unsigned char*)ptr + i) >> j) & 1));
        }
        putchar(' ');
    }
    putchar('\n');
}

int main()
{
    char a;
    unsigned char b, c;

    /*
    scanf("%c", &a);
    printf("%d", a);
    */

    
    memcpy(&a, stdin, sizeof(char));
    bitsprint(&a, sizeof(a));
    

    return 0;
}
