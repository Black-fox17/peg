#include "game.h"
#include <stdio.h>

symbolized_move_t read_move() {
    symbolized_move_t sm = {0};
    char buf[100];
    if (fgets(buf, sizeof(buf), stdin)) {
        sscanf(buf, " %c%c %c%c", &sm.from_row, &sm.from_col, &sm.to_row, &sm.to_col);
    }
    return sm;
}
int main(){
    char buffer[100];
    char choice;

    do {
        game_t game;

        game_init(&game);
        printf("Peg Solitaire\n");
        printf("Enter move: FROM TO (e.g., D2 D4)\n");
        printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");

        game_display(&game);

        while(!game_over(&game)){
            symbolized_move_t sym_move = read_move();
            if(game_play_move(&game, sym_move)){
                game_display(&game);
            } else {
                printf("Invalid move. Try again.\n");
            }
        }
        if (game_check_victory(&game)){
            printf("Congratulations you just solved the puzzle!\n");
        } else {
            printf("Game Over! No more moves possible.\n");
        }

        printf("Play again? (y/n): ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            choice = buffer[0];
        } else {
            choice = 'n';
        }

    } while (choice == 'y' || choice == 'Y');

    return 0;
}