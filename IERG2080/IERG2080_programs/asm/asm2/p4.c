#include <stdio.h>

int main()
{
    // input n
    int n;
    scanf("%d", &n);

    for(int row = 0; row < 2*n + 3; row ++)
    {
        for(int col = 0; col < 4*n + 5; col ++)
        {
            if(row + col <= 2*n + 1)
            {
                putchar('.');
            }
            else if(row + col == 2*n + 2)
            {
                putchar('*');
            }
            else if(col - row > 2*n + 2);
            else if(col - row == 2*n + 2)
            {
                putchar('*');
            }
            else
            {
                if(row + 1 == n + 2)
                {
                    putchar('*');
                }
                else
                {
                    putchar('.');
                }
            }
        }
        putchar('\n');
    }


    return 0;
}