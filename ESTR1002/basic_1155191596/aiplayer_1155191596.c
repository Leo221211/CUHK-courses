/**
 * function: tell the location of the next move
 * input:(1) player (1: black, 2: white)
 *       (2) board
 * notes:(1) there is 2 subfunctions
*/

// #include "check_loc_validity.c"
#ifndef CLV1
#define CLV1

int sub_dir_validity_1155191596(int player, const int* board, int location, int direction)
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

int check_loc_validity_1155191596(int player, const int* board, int location)
{
    static const int    UP = -10,   UPRIGHT = -9,   RIGHT = 1,  DOWNRIGHT = 11;
    static const int    DOWN = 10,  DOWNLEFT = 9,   LEFT = -1,  UPLEFT = -11;

    if(0 <= location && location <= 99)
    {
        if(board[location] == 0)    // on gameboard and cell is empty
        { 
            if(sub_dir_validity_1155191596(player, board, location, UP))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, UPRIGHT))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, RIGHT))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, DOWNRIGHT))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, DOWN))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, DOWNLEFT))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, LEFT))
            {
                return 1;
            }
            if(sub_dir_validity_1155191596(player, board, location, UPLEFT))
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

int object_cmp1_1155191596(int player, const int* board, int location)  // version1: check number of flipped discs
{
    static const int    UP = -10,   UPRIGHT = -9,   RIGHT = 1,  DOWNRIGHT = 11;
    static const int    DOWN = 10,  DOWNLEFT = 9,   LEFT = -1,  UPLEFT = -11;

    int flip_num = 0;
    int opponent = player % 2 + 1;

    // check
    for(int cur_loc = location + UP; board[cur_loc] == opponent; cur_loc += UP)
    {
        flip_num ++;
    }
    for(int cur_loc = location + UPRIGHT; board[cur_loc] == opponent; cur_loc += UPRIGHT)
    {
        flip_num ++;
    }
    for(int cur_loc = location + RIGHT; board[cur_loc] == opponent; cur_loc += RIGHT)
    {
        flip_num ++;
    }
    for(int cur_loc = location + DOWNRIGHT; board[cur_loc] == opponent; cur_loc += DOWNRIGHT)
    {
        flip_num ++;
    }
    for(int cur_loc = location + DOWN; board[cur_loc] == opponent; cur_loc += DOWN)
    {
        flip_num ++;
    }
    for(int cur_loc = location + DOWNLEFT; board[cur_loc] == opponent; cur_loc += DOWNLEFT)
    {
        flip_num ++;
    }
    for(int cur_loc = location + LEFT; board[cur_loc] == opponent; cur_loc += LEFT)
    {
        flip_num ++;
    }
    for(int cur_loc = location + UPLEFT; board[cur_loc] == opponent; cur_loc += UPLEFT)
    {
        flip_num ++;
    }

    return flip_num;
    
}

int aiplayer_1155191596(int player, const int* board)
{
    // define
    // UPLEFT = 0, UPRIGHT = 1, DOWNLEFT = 2, DOWNRIGHT = 3;
    const int corner_elenum = 4, corner[4] = {11, 18, 81, 88};
    const int ring2_elenum = 12, ring2[12] = {12, 21, 22, 17, 27, 28, 71, 72, 82, 87, 77, 78};
    const int ring3_elenum = 20, ring3[20] = {13, 31, 33, 32, 23, 16, 26, 36, 37, 38, 61, 62, 63, 73, 83, 66, 67, 68, 76, 86};
    const int midboard_elenum = 28, midboard[28] = {14, 15, 24, 25, 34, 35, 41, 42, 43, 44, 45, 46, 47, 48, 51, 52, 53, 54, 55, 56, 57, 58, 64, 65, 74, 75, 84, 85};

    typedef struct{
        int coordinate;
        int obj_cmp;
    } Loc_status;
    Loc_status best_loc;
    best_loc.coordinate = 0;
    best_loc.obj_cmp = 0;

    // check corner
    for(int i = 0; i < corner_elenum; i ++)
    {
        int tmp_cor = corner[i];

        if(check_loc_validity_1155191596(player, board, tmp_cor) == 1)    // valid
        {
            int tmp_obj = object_cmp1_1155191596(player, board, tmp_cor);
            if(tmp_obj > best_loc.obj_cmp) // a better choice
            {
                best_loc.obj_cmp = tmp_obj;
                best_loc.coordinate = tmp_cor;
            }
        }
    }

    if(best_loc.coordinate != 0)
    {
        return best_loc.coordinate;
    }

    // check ring3
    for(int i = 0; i < ring3_elenum; i ++)
    {
        int tmp_cor = ring3[i];

        if(check_loc_validity_1155191596(player, board, tmp_cor) == 1)    // valid
        {
            int tmp_obj = object_cmp1_1155191596(player, board, tmp_cor);
            if(tmp_obj > best_loc.obj_cmp) // a better choice
            {
                best_loc.obj_cmp = tmp_obj;
                best_loc.coordinate = tmp_cor;
            }
        }
    }

    if(best_loc.coordinate != 0)
    {
        return best_loc.coordinate;
    }

    // check midboard
    for(int i = 0; i < midboard_elenum; i ++)
    {
        int tmp_cor = midboard[i];

        if(check_loc_validity_1155191596(player, board, tmp_cor) == 1)    // valid
        {
            int tmp_obj = object_cmp1_1155191596(player, board, tmp_cor);
            if(tmp_obj > best_loc.obj_cmp) // a better choice
            {
                best_loc.obj_cmp = tmp_obj;
                best_loc.coordinate = tmp_cor;
            }
        }
    }

    if(best_loc.coordinate != 0)
    {
        return best_loc.coordinate;
    }

    // check ring2
    for(int i = 0; i < ring2_elenum; i ++)
    {
        int tmp_cor = ring2[i];

        if(check_loc_validity_1155191596(player, board, tmp_cor) == 1)    // valid
        {
            int tmp_obj = object_cmp1_1155191596(player, board, tmp_cor);
            if(tmp_obj > best_loc.obj_cmp) // a better choice
            {
                best_loc.obj_cmp = tmp_obj;
                best_loc.coordinate = tmp_cor;
            }
        }
    }

    return best_loc.coordinate;

}

/*
#include "initialize_board.c"
#include "display_user_interface.c"
#include <stdio.h>

int main()
{
    int board[100];
    initialize_board(board);
    board[56] = 2;
    board[45] = 0;

    display_user_interface(board);

    printf("%d",aiplayer_1155191596(1, board));

    return 0;
}
*/
