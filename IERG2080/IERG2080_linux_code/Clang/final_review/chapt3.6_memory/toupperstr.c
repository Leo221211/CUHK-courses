#include <stdio.h>
#include <ctype.h>
void StringUpper(char *dest, char *src)
{
    while (*src)
    {
        *dest = toupper(*src); // convert char to upper case +4.dest; ++src
        ++dest;
        ++src;
    }
    *dest = 0;
}

int main(void)
{
    char input[5];
    printf("Please input a string: ");
    fgets(input, 5, stdin);
    //scanf("%5s", input);

    char output[5];

    StringUpper(output, input);

    printf("In upper case: %s\n", output);

    return 0;      
}