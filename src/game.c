#include "game.h"
#include <stdio.h>

void game_init(game_t *game) {
    create_board(&game->board);
    game->moves = 0;
}

bool game_play_move(game_t *game, symbolized_move_t move){
    move_t m = convert(move);
    
    if (is_valid_move(&game->board, m)) {
        apply_move(&game->board, m);
        game->moves++;
        return true;
    } else {
        return false;
    }
}

bool game_check_victory(const game_t *game) {
    return count_pegs(&game->board) == 1;
}

void game_display(const game_t *game) {
    print_board(&game->board);
    printf("Valid Moves: %d\n", game->moves);
    printf("Pegs remaining: %d\n", count_pegs(&game->board));
}

bool game_over(game_t *game) {
    if (count_pegs(&game->board) == 1) {
        return true;
    }

    // Iterate over every cell on the board
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {

            // Only consider cells that contain a peg
            if (game->board.board[r][c] == PEG) {

                // Possible jump directions (up, down, left, right)
                // Each move jumps exactly two cells
                int dr[] = { -2,  2,  0,  0 };
                int dc[] = {  0,  0, -2,  2 };

                // Try all four directions
                for (int i = 0; i < 4; i++) {
                    move_t m;

                    // Starting position of the move
                    m.from_row = r;
                    m.from_col = c;

                    // Destination position after the jump
                    m.to_row = r + dr[i];
                    m.to_col = c + dc[i];

                    // Position of the peg being jumped over (middle cell)
                    m.over_row = r + dr[i] / 2;
                    m.over_col = c + dc[i] / 2;

                    // If at least one valid move exists, the game is not over
                    if (is_valid_move(&game->board, m))
                        return false;
                }
            }
        }
    }
    return true;
}
