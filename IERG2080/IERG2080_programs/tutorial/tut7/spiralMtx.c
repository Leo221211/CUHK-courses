/**
 * warning!
 * *row ++
*/
#include <stdio.h>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

/*
// tell if is end of a direction: 1 yes, 0 no
int tell_end(int mtx[20][20], int len, int row, int col)
{
    // if is margin
    if(row == len - 1 || col == len - 1)
    {

    }
}
*/

// tel the new position (not final)
void tell_newpos(int type, int mtx[20][20], int* row, int* col)
{
        if(type == RIGHT)
        {
            (*col) ++;
        }
        else if(type == DOWN)
        {
            (*row) ++;
        }
        else if(type == LEFT)
        {
            (*col) --;
        }
        else    // UP
        {
            (*row) --;
        }
}

void det_pos(int* type, int mtx[20][20], int* row, int* col)
{
    // assumed new pos
    int asm_row = *row;
    int asm_col = *col;
    tell_newpos(*type, mtx, &asm_row, &asm_col);

    // check if ok, if not, change type and new pos
    if(mtx[asm_row][asm_col] != -1)     // not OK
    {
        *type = (*type + 1) % 4;
        tell_newpos(*type, mtx, row, col);
    }
    else
    {
        *row = asm_row;
        *col = asm_col;
    }
}

int main()
{
    // initialize
    int mtx[20][20] = {0};
    int type = RIGHT;
    int len;                // inputted len of the mtx
    int col = 0, row = 0;   // original row and col

    // input
    scanf("%d", &len);

    // fill the to fill entries to -1
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            mtx[i][j] = -1;
        }
    }

    // fill
    for(int i = 1; i <= len * len; i ++)
    {
        // set num
        mtx[row][col] = i;

        // tel new position
        det_pos(&type, mtx, &row, &col);
    }

    // print
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%3d ", mtx[i][j]);
        }
        printf("%c", '\n');
    }

    return 0;
}

/**
 *        if(tell_end(mtx, len, row, col))     // is the end
        {
            type = (type + 1) % 4;

        }
*/