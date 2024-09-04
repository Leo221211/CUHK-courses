#include <stdio.h>
#include <stdlib.h>
int max(int x, int y)
{
    return (x > y ? x : y);
}
int min(int x, int y)
{
    return (x < y ? x : y);
}
int main()
{
    int N;
    scanf("%d", &N);
    int *arr = (int *)malloc(N * sizeof(int));
    int *sum = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
        if (i == 0)
        {
            sum[i] = arr[i];
        }
        else
            sum[i] = sum[i - 1] + arr[i];
    }
    
    int max_sum = sum[0], min_sum = sum[0];
    for (int i = 1; i < N; i++)
    {
        max_sum = max(max_sum, sum[i]);
        min_sum = min(min_sum, sum[i]);
    }
    printf("%d", max_sum - min_sum);
}