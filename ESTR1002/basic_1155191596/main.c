// remember to remove sleep!

#include <stdio.h>
#include <unistd.h>
#include "end_game.c"
#include "check_loc_validity.c"
#include "check_pass.c"
#include "display_user_interface.c"
#include "human_player_1155191596.c"
#include "initialize_board.c"
#include "place_and_flip.c"
#include "aiplayer_1155191596.c"

int main()
{
    // initialize gameboard and player
    int board[100];
    int player = 1;
    initialize_board(board);

    // ask for play mode
    int mode;
    printf("choose play mode (1 for pvp; 2 for pvc): ");
    scanf("%d", &mode);
    
    // game loop
    if(mode == 1)
    {
        while(1)
        {
            display_user_interface(board);

            int opponent = player % 2 + 1;

            if(check_pass(player, board) == 0)  // don't need to pass
            {
                int temp_loc = human_player_1155191596(player, board);

                while(check_loc_validity(player, board, temp_loc) == 0)  // invalid location
                {
                    printf("invalid location!\n");
                    temp_loc = human_player_1155191596(player, board);
                }

                place_and_flip(player, board, temp_loc);

                player = opponent;
            }
            else if(check_pass(opponent, board) == 1)    // needs to pass, check if opponent also needs to pass, if so end game
            {
                break;
            }

            player = opponent;

        }

        // end game display
        end_game(board);

        return 0;
    }
    else    // pvc
    {
        int counter = 0;

        while(1)
        {

            display_user_interface(board);

            int opponent = player % 2 + 1;

            if(check_pass(player, board) == 0)  // don't need to pass
            {
                int temp_loc;
                if(counter % 2 == 1)    // ai round
                {
                    sleep(1);
                    temp_loc = aiplayer_1155191596(player, board);
                    printf("white player input coordinate: %d\n", temp_loc);
                }
                else
                {
                    temp_loc = human_player_1155191596(player, board);
                }

                while(check_loc_validity(player, board, temp_loc) == 0)  // invalid location
                {
                    printf("invalid location!\n");
                    temp_loc = human_player_1155191596(player, board);
                }

                place_and_flip(player, board, temp_loc);

                player = opponent;
            }
            else if(check_pass(opponent, board) == 1)    // needs to pass, check if opponent also needs to pass, if so end game
            {
                break;
            }

            player = opponent;
            counter ++;
        }

        // end game display
        end_game(board);

        return 0;
    }

}
