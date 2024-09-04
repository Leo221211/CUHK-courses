/**
 * 'O' (capital letter O) for white(2)
 * '#' for black(1)
 * '.' for empty cell
 * 
 * function: print out the game board, the numbers or coordinate, and the now situation
 * input: const int* board
 * 
 * workflow: count black and white
 *           print first row
 *           for loop to print the other rows
*/

#ifndef DUI
#define DUI

#include <stdio.h>

void display_user_interface(const int* board)
{
    // count black and white
    int black_count = 0; 
    int white_count = 0;

    for(int i = 11; i <= 88; i ++)
    {
        if(board[i] == 1)
        {
            black_count ++;
        }
        else if(board[i] == 2)
        {
            white_count ++;
        }
    }

    // print first row
    printf("  1 2 3 4 5 6 7 8 [#=%d O=%d]\n", black_count, white_count);

    // print the 8 rows
    int tens_dig = 0;

    for(int i = 1; i <= 8; i ++)
    {
        printf("%d ", i);

        tens_dig += 10;
        for(int j = 1; j <= 8; j ++)
        {
            if(board[tens_dig + j] == 0)        // empty
            {
                printf(". ");
            }
            else if(board[tens_dig + j] == 1)   // black
            {
                printf("# ");
            }
            else                                // white
            {
                printf("O ");
            }
        }

        printf("\n");
    }
}


/*
#include "initialize_board.c"

int main()
{
    int board[100];
    initialize_board(board);

    board[13] = 1;
    board[88] = 2;

    display_user_interface(board);

    return 0;
}
*/

#endif