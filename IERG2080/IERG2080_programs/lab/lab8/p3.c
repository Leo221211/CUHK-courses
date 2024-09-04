// wrong! can't change assign address of array!!
// watch out the index: i or i + 1 !!!
// macro of j !!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char input[256];
    char firstWord[256];
    char secondWord[256];

    printf("input: ");
    fgets(input, 256, stdin); 

    int i, j;

    firstWord[0] = input[0];
    for(i = 1; 'a' <= input[i] && input[i] <= 'z'; i ++)
    {
        firstWord[i]= input[i];
    }
    firstWord[i] = '\0';

    secondWord[0] = input[i ++];
    // for(int j = 1; 'a' <= input[i] && input[i] <= 'z'; i ++, j ++) : another macro for j !!
    for(j = 1; 'a' <= input[i] && input[i] <= 'z'; i ++, j ++)
    {
        secondWord[j]= input[i];
    }
    secondWord[j] = '\0';

    printf("%s\n", firstWord);
    printf("%s\n", secondWord);
}