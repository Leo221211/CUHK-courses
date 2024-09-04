/**
 * function: print out the winner or draw
 * 
*/

void end_game(const int* board)
{
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

    if(black_count > white_count)
    {
        printf("Black wins!");
    }
    else if(white_count > black_count)
    {
        printf("White wins!");
    }
    else
    {
        printf("Draw!");
    }
}