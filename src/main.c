#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    game_t game;
    char buffer[100];

    game_init(&game);
    printf("Peg Solitaire\n");
    printf("Enter move: FROM TO (e.g., D2 D4)\n");
    printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");
    printf("Enter 'q' to quit, 'u' to undo.\n");

    game_display(&game);

    while (1) {
        if (game_over(&game.board)) {
            if (game_check_victory(&game)) {
                printf("Victory! You won in %.0f seconds.\n", game_get_time(&game));
            } else {
                printf("Game Over! No more moves possible.\n");
            }
            printf("Total Penalties: %d\n", game.penalty);
            break;
        }

        printf("Move > ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        if (buffer[0] == 'q' || buffer[0] == 'Q') {
            break;
        }
        
        if (buffer[0] == 'u' || buffer[0] == 'U') {
            game_undo(&game);
            game_display(&game);
            printf("Undo performed.\n");
            continue;
        }

        char r1_char, r2_char;
        char c1_char, c2_char;
        
        int parsed = sscanf(buffer, " %c%c %c%c", &r1_char, &c1_char, &r2_char, &c2_char);

        if (parsed == 4) {
            symbolized_move_t sym_move;
            sym_move.from_row = r1_char;
            sym_move.from_col = c1_char;
            sym_move.to_row = r2_char;
            sym_move.to_col = c2_char;

            if (game_play_move(&game, sym_move)) {
                game_display(&game);
                printf("Pegs remaining: %d\n", count_pegs(&game.board));
            } else {
                printf("Invalid move or input format. Try again.\n");
            }
        } else {
             printf("Bad input. Please enter move like: D2 D4, or 'u' to undo.\n");
        }
    }
    return 0;
}