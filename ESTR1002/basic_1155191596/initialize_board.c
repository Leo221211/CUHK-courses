/**
 * the game board is a 100 length int array
 * 0: empty, 1: black, 2:white, 3:boundary
 * 
 * function: to initialize the array to the original form
 * input: int* board
 * 
 * work flow: initialize everything to 0
 *            initialize the boundary
 *            place the first four discs
*/

#ifndef IB
#define IB

void initialize_board(int* board)
{
    // innitialize all to 0
    for(int i = 0; i <= 99; i ++)
    {
        board[i] = 0;
    }

    // initialize the boundary
    for(int i = 0; i <= 10; i ++)
    {
        board[i] = 3;
    }

    for(int i = 89; i <= 99; i ++)
    {
        board[i] = 3;
    }

    for(int i = 19; i <=79; i += 10)
    {
        board[i] = 3;
        board[i + 1] = 3;
    }

    // initialize the 4 original discs
    board[44] = 2;
    board[45] = 1;
    board[54] = 1;
    board[55] = 2;
}

/*
int main()
{
    int board[100];

    initialize_board(board);

    return 0;
}
*/

#endif