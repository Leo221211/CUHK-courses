#include <stdio.h>

void tell_state(int dec, int state[])
{
    for(int j = 0; j < 8; j ++)
    {
        state[j] = dec % 2;
        dec /= 2;
    }
}

// if able to all turn of return 1
int toggle(int state[8], int bulbs[4][4])
{
    // test row
    for(int i = 0; i < 4; i ++)
    {
        if(state[i] == 1)   // toggle
        {
            for(int row = 0; row < 4; row ++)
            {
                bulbs[i][row] = (bulbs[i][row] + 1) % 2;
            }
        }
    }
    
    // test col
    for(int i = 0; i < 4; i ++)
    {
        if(state[i + 4] == 1)   // toggle
        {
            for(int row = 0; row < 4; row ++)
            {
                bulbs[row][i] = (bulbs[row][i] + 1) % 2;
            }
        }
    }

    // tell if turned off
    for(int row = 0; row < 4; row ++)
    {
        for(int col = 0; col < 4; col ++)
        {
            if(bulbs[row][col] == 1)    // has some bulbs on
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    // input
    int bulbs[4][4] = {0};
    for(int i = 0; i < 4; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            if(getchar() == '1')
            {
                bulbs[i][j] = 1;
            }
        }
        getchar();  // skip the '\n'
    }

    // brute force
    int tmp[4][4];
    int state[8];       // state of toggle

    for(int i = 0; i < 256; i ++)
    {
        // copy initial
        for(int row = 0; row < 4; row ++)
        {
            for(int col = 0; col < 4; col ++)
            {
                tmp[row][col] = bulbs[row][col];
            }
        }

        // tell state
        tell_state(i, state);

        // toggle
        if(toggle(state, tmp))      // offable
        {
            printf("true");
            return 0;
        }
        
    }

    printf("false");

    return 0;
}