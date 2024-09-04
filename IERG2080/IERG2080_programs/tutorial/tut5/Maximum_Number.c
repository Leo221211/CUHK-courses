#include <stdio.h>
#define MAX_LEN_BAN 20

int main()
{
    int banned[MAX_LEN_BAN] = {0};
    int max_int, max_sum;
    long sum = 0;
    int chosen_num = 0;

    // input
    for(int i = 0; i < MAX_LEN_BAN; i ++)
    {
        scanf("%d", &banned[i]);

        if(banned[i] == 0)
        {
            break;
        }
    }

    scanf("%d%d", &max_int, &max_sum);

    // cal
    for(int i = 1; i <= max_int; i ++)
    {
        // check banned
        for(int j = 0; banned[j] != 0; j ++)
        {
            if(banned[j] == i)
            {
                goto label;
            }
        }

        sum += i;
        if(sum > max_sum)
        {
            break;
        }
        chosen_num ++;

        label:;
    }

    // print
    printf("%d", chosen_num);
}