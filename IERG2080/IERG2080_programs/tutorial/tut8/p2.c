#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
    return a < b ? b : a;
}

int find_max(int array[], int start, int len, int prev)
{
    if(start == len)
    {
        return 0;
    }

    int want, not_want;

    // find want
    if(array[start] <= prev)
    {
        want = INT_MIN;
    }
    else
    {
        want = 1 + find_max(array, start + 1, len, array[start]);
    }

    // find not_want
    not_want = find_max(array, start + 1, len, prev);

    // return
    return max(want, not_want);
}

int main()
{
    // initialize
    int len;
    scanf("%d", &len);
    int array[len];

    for(int i = 0; i < len; i ++)
    {
        scanf("%d", &array[i]);
    }

    printf("%d", find_max(array, 0, len, INT_MIN));

    return 0;
}
