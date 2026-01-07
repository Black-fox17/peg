#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.h"

#define BOARD_SIZE 7

void create_board(board_t *board) {
    int r, c;
    for (r = 0; r < BOARD_SIZE; r++) {
        for (c = 0; c < BOARD_SIZE; c++) {
            if ((r < 2 || r > 4) && (c < 2 || c > 4)) {
                board->board[r][c] = INVALID;
            } else {
                board->board[r][c] = PEG;
            }
        }
    }
    board->board[3][3] = EMPTY;
}

void print_board(const board_t *board) {
    int r, c;
    
    // Print Column Headers
    printf("    1 2 3 4 5 6 7\n");
    printf("    -------------\n");

    for (r = 0; r < BOARD_SIZE; r++) {
        // Print Row Label
        printf("%c | ", 'A' + r);
        
        for (c = 0; c < BOARD_SIZE; c++) {
            switch (board->board[r][c]) {
                case INVALID:
                    printf("  "); 
                    break;
                case EMPTY:
                    printf(". ");
                    break;
                case PEG:
                    printf("o ");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

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

bool is_valid(const board_t *board, move_t move) {

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

    if(move.over_row != move.from_row + dr / 2 ||
        move.over_col != move.from_col + dc / 2) {
        return false;
    }

    return true;
}

int count_pegs(const board_t *board) {
    int count = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board->board[r][c] == PEG) {
                count++;
            }
        }
    }
    return count;
}

void apply_move(board_t *board, move_t move) {
    int r1 = move.from_row;
    int c1 = move.from_col;
    int r2 = move.to_row;
    int c2 = move.to_col;
    
    int mid_r = (r1 + r2) / 2;
    int mid_c = (c1 + c2) / 2;

    set_cell(board, r1, c1, EMPTY);
    set_cell(board, mid_r, mid_c, EMPTY);
    set_cell(board, r2, c2, PEG);

}

bool game_over(const board_t *board) {
    return count_pegs(board) == 1;
}



move_t convert(symbolized_move_t move){
    move_t move_converted;
    move_converted.from_row = move.from_row - 'A';
    move_converted.from_col = move.from_col - '1';
    move_converted.to_row = move.to_row - 'A';
    move_converted.to_col = move.to_col - '1';
    return move_converted;
}
