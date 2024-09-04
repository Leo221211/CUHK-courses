#include <stdio.h>

long cnt(int n)
{
    if(n == 1)
    {
        return 1;
    }
    else if(n == 2)
    {
        return 2;
    }
    else
    {
        return cnt(n - 1) + cnt(n - 2);
    }


}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%ld", cnt(n));

    return 0;
}