#include <stdio.h>

int fact(int n)
{
    /*
    if(n == 0)
    {
        return 1;
    }
    */

    int f = 1;
    for(int i = 2; i <= n; i ++)
    {
        f *= i;
    }
    return f;
}

int comb(int n, int r)
{
    return fact(n) / (fact(n - r) * fact(r));
}

int main()
{
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j <= i; j ++)
        {
            printf("%d", comb(i, j));
            if(j != n)
            {
                printf(", ");
            }
        }
        printf("\n");
    }

}