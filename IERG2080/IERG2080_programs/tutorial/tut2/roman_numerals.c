#include <stdio.h>

int main()
{
    // input and covert
    int num;
    int dig[4];

    scanf("%d", &num);
    dig[0] = num / 1000;
    dig[1] = num / 100 % 10;
    dig[2] = num / 10 % 10;
    dig[3] = num % 10;

    // print thousands
    for(int i = 0; i < dig[0]; i ++)
    {
        putchar('M');
    }

    // print hundreds
    if(dig[1] <= 3)
    {
        for(int i = 0; i < dig[1]; i ++)
        {
            putchar('C');
        }
    }
    else if(dig[1] == 4)
    {
        printf("CD");
    }
    else if(5 <= dig[1] && dig[1] <= 8)
    {
        putchar('D');
        for(int i = 0; i < dig[1] - 5; i ++)
        {
            putchar('C');
        }
    }
    else
    {
        printf("CM");
    }

    // print tens
    if(dig[2] <= 3)
    {
        for(int i = 0; i < dig[2]; i ++)
        {
            putchar('X');
        }
    }
    else if(dig[2] == 4)
    {
        printf("XL");
    }
    else if(5 <= dig[2] && dig[2] <= 8)
    {
        putchar('L');
        for(int i = 0; i < dig[2] - 5; i ++)
        {
            putchar('X');
        }
    }
    else
    {
        printf("XC");
    }

    // print units
    if(dig[3] <= 3)
    {
        for(int i = 0; i < dig[3]; i ++)
        {
            putchar('I');
        }
    }
    else if(dig[3] == 4)
    {
        printf("IV");
    }
    else if(5 <= dig[3] && dig[3] <= 8)
    {
        putchar('V');
        for(int i = 0; i < dig[2] - 5; i ++)
        {
            putchar('I');
        }
    }
    else
    {
        printf("IX");
    }

    return 0;
}