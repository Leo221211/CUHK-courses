/**
 * function: check if a player needs to pass(1) or not (0)
 * input:(1) player: 1 for black and 2 for white
 *       (2) board
 * notice: includes "check_loc_validity.c"
 * 
 * workflow: 
 * loop through every playboard cell
 *      if cell valid ? return 0
*/

// #include "check_loc_validity.c"

int check_pass(int player, const int* board)
{
    static const int PB_CELL_NUM = 64;
    static const int playboard[64] =
    {
        11, 12, 13, 14, 15, 16, 17, 18, 
        21, 22, 23, 24 ,25, 26, 27, 28,
        31, 32, 33, 34 ,35, 36, 37, 38, 
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78, 
        81, 82, 83, 84, 85, 86, 87, 88
    };

    for(int i = 0; i < PB_CELL_NUM; i ++)
    {
        if(check_loc_validity(player, board, playboard[i]) == 1)    // valid
        {
            return 0;   // don't need to pass
        }
    }

    return 1;
}

/*
#include "initialize_board.c"
#include "display_user_interface.c"

int main()
{
    static const int playboard[64] =
    {
        11, 12, 13, 14, 15, 16, 17, 18, 
        21, 22, 23, 24 ,25, 26, 27, 28,
        31, 32, 33, 34 ,35, 36, 37, 38, 
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78, 
        81, 82, 83, 84, 85, 86, 87, 88
    };

    // initialize borad to all black
    int board[100];
    initialize_board(board);
    for(int i = 0; i < 64; i ++)
    {
        //board[playboard[i]] = 1;
    }


    // make empty or white
    board[22] = board[24] = board[27] = 0;
    board[26] = 2;

    display_user_interface(board);

    printf("%d", check_pass(1, board));

    return 0;
}
*/
