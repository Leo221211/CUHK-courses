#include <stdio.h>
#define END 9   // len of LED array - 1

void cal_n_print(int board[], int status[])
{
    int hour = 0;
    int min = 0;

    // calculate and check hour
    for(int i = 0; i <= 3; i ++)
    {
        hour += board[i] * status[i];
    }

    if(hour < 0 || hour >= 12)
    {
        return;
    }

    // calculate and check minutes
    for(int i = 4; i <= 9; i ++)
    {
        min += board[i] * status[i];
    }

    if(min < 0 || min >= 60)
    {
        return;
    }

    //print
    printf("%d:%02d\n", hour, min);

}

void cmb(int to_num, int depth, int board[], int start)
{
    static int store[10] = {0};

    if(depth == to_num)
    {
        cal_n_print(board, store);
    }
    else
    {
        for(int i = start; i <= END; i ++)
        {
            store[i] = 1;

            cmb(to_num, depth + 1, board, i + 1);

            store[i] = 0;
        }
    }
}

int main()
{
    int board[] ={8, 4, 2, 1, 32, 16, 8, 4, 2, 1};
    int to_num;     // turned on number

    scanf("%d", &to_num);

    cmb(to_num, 0, board, 0);

    return 0;
}