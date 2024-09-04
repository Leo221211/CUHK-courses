#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);

    a ^= b;

    int count = 0;
    for(int i = 0; i < sizeof(int) * 8; i ++)
    {
        count += (a >> i) & 1;
    }

    printf("%d", count);

    return 0;
}