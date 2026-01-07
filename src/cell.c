cell check_cell(const board_t *board, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return INVALID;
    }
    return board->board[row][col];
}

void set_cell(board_t *board, int row, int col, cell value) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return;
    }
    board->board[row][col] = value;
}

