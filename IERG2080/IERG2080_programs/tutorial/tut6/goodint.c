#include <stdio.h>

int main()
{
    // input 
    int n, a, b;

    scanf("%d%d%d", &n, &a, &b);

    // find
    int i;
    for(i = 1; n != 0; i ++)
    {
        if( i % a == 0)
        {
            n --;
        }
        else if(i % b == 0)
        {
            n --;
        }
    }

    // print
    printf("%d", i-1);


    return 0;
}