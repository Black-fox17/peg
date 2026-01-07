#include <stdio.h>
#include "board.h"

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
