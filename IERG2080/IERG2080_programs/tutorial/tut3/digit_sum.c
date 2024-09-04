#include <stdio.h>

int tell_dig(int num)
{
    int dig = 0;
    for(int i = 1; num / i > 0; i *= 10, dig ++);
    return dig;
}

int find_sum(int num)
{
    int sum = 0;
    int n = 1;
    for(int i = 1; i <= tell_dig(num); i ++, n *= 10)
    {
        sum += num / n % 10;
    }

    return sum;
}

int main()
{
    int num;
    scanf("%d", &num);

    while(tell_dig(num) > 1)
    {
        num = find_sum(num);
    }

    printf("%d", find_sum(num));

    return 0;
}