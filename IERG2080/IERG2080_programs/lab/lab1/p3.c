#include <stdio.h>
#include <stdlib.h>

struct Prisoner
{
    int index;
    struct Prisoner * before;
    struct Prisoner * after;
};

int main()
{
    // input
    int p_count, move;
    scanf("%d %d", &p_count, &move);

    // use linked list to store prisoners' data
    struct Prisoner * P_ptr;
    P_ptr = (struct Prisoner *)malloc(p_count * sizeof(struct Prisoner));
    
    // link the prisoners
    P_ptr[0].before = &P_ptr[p_count - 1];
    P_ptr[0].after = &P_ptr[1];

    for(int i = 1; i < p_count - 1; i ++)
    {
        P_ptr[i].before = &P_ptr[i - 1];
        P_ptr[i].after = &P_ptr[i + 1];
    }

    P_ptr[p_count - 1].before = &P_ptr[p_count - 2];
    P_ptr[p_count - 1].after = &P_ptr[0];

    // index of the prisoners
    for(int i = 0; i < p_count; i ++)
    {
        P_ptr[i].index = i;
    }


    // kill
    struct Prisoner * cur_ptr = &P_ptr[1];

    while(p_count > 1)
    {
        p_count --;

        (*((*cur_ptr).before)).after = (*cur_ptr).after;
        (*((*cur_ptr).after)).before = (*cur_ptr).before;

        for(int i = 0; i < move; i ++)
        {
            cur_ptr = (*cur_ptr).after;
        }
    }

    // output
    printf("%d", (*cur_ptr).index);

    // finish
    free(P_ptr);
    return 0;
}