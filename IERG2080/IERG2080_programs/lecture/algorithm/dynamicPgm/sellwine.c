#include <stdio.h>

#ifdef DEBUG
    #define dprint printf
#else
    #define dprint (void)
#endif

// returns the max profit can get starting with wine and year
int dp(int wine[], int year, int remain)
{
    if(remain == 1)
    {
        return year * wine[0];
    }

    int sell_left = wine[0] * year + dp(wine + 1, year + 1, remain - 1);            // max profit can get selling left
    int sell_right = wine[remain - 1] * year + dp(wine, year + 1, remain - 1);      // max profit can get selling right

    if(sell_left > sell_right)
    {
        dprint("year %d selling wine %d\n", year, wine[0]);
        return sell_left;
    }
    else
    {
        dprint("year %d selling wine %d\n", year, wine[remain - 1]);
        return sell_right;
    }
}

int main()
{
    int wine[5]  = {1, 3, 5, 1, 4};

    printf("%d", dp(wine, 1, 5));

    return 0;
}