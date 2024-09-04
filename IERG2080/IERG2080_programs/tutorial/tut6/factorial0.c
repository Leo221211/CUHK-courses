#include <stdio.h>

int main()
{
    // input 
    int n;
    scanf("%d", &n);

    // find
    int count = 0;
    for(int factor = 5; factor <= n; factor *= 5)
    {
        for(int i = 1; i * factor <= n; i ++)
        {
            count ++;
        }
    }

    // print
    printf("%d", count);

    return 0;
}