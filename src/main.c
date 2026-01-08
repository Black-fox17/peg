#include "game.h"
#include <stdio.h>

int main(){
    game_t game;
    char buffer[100];

    game_init(&game);
    printf("Peg Solitaire\n");
    printf("Enter move: FROM TO (e.g., D2 D4)\n");
    printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");
    printf("Enter 'q' to quit.\n");

    game_display(&game);

    while(1){
        if(fgets(buffer, sizeof(buffer), stdin) != NULL){
            if(buffer[0] == 'q'){
                printf("Goodbye!\n");
                break;
            }else{
                symbolized_move_t sym_move;
                if(sscanf(buffer, "%c%c %c%c", &sym_move.from_row, &sym_move.from_col, &sym_move.to_row, &sym_move.to_col) == 4){
                    if(game_play_move(&game, sym_move)){
                        game_display(&game);
                    } else {
                        printf("Invalid move. Try again.\n");
                    }
                } else {
                    printf("Invalid input format. Try again.\n");
                }
            }
        }
        if(game_over(&game)){
            if (game_check_victory(&game)){
                printf("Congratulations you just solved the puzzle!\n");
            } else {
                printf("Game Over! No more moves possible.\n");
            }
            break;
        }
    }
    return 0;
}