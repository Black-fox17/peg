#include "move.h"
#include <ctype.h>

bool is_valid_move(const board_t *board, move_t m)
{
    if (m.from_row < 0 || m.from_row >= BOARD_SIZE ||
        m.from_col < 0 || m.from_col >= BOARD_SIZE ||
        m.over_row < 0 || m.over_row >= BOARD_SIZE ||
        m.over_col < 0 || m.over_col >= BOARD_SIZE ||
        m.to_row   < 0 || m.to_row   >= BOARD_SIZE ||
        m.to_col   < 0 || m.to_col   >= BOARD_SIZE)
        return false;

    if (check_cell(board, m.from_row, m.from_col) == INVALID ||
        check_cell(board, m.over_row, m.over_col) == INVALID ||
        check_cell(board, m.to_row,   m.to_col)   == INVALID)
        return false;

    if (check_cell(board, m.from_row, m.from_col) != PEG)
        return false;

    if (check_cell(board, m.over_row, m.over_col) != PEG)
        return false;

    if (check_cell(board, m.to_row, m.to_col) != EMPTY)
        return false;
    int dr = m.to_row - m.from_row;
    int dc = m.to_col - m.from_col;

    if (!((dr == 0 && (dc == 2 || dc == -2)) ||
          (dc == 0 && (dr == 2 || dr == -2))))
        return false;
    if (m.over_row != m.from_row + dr / 2 ||
        m.over_col != m.from_col + dc / 2)
        return false;

    return true;
}


void apply_move(board_t *board, move_t move) {
    set_cell(board, move.from_row, move.from_col, EMPTY);
    set_cell(board, move.over_row, move.over_col, EMPTY);
    set_cell(board, move.to_row, move.to_col, PEG);
}

move_t convert(symbolized_move_t move){
    move_t move_converted;
    move_converted.from_row = toupper(move.from_row) - 'A';
    move_converted.from_col = move.from_col - '1';
    move_converted.to_row = toupper(move.to_row) - 'A';
    move_converted.to_col = move.to_col - '1';
    move_converted.over_row = (move_converted.from_row + move_converted.to_row) / 2;
    move_converted.over_col = (move_converted.from_col + move_converted.to_col) / 2;
    return move_converted;
}
