#ifndef CELL_H
#define CELL_H

// Forward declaration
struct board;

typedef enum {
    INVALID,
    EMPTY,
    PEG
}cell;

/// @brief check if the cell maybe empty or has pegs or invalid
/// @param board the board to check
/// @param row the row to check
/// @param col the colum to check
/// @return the enum above if its empty, peg,invalid
cell check_cell (const struct board *board,int row,int col);

/// @brief set the value of the sell empty,pegs,invalid
/// @param board the board to set
/// @param row the row to set
/// @param col the colum to set
/// @param value the "status" of that cell
void set_cell(struct board *board,int row,int col,cell value);
 
#endif 
