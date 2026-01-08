#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "move.h"

typedef struct {
    board_t board;
    int moves;
} game_t;

/// @brief Initialize the game
void game_init(game_t *game);

/// @brief Apply a move to the game (updates board, history, etc)
/// @return true if move was successful (valid and applied), false otherwise
bool game_play_move(game_t *game, symbolized_move_t move);

/// @brief Check if game is won/lost
bool game_check_victory(const game_t *game);

/// @brief Display the current state of the game
void game_display(const game_t *game);

/// @brief check if there's no valid move left or has solved 
/// @param game the game to check
bool game_over(game_t *game);


#endif
