/**
 * function: check if the location is valid (1) else (0)
 * input:(1) player color 1 for black and 2 for white
 *       (2) board
 *       (3) location
 * note: there is a sub function for this function
 * 
 *      workflow of check_loc_validity:
 *      if empty and on game board ? next : return 0
 *          loop: up, up-right, ... , eight directions
 *              if(sub_dir_validity) ? return 1
 *          return 0
 * 
 *      workflow of sub_dir_validiity: (0 for invalid and 1 for valid)
 *      if the immediate neibour contains an opponent disk ? next : return 0
 *              loop: until empty / boundary / self disk
 *                  if self ? return 1
*/
#ifndef CLV
#define CLV

int sub_dir_validity(int player, const int* board, int location, int direction)
{
    int opponent = player % 2 + 1 ;    // if player is 1 opponent is 2, if player is 2 opponet is 1
    int cur_loc = location + direction;

    if(board[cur_loc] == opponent)   // the next cell is opponent
    {
        for(cur_loc += direction ; board[cur_loc] != 0 && board[cur_loc] != 3; cur_loc += direction)
        {
            if(board[cur_loc] == player)
            {
                return 1;
            }
        } 
    }

    return 0;
}

int check_loc_validity(int player, const int* board, int location)
{
    static const int    UP = -10,   UPRIGHT = -9,   RIGHT = 1,  DOWNRIGHT = 11;
    static const int    DOWN = 10,  DOWNLEFT = 9,   LEFT = -1,  UPLEFT = -11;

    if(0 <= location && location <= 99)
    {
        if(board[location] == 0)    // on gameboard and cell is empty
        { 
            if(sub_dir_validity(player, board, location, UP))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, UPRIGHT))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, RIGHT))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, DOWNRIGHT))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, DOWN))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, DOWNLEFT))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, LEFT))
            {
                return 1;
            }
            if(sub_dir_validity(player, board, location, UPLEFT))
            {
                return 1;
            }
        }
    }
    
    return 0;
}

/*
#include "initialize_board.c"
#include "display_user_interface.c"

int main()
{
    int board[100];
    initialize_board(board);

    board[35] = 1;

    display_user_interface(board);

    printf("%d ", check_loc_validity(1, board, 42));
    
    return 0;
}
*/

#endif