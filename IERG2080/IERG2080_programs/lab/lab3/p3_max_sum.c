#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    // input
    int len;
    scanf("%d", &len);

    int* num = (int*)malloc(len * sizeof(int));
    for(int i = 0; i < len; i ++)
    {
        scanf("%d", &num[i]);
    }

    // enumerate
    long tmp;
    long max = LONG_MIN;

    for(int i = 0; i < len; i ++)       // start num
    {
        tmp = 0;

        for(int j = i; j < len; j ++)   // end num 
        {
            tmp += num[j];
            if(tmp > max)
            {
                max = tmp;
            }
        }
    }

    // print
    printf("%ld", max);

    return 0;
}