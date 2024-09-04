#include <stdio.h>
#include <string.h>

int main()
{
    // input str
    int idx = 0;
    char num[33], cmp[33];

    scanf("%32s", num);
    if(strlen(num) == 0)
    {
        printf("True");
        return 0;
    }

    // check match
    for(int i = 0; num[i] != '\0'; i++)
    {
        if(num[i] == '(' || num[i] == '[' || num[i] == '{') // left
        {
            cmp[idx] = num[i];
            idx ++;
        }
        else    // right
        {
            if(idx < 0)
            {
                printf("False");
                return 0;
            }

            if(idx >= 0 && \
              ((cmp[idx - 1] == '(' && num[i] == ')') || \
               (cmp[idx - 1] == '[' && num[i] == ']') || \
               (cmp[idx - 1] == '{' && num[i] == '}'))   )  // same pair
            {
                idx --;
            }
            else    // different pair
            {
                printf("False");
                return 0;
            }
        }
    }
    
    if(idx == 0)
    {
        printf("True");
    }
    else
    {
        printf("False");
    }

    return 0;
}