// line 59: col = 0 is a must if no initialize inside the for loop
#include <stdio.h>

int main()
{
    int x, y, row = 0, col = 0;
    scanf("%d%d", &y, &x);

    for(; row < x; row ++)
    {
        for(; col < 2*y + 2*x - 2; col ++)
        {
            if(col + 1 <= y)
            {
                if((col + 1) + (row + 1) <= x)
                {
                    putchar('.');
                }
                else
                {
                    putchar('*');
                }
            }
            else if(col + 1 <= 2*y - 1)
            {
                if((2*y - 1) - (col + 1) + (row + 1) < x)
                {
                    putchar('.');
                }
                else
                {
                    putchar('*');
                }
            }
            else if(col + 1 <= 2*y - 1 + x)
            {
                if((col + 1) + (row + 1) - (2*y - 1) <= x)
                {
                    putchar('.');
                }
                else
                {
                    putchar('*');
                }
            }
            else
            {
                if((2*x - 1) + (2*y - 1) - (col + 1) + (row + 1) < x)
                {
                    putchar('.');
                }
                else
                {
                    putchar('*');
                }
            }
        }
        putchar('\n');
        col = 0;
    }

    return 0;
}