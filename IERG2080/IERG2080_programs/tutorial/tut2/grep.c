#include <stdio.h>
#include <ctype.h>  // isalpha() 0 for no
#include <string.h>

// compare 2 chars; same 1 diff 0
int charcmp(char str, char exp);

// compare 2 strs; same 1 diff 0
int grep(char str[], char exp[]);

// count the max num of repeat
int cnt_rpt(char str[], char exp);

int main()
{
    char str[21], exp[21];
    scanf("%20s%20s", str, exp);

    if(grep(str, exp))
    {
        printf("True");
    }
    else
    {
        printf("False");
    }

    return 0;
}

int grep(char str[], char exp[])
{
    if(strlen(str) == 0 && strlen(exp) == 0)
    {
        return 1;
    }
    else
    {
        if(exp[1] != '*')   // star
        {
            if(charcmp(str[0], exp[0]) == 0)    // diff
            {
                return 0;
            }

            return grep(str + 1, exp + 1);
        }
        else                // not star
        {
            for(int i = cnt_rpt(str, exp[0]); i >= 0; i --)
            {
                if(grep(str + i, exp +2) == 1)
                {
                    return 1;
                }
            }

            return 0;
        }
    }
}

int cnt_rpt(char str[], char exp)
{
    int cnt = 0;

    for(int i = 0; str[i] != '\0'; i ++)
    {
        if(charcmp(str[i], exp)) // same
        {
            cnt ++;
        }
        else
        {
            break;
        }
    } 

    return cnt;
}

int charcmp(char str, char exp)
{
    if(exp == '.')
    {
        return 1;
    }

    if(exp == str)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}