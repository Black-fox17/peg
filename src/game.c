#include "game.h"
#include <stdio.h>

void game_init(game_t *game) {
    create_board(&game->board);
    history_init(&game->history);
    game->active = true;
    game->start_time = time(NULL);
    game->penalty = 0;
}

bool game_play_move(game_t *game){
    move_t m = convert(game->sym_move);
    
    if (is_valid_move(&game->board, m)) {
        apply_move(&game->board, m);
        history_push(&game->history, m);
        return true;
    } else {
        game->penalty++; 
        return false;
    }
}

void game_undo(game_t *game) {
    if (!history_is_empty(&game->history)) {
        move_t last = history_pop(&game->history);
        undo_move(&game->board, last);
    }
}

bool game_check_victory(const game_t *game) {
    return count_pegs(&game->board) == 1;
}

double game_get_time(const game_t *game) {
    time_t now = time(NULL);
    return difftime(now, game->start_time);
}

void game_display(const game_t *game) {
    print_board(&game->board);
}

void game_over(game_t *game) {
    if (count_pegs(&game->board) == 1) {
        game->active = false;
        return;
    }
    
    for (int r=0; r<BOARD_SIZE; r++){
        for(int c=0; c<BOARD_SIZE; c++){
            if(game->board.board[r][c] == PEG){
                int dr[] = {-2, 2, 0, 0};
                int dc[] = {0, 0, -2, 2};
                for(int i=0; i<4; i++){
                    move_t m;
                    m.from_row = r; m.from_col = c;
                    m.to_row = r + dr[i]; m.to_col = c + dc[i];
                    m.over_row = r + dr[i]/2; m.over_col = c + dc[i]/2;
                    if(is_valid_move(&game->board, m)) return;
                }
            }
        }
    }

    game->active = false;
    return;
}

int main(){
    game_t game;
    char buffer[100];

    game_init(&game);
    printf("Peg Solitaire\n");
    printf("Enter move: FROM TO (e.g., D2 D4)\n");
    printf("Format: [RowLetter][ColNumber] [RowLetter][ColNumber]\n");
    printf("Enter 'q' to quit, 'u' to undo.\n");

    game_display(&game);

    while(game.active){
        if(fgets(buffer, sizeof(buffer), stdin) != NULL){
            if(buffer[0] == 'q'){
                printf("Goodbye!\n");
                game.active = false;
            }else if(buffer[0] == 'u'){
                printf("Undoing move...\n");
                game_undo(&game);
            }else{
                symbolized_move_t sym_move;
                if(sscanf(buffer, "%c%c %c%c", &sym_move.from_row, &sym_move.from_col, &sym_move.to_row, &sym_move.to_col) == 4){
                    game.sym_move = sym_move;
                    if(game_play_move(&game)){
                        game_display(&game);
                        printf("Pegs remaining: %d\n", count_pegs(&game.board));
                    } else {
                        printf("Invalid move. Try again.\n");
                    }
                } else {
                    printf("Invalid input format. Try again.\n");
                }
            }
        }
        game_over(&game);
    }

    if (game.active == false && buffer[0] != 'q'){
        if (game_check_victory(&game)){
            printf("Victory! You won in %.0f seconds.\n", game_get_time(&game));
        } else {
            printf("Game Over! No more moves possible.\n");
        }
        printf("Total Penalties: %d\n", game.penalty);
    }
    return 0;
}