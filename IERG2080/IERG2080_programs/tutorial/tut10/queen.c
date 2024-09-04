#include <stdio.h>
#define FILL 1
#define UNFILL -1

void printboard(int board[9][9], int len)
{
    static int sol = 0;
    printf("solution %d:\n", ++sol);

    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            if(board[i][j] == 0)    // no queen
            {
                putchar('.');
            }
            else
            {
                putchar('|');
            }
        }
        putchar('\n');
    }
}

void fill(int board[9][9], int row, int col, int len, int status)
{
    // row
    for(int i = 0; i < len; i ++)
    {
        board[row][i] += status;    // fill +1, unfill -1
    }

    // col
    for(int i = 0; i < len; i ++)
    {
        board[i][col] += status;
    }

    // diagonal
    for(int i = 1; col - i >= 0 && row - i >= 0; i ++) // left up
    {
        board[row - i][col - i] += status;
    }
    for(int i = 1; col + i < len && row + i < len; i ++) // right down
    {
        board[row + i][col + i] += status;
    }
    for(int i = 1; col + i < len && row - i >= 0; i ++) // right up
    {
        board[row - i][col + i] += status;
    }
    for(int i = 1; col - i >= 0 && row + i < len; i ++) // left down
    {
        board[row + i][col - i] += status;
    }
}

void find_queen(int len, int row)
{
    static int board[9][9];
    static int rem_board[9][9];

    if(row >= len)   // end fill
    {
        printboard(rem_board, len);
        return;
    }

    for(int col = 0; col < len; col ++)
    {
        if(board[row][col] != 0)    // filled
        {
            continue;
        }

        fill(board, row, col, len, FILL);
        rem_board[row][col] += FILL;

        find_queen(len, row + 1);

        fill(board, row, col, len, UNFILL);
        rem_board[row][col] += UNFILL;
    }
}

int main()
{
    int len;
    scanf("%d", &len);

    find_queen(len, 0);

    return 0;
}