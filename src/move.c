bool is_valid_move(const board_t *board, move_t move) {
    if(move.from_row < 0 || move.from_row >= 7 ||
        move.from_col < 0 || move.from_col >= 7 ||
        move.over_row < 0 || move.over_row >= 7 ||
        move.over_col < 0 || move.over_col >= 7 ||
        move.to_row   < 0 || move.to_row   >= 7 ||
        move.to_col   < 0 || move.to_col   >= 7) {
        return false;
    }

    if(check_cell(board, move.from_row, move.from_col) != PEG)
        return false;

    if(check_cell(board, move.over_row, move.over_col) != PEG)
        return false;

    if(check_cell(board, move.to_row, move.to_col) != EMPTY)
        return false;

    int dr = move.to_row - move.from_row;
    int dc = move.to_col - move.from_col; 

    if(!((dr == 0 && (dc == 2 || dc == -2)) ||
          (dc == 0 && (dr == 2 || dr == -2)))) {
        return false;
    }

    // Midpoint check
    if(move.over_row != move.from_row + dr / 2 ||
        move.over_col != move.from_col + dc / 2) {
        return false;
    }

    return true;
}


void apply_move(board_t *board, move_t move) {
    set_cell(board, move.from_row, move.from_col, EMPTY);
    set_cell(board, move.over_row, move.over_col, EMPTY);
    set_cell(board, move.to_row, move.to_col, PEG);
}

void undo_move(board_t *board, move_t move) {
    // Reverse apply: to->EMPTY, over->PEG, from->PEG
    set_cell(board, move.to_row, move.to_col, EMPTY);
    set_cell(board, move.over_row, move.over_col, PEG);
    set_cell(board, move.from_row, move.from_col, PEG);
}


move_t convert_move(symbolized_move_t move){
    move_t move_converted;
    move_converted.from_row = move.from_row - 'A';
    move_converted.from_col = move.from_col - '1';
    move_converted.to_row = move.to_row - 'A';
    move_converted.to_col = move.to_col - '1';
    move_converted.over_row = (move_converted.from_row + move_converted.to_row) / 2;
    move_converted.over_col = (move_converted.from_col + move_converted.to_col) / 2;
    return move_converted;
}
