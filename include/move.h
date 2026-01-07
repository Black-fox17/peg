#ifndef MOVE_H
#define MOVE_H

#include "board.h"
#include <stdbool.h>

typedef struct {
    int from_row, from_col;
    int over_row, over_col;
    int to_row, to_col;
}move_t;

typedef struct{
    char from_row, from_col;
    char to_row, to_col;
}symbolized_move_t;

/// @brief convert the A1 B3 to coordinate
/// @param move the A1 A2 for e.g
/// @return the move
move_t convert(symbolized_move_t move);

/// @brief just move the pegs =))
/// @param board the board to move
/// @param move how to move
void apply_move(board_t *board,move_t move);

/// @brief undo the move
/// @param board the board to undo on
/// @param move the move to reverse
void undo_move(board_t *board, move_t move);

/// @brief check if the move is valid
/// @param board the board to check
/// @param move the move to check
/// @return true if valid and false for not
bool is_valid_move(const board_t *board,move_t move);


#endif