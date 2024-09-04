#include <stdio.h>

#define DEBUG
#ifdef DEBUG
    #define dprint printf
#else
    #define dprint (void)
#endif

// returns the max profit can get starting with wine and year
int dp(int wine[], int year, int remain, int start)
{
    static int order[5] = {0};

    if(remain == 1)
    {
        order[4] = start + 1;
        dprint("current order: ");
        for(int i = 0; i < 5; i ++)
        {
            dprint("%d ", order[i]);
        }
        dprint("\n");
        return year * wine[start];
    }

    int sell_left = wine[start] * year + dp(wine, year + 1, remain - 1, start + 1);                 // max profit can get selling left
    int sell_right = wine[start + remain - 1] * year + dp(wine, year + 1, remain - 1, start);       // max profit can get selling right

    if(sell_left > sell_right)
    {
        order[year - 1] = start + 1;
        dprint("current order: ");
        for(int i = 0; i < 5; i ++)
        {
            dprint("%d ", order[i]);
        }
        dprint("\n");
        return sell_left;
    }
    else
    {
        order[year - 1] = start + remain;
        dprint("current order: ");
        for(int i = 0; i < 5; i ++)
        {
            dprint("%d ", order[i]);
        }
        dprint("\n");
        return sell_right;
    }
}

int main()
{
    int wine[5]  = {1, 3, 5, 1, 4};

    printf("%d", dp(wine, 1, 5, 0));

    return 0;
}