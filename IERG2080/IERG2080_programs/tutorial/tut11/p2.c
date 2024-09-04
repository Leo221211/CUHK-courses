// have inputed a \n !!
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    int freq[26];
    int max = INT_MIN;

    // input
    int size;
    scanf("%d", &size);
    getchar();  // get the \n
    char* str = (char*)malloc(size * sizeof(char));
    for(int i = 0; i < size; i ++)
    {
        scanf("%c", &str[i]);
    }

    for(int i = 0; i < size; i ++)      // start with index i
    {
        for(int j = 0; j < 26; j ++)    // initialize freq
        {
            freq[j] = 0;
        }

        for(int j = 0; j + i < size; j ++)  // what's the longest in thic case
        {
            if(freq[str[j + i] - 'a'] == 1) // repeated
            {
                max = (max > j ? max : j);
                break;
            }
            else
            {
                freq[str[j + i] - 'a'] ++;
            }
        }
    }

    printf("%d", max);

    return 0;
}