// if no '\n' no output?

#include <stdio.h>
int main()
{
    int a,i;
    // scanf("%d", &a);
    printf("%d", fileno(stdout));
    i = fileno(stdout);
    // printf("%d\n", i);

    

    return 0;
}