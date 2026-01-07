#ifndef MOVE_H
#define MOVE_H

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

#endif