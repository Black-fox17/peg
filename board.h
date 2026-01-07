#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "move.h"
#include <stdbool.h>

typedef struct{
    cell board[7][7];
}board_t;


/// @brief the board
/// @param board the board to create
void create_board(board_t* board);

/// @brief print the board to console  
/// @param board the board to print
void print_board(const board_t* board); 

/// @brief check if the cell maybe empty or has pegs or invalid
/// @param board the board to check
/// @param row the row to check
/// @param col the colum to check
/// @return the enum above if its empty, peg,invalid
cell check_cell (const board_t *board,int row,int col);

/// @brief set the value of the sell empty,pegs,invalid
/// @param board the board to set
/// @param row the row to set
/// @param col the colum to set
/// @param value the "status" of that cell
void set_cell(board_t *board,int row,int col,cell value);
 
/// @brief check if the move is valid
/// @param board the board to check
/// @param move the move to check
/// @return true if valid and false for not
bool is_valid(const board_t *board,move_t move);

/// @brief count the remain pegs
/// @param board the board to check
/// @return return the total pegs left on board
int count_pegs(const board_t *board);

/// @brief just move the pegs =))
/// @param board the board to move
/// @param move how to move
void apply_move(board_t *board,move_t move);


/// @brief check if there's no valid move left or has solved 
/// @param board the board to check
/// @return true if over false if can be continued
bool game_over(const board_t *board);

#endif