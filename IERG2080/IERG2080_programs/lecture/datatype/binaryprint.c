#include <stdio.h>

void hexdumpf(float *x)
{
    // size of unsigned char is i Byte, and stores from 0 ~ 255, use %x to print unsigned char in Ox form
    unsigned char *ptr = (unsigned char *)x;

    printf("%f is hexa is: ", *x);
    for(int i = 0; i < sizeof(float); i ++) // sizeof(flaot) / sizeof(unsigned char) = number of repetition; sizeof(unsigned char) == 1
    {
        printf("%02X ", ptr[i]);
    }
    putchar('\n');

    printf("%f in binary is: ", *x);
    for(int i = 0; i < sizeof(float); i ++)
    {
        for(int j = 0; j < 8; j ++)             // 1 Byte is 8 bits
        {
            printf("%d", (ptr[i] >> j) & 1);

            if(j == 3)
            {
                putchar(' ');
            }
        }
        putchar(' ');
    }
    putchar('\n');
    
}

void biprintf(float *x)
{
    printf("%f in binary is: ", *x);
    for(int i = 0; i < sizeof(float) * 4; i ++)
    {
        // printf("%d ", (((*x) >> i) & 1);
        // wrong: can't >> a float, int only. 
        // for any non-integer, use unsigned char, then use >>
    }
    putchar('\n');
}

int main()
{
    float x = 0.1;

    // biprintf(&x);
    hexdumpf(&x);

    printf("%f in decimal is: %.30f", x, x);

    return 0;    
}