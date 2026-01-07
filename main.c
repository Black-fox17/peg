#include <stdio.h>
#include "board.h"

int main() {
    board_t game;
    char buffer[100];
    int r1,c1,r2,c2;
    move_t move;

    create_board(&game);
    printf("Peg Solitaire\n");
    printf("Enter move: FROM TO (e.g., D2 D4)\n");
    printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");
    printf("Enter 'q' to quit.\n");

    print_board(&game);

    while (1) {
        if (game_over(&game)) {
            printf("Game Over!\n");
            break;
        }
            printf("Move: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        if (buffer[0] == 'q' || buffer[0] == 'Q') {
            break;
        }

        char r1_char, r2_char;
        char c1_char, c2_char;
        
        int parsed = sscanf(buffer, " %c%c %c%c", &r1_char, &c1_char, &r2_char, &c2_char);

        if (parsed == 4) {
            symbolized_move_t symbolized_move;
            symbolized_move.from_row = r1_char;
            symbolized_move.from_col = c1_char;
            symbolized_move.to_row = r2_char;
            symbolized_move.to_col = c2_char;
            move = convert(symbolized_move);
            r1 = move.from_row;
            r2 = move.to_row;
            c1 = move.from_col;
            c2 = move.to_col;
            move.over_row = move.from_row + (move.to_row - move.from_row) / 2;
            move.over_col = move.from_col + (move.to_col - move.from_col) / 2;

            if (r1 == -1 || r2 == -1) {
                printf("Invalid row letter. Use A-G.\n");
                continue;
            }


            if (is_valid(&game, move)) {
                apply_move(&game, move);
                print_board(&game);
                printf("Pegs remaining: %d\n", count_pegs(&game));
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            printf("Bad input. Please enter move like: D2 D4, or 'u' to undo.\n");
        }

        
    }
    return 0;
}