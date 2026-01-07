#include "game.h"
#include <stdio.h>

int main(){
    game_t game;
    char buffer[100];

    game_init(&game);
    printf("Peg Solitaire\n");
    printf("Enter move: FROM TO (e.g., D2 D4)\n");
    printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");
    printf("Enter 'q' to quit, 'u' to undo.\n");

    game_display(&game);

    while(game.active){
        if(fgets(buffer, sizeof(buffer), stdin) != NULL){
            if(buffer[0] == 'q'){
                printf("Goodbye!\n");
                game.active = false;
            }else if(buffer[0] == 'u'){
                if(game_undo(&game)) {
                    printf("Undoing move...\n");
                    game_display(&game);
                } else {
                    printf("You can't undo, undo is impossible\n");
                }
            }else{
                symbolized_move_t sym_move;
                if(sscanf(buffer, "%c%c %c%c", &sym_move.from_row, &sym_move.from_col, &sym_move.to_row, &sym_move.to_col) == 4){
                    game.sym_move = sym_move;
                    if(game_play_move(&game)){
                        game_display(&game);
                    } else {
                        printf("Invalid move. Try again.\n");
                        printf("Time: %.0f s, Penalty: %d\n", game_get_time(&game), game.penalty);
                    }
                } else {
                    printf("Invalid input format. Try again.\n");
                }
            }
        }
        game_over(&game);
    }

    if (game.active == false && buffer[0] != 'q'){
        if (game_check_victory(&game)){
            printf("Victory! You won in %.0f seconds.\n", game_get_time(&game));
        } else {
            printf("Game Over! No more moves possible.\n");
        }
        printf("Total Penalties: %d\n", game.penalty);
    }
    return 0;
}