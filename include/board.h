#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <stdbool.h>

#define BOARD_SIZE 7

typedef struct board {
    cell board[BOARD_SIZE][BOARD_SIZE];
} board_t;


/// @brief the board
/// @param board the board to create
void create_board(board_t* board);

/// @brief print the board to console  
/// @param board the board to print
void print_board(const board_t* board); 

/// @brief count the remain pegs
/// @param board the board to check
/// @return return the total pegs left on board
int count_pegs(const board_t *board);

#endif