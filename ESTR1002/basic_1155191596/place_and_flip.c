/**
 * function: place the disc and flip oppenents discs
 * input:(1) player
 *       (2) board
 *       (3) location
 * notice:(1）include sub_dir_pf and not include "check_loc_validity.c"
 *        (2)!! hasn't checked if the input location is valid!\
 * 
 * workflow of place_and_flip
 * current place -> player
 * 8 direction sub_dir_pf
 * 
 * workflow of sub_dir_flip
 * if sub-direction valid
 *      flip until meet player disk
 *          
*/

// #include "check_loc_validity.c"

void sub_dir_flip(int player, int* board, int location, int direction)
{

    if(sub_dir_validity(player, board, location, direction) == 1)   // this direction is valid
    {
        int opponent = player % 2 + 1 ;    // if player is 1 opponent is 2, if player is 2 opponet is 1

        for(int cur_loc = location + direction; board[cur_loc] != player; cur_loc += direction)
        {
            board[cur_loc] = player;
        }
    }
}

void place_and_flip(int player, int* board, int location)
{
    static const int    UP = -10,   UPRIGHT = -9,   RIGHT = 1,  DOWNRIGHT = 11;
    static const int    DOWN = 10,  DOWNLEFT = 9,   LEFT = -1,  UPLEFT = -11;

    board[location] = player;

    sub_dir_flip(player, board, location, UP);
    sub_dir_flip(player, board, location, UPRIGHT);
    sub_dir_flip(player, board, location, RIGHT);
    sub_dir_flip(player, board, location, DOWNRIGHT);
    sub_dir_flip(player, board, location, DOWN);
    sub_dir_flip(player, board, location, DOWNLEFT);
    sub_dir_flip(player, board, location, LEFT);
    sub_dir_flip(player, board, location, UPLEFT);
}

/*
#include "initialize_board.c"
#include "display_user_interface.c"

int main()
{
    int board[100];
    initialize_board(board);

    display_user_interface(board);

    place_and_flip(2, board, 64);

    printf("\n");

    display_user_interface(board);

    return 0;
}
*/