#include <stdio.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int main()
{
    // find len and initialize
    int len;
    scanf("%d", &len);
    int cost[len];

    for(int i = 0; i < len; i ++)
    {
        scanf("%d", &cost[i]);
    }

    // initialize store
    int store[len];

    store[len - 1] = cost[len - 1];
    store[len - 2] = cost[len - 2];

    for(int i = len - 3; i >= 0; i --)
    {
        store[i] = cost[i] + min(store[i + 1], store[i + 2]);
    }

    printf("%d", min(store[0], store[1]));

    return 0;
}