#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "history.h"
#include <time.h>
#include "move.h"

typedef struct {
    board_t board;
    history_t history; // Stores previous moves for backtracking / undoing
    time_t start_time;
    int penalty; // penalty time tracking
    bool active;
    symbolized_move_t sym_move;
} game_t;

/// @brief Initialize the game
void game_init(game_t *game);

/// @brief Apply a move to the game (updates board, history, etc)
/// @return true if move was successful (valid and applied), false otherwise
bool game_play_move(game_t *game);

/// @brief Undo the last move
void game_undo(game_t *game);

/// @brief Check if game is won/lost
bool game_check_victory(const game_t *game);

/// @brief Update game state (e.g. time)
void game_update(game_t *game);

/// @brief Get current elapsed time including penalty
double game_get_time(const game_t *game);


/// @brief check if there's no valid move left or has solved 
/// @param game the game to check
void game_over(game_t *game);


#endif
