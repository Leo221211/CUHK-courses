#include <stdio.h>
#include <stdlib.h>

int *tr(int *a, int *b, int n, int *c)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            b[k] = a[i];
            k++;
        }
        else if (a[i] <= 0)
        {
            for (; a[i] <= 0; i++)
            {
                b[k] += a[i];
            }
            i--;
            k++;
        }
        if (b[k - 1] == 0)
        {
            *c++;
        }
    }
    return b;
}
int main()
{
    int N, j;
    int sum = 0;
    scanf("%d", &N);
    int *num1;
    int *num2;
    int num0 = 0;
    num1 = (int *)malloc(N * sizeof(int));
    num2 = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num1[i]);
        num2[i] = 0;
    }
    tr(num1, num2, N, &num0);
    if (num0 == 0)
    {
        for (j = 0; j < N - 1 && num2[j] != 0; j++)
        {
            if (num2[j] <= 0)
            {
                if (sum + num2[j] + num2[j + 1] > num2[j + 1])
                {
                    if (j == N - 2 && num2[j] + num2[j + 1] <= 0)
                        continue;
                    else
                    {
                        sum = sum + num2[j] + num2[j + 1];
                        j++;
                        continue;
                    }
                }
                else if (sum + num2[j] + num2[j + 1] <= num2[j + 1])
                {
                    sum = num2[j + 1];
                    j++;
                    continue;
                }
            }
            else if (num2[j] > 0)
            {
                if (sum > 0)
                    sum += num2[j];
                else
                    sum = num2[j];
            }
        }
        if (num2[j] > 0 && num2[j - 1] > 0)
        {
            if (sum > 0)
                sum += num2[j];
        }
        else
            ;
    }
    else if (num0 != 0)
    {
        for (j = 0; j < N - 1 && (num0 == 0 && num2[j] != 0); j++)
        {
            if (num2[j] == 0)
                num0--;
            else if (num2[j] < 0)
            {
                if (sum + num2[j] + num2[j + 1] > num2[j + 1])
                {
                    if (j == N - 2 && num2[j] + num2[j + 1] <= 0)
                        continue;
                    else
                    {
                        sum = sum + num2[j] + num2[j + 1];
                        j++;
                        continue;
                    }
                }
                else if (sum + num2[j] + num2[j + 1] <= num2[j + 1])
                {
                    sum = num2[j + 1];
                    j++;
                    continue;
                }
            }
            else if (num2[j] > 0)
            {
                if (sum > 0)
                    sum += num2[j];
                else
                    sum = num2[j];
            }
        }
        if (num2[j] > 0 && num2[j - 1] > 0)
        {
            if (sum > 0)
                sum += num2[j];
        }
        else
            ;
    }
    printf("%d", sum);
    free(num1);
    free(num2);
    return 0;
}