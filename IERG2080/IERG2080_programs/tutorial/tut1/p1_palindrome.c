#include <stdio.h>

int main()
{
    // input num and get len
    int len = 0;
    char num[11];

    scanf("%10s", num);
    for(; num[len] != '\0'; len ++);

    // check palindrome
    for(int cnt = 0; cnt < (len + 1) / 2; cnt ++)
    {
        if(num[cnt] != num[len - 1 - cnt])
        {
            printf("False");
            return 0;
        }
    }

    printf("True");
    return 0;
}