/**
 * (-5) % 3 = -2: simply ignore the minus sign and add it in the end
 * macro?
*/
#include <stdio.h>
//#define SWAP(A, B) {int tmp = A; A = B; B = tmp;}

// different types
void odd(int len, int ms[5000][5000]);
void move_odd(int* cdn, int d, int len);

void s_even(int len, int ms[5000][5000]);
void se_fill_sub(int* bigms, int big_len, int stt_num, int stt_row, int stt_col);
void SWAP(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void d_even(int len, int ms[5000][5000]);
int tell_truth(int row, int col);

int ms[5000][5000];

int main()
{
    int size;
    scanf("%d", &size);

    // initialize
    // int ms[size][size];
    for(int i = 0; i < size; i ++)
    {
        for(int j = 0; j < size; j ++)
        {
            ms[i][j] = 0;
        }
    }

    if(size % 2 == 1)       // odd
    {
        odd(size, ms);
    }
    else if(size % 4 == 0)  // doubly even
    {
        d_even(size, ms);
    }
    else                    // singly even
    {
        s_even(size, ms);
    }

    return 0;
}

void odd(int len, int ms[5000][5000])
{
    // find elements
    int row = len / 2;
    int col = len - 1;
    ms[row][col] = 1;

    for(int i = 2; i <= len * len; i ++)
    {
        // condition 3
        if(row == -1 && col == len)     
        {
            row = 0;
            col = len - 2;
        }

        // move
        move_odd(&row, -1, len);
        move_odd(&col, 1, len);

        // check occupy
        if(ms[row][col] != 0)
        {
            move_odd(&col, -2, len);
            move_odd(&row, 1, len);
        }

        ms[row][col] = i;
    }

    // print
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%d ", ms[i][j]);
        }

        putchar('\n');
    }
}

void move_odd(int* cdn, int d, int len)
{
    *cdn += d;
    if(*cdn < 0)
    {
        *cdn += len;
    }
    else if(*cdn >= len)
    {
        *cdn -= len;
    }
}

void s_even(int len, int ms[5000][5000])
{
    // filling sub-square
    se_fill_sub((int*)ms, len, 1                            , 0      , 0      );
    se_fill_sub((int*)ms, len, 1 + (len / 2) * (len / 2)    , len / 2, len / 2);
    se_fill_sub((int*)ms, len, 1 + 2 * (len / 2) * (len / 2), 0      , len / 2);
    se_fill_sub((int*)ms, len, 1 + 3 * (len / 2) * (len / 2), len / 2, 0      );

    // swap
    for(int i = 0; i < len / 2; i ++)
    {
        for(int j = 0; j < (len - 2) / 4; j ++)
        {
            SWAP(&ms[i][j], &ms[i + len / 2][j]);
        }
    }
    // check print
    /*
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%d ", ms[i][j]);
        }

        putchar('\n');
    }
    */
    

    for(int i = 0; i < len / 2; i ++)
    {
        for(int j = 1; j <= (len - 2) / 4 - 1; j ++)
        {
            SWAP(&ms[i][len - j], &ms[i + len / 2][len - j]);
        }
    }

    SWAP(&ms[len / 4][0], &ms[len / 4 + len / 2][0]);
    SWAP(&ms[len / 4][len / 4], &ms[len / 4 + len / 2][len / 4]);

    // print
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%d ", ms[i][j]);
        }

        putchar('\n');
    }

}

void se_fill_sub(int* bigms, int big_len, int stt_num, int stt_row, int stt_col)
{
    // initialize small ms
    int len = big_len / 2;

    int ms[len][len];
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            ms[i][j] = 0;
        }
    }

    // find elements for small ms
    int row = len / 2;
    int col = len - 1;

    int cnt = stt_num;
    ms[row][col] = stt_num;

    for(int i = 2; i <= len * len; i ++)
    {
        // condition 3
        if(row == -1 && col == len)     
        {
            row = 0;
            col = len - 2;
        }

        // move
        move_odd(&row, -1, len);
        move_odd(&col, 1, len);

        // check occupy
        if(ms[row][col] != 0)
        {
            move_odd(&col, -2, len);
            move_odd(&row, 1, len);
        }

        ms[row][col] = ++cnt;
    }

    // transpose
    int tmp_ms[len][len];

    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            tmp_ms[len - 1 - j][len -1 - i] = ms[i][j];
        }
    }

    // check print
    /*
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%d ", tmp_ms[i][j]);
        }

        putchar('\n');
    }
    */

    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            bigms[(stt_row + i) * (big_len) + stt_col + j] = tmp_ms[i][j];
        }
    }

}

void d_even(int len, int ms[len][len])
{
    int cnt;

    // first round
    cnt = 0;
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            cnt ++;

            if(tell_truth(i , j) == 1)
            {
                ms[i][j] = cnt;
            }
        }
    }

    // second round
    cnt = 0;
    for(int i = len -1; i >= 0; i --)
    {
        for(int j = len - 1; j >= 0; j --)
        {
            cnt ++;

            if(tell_truth(i , j) == 0)
            {
                ms[i][j] = cnt;
            }
        }
    }

    // print
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len; j ++)
        {
            printf("%d ", ms[i][j]);
        }

        putchar('\n');
    }
}

int tell_truth(int row, int col)
{
    char truth_table[4][4] = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 0, 1}};

    return truth_table[row % 4][col % 4];
}