/**
 * function: read the input location from the user and and return the location
 * input:(1) int player: 1 for black; 2 for white
 *       (2) const int* board
*/

// #include <stdio.h>

int human_player_1155191596(int player, const int* board)
{
    int input;

    if(player == 1) // black
    {
        printf("black player input coordinate: ");
    }
    if(player == 2) // white
    {
        printf("white player input coordinate: ");
    }

    scanf("%d", &input);

    return input;
}