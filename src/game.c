void create_game(game_t *game) {
    create_board(&game->board);
    history_init(&game->history);
    game->active = true;
    game->start_time = time(NULL);
    game->penalty = 0;
}

bool game_play_move(game_t *game, symbolized_move_t sym_move){
    move_t m = convert(sym_move);
    
    if (is_valid(&game->board, m)) {
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

bool game_over(const board_t *board) {
    if (count_pegs(board) == 1) return true;
    
    for (int r=0; r<BOARD_SIZE; r++){
        for(int c=0; c<BOARD_SIZE; c++){
            if(board->board[r][c] == PEG){
                int dr[] = {-2, 2, 0, 0};
                int dc[] = {0, 0, -2, 2};
                for(int i=0; i<4; i++){
                    move_t m;
                    m.from_row = r; m.from_col = c;
                    m.to_row = r + dr[i]; m.to_col = c + dc[i];
                    m.over_row = r + dr[i]/2; m.over_col = c + dc[i]/2;
                    if(is_valid(board, m)) return false;
                }
            }
        }
    }
    return true;
}
