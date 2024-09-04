#include <stdio.h>
/*
problem: the previous max is out of the window
int main()
{
    // define sequence
    int seq[7] = {1, 3, 5, 4, 9, 10, 2};
    int len = 7;

    // define and initialize max
    int max = seq[0];

    // find max among first 3
    for(int i = 1; i < 3; i ++)
    {
        if(seq[i] > max)
        {
            max = seq[i];
        }
    }
    printf("%d ", max);

    // find max among the rest
    for(int i = 3; i < len; i ++)
    {
        if(seq[i] > max)
        {
            max = seq[i];
        }
        printf("%d ", max);
    }
}
*/

// find the biggest one among the previous 3
int find_max_3(int index, int array[])
{
    int max = array[index];

    if(array[index - 1] > max)
    {
        max = array[index - 1];
    }

    if(array[index - 2] > max)
    {
        max = array[index - 2];
    }

    return max;
}

int main()
{
    // define sequence
    int seq[7] = {10, 3, 5, 4, 9, 10, 2};
    int len = 7;

    // find largest
    for(int i = 2; i < len; i ++)
    {
        printf("%d ", find_max_3(i, seq));
    }

    return 0;
}