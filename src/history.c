#include "history.h"

void history_init(history_t *h) {
    h->count = 0;
}

bool history_push(history_t *h, move_t m) {
    if (h->count >= MAX_MOVES) return false;
    h->moves[h->count++] = m;
    return true;
}

move_t history_pop(history_t *h) {
    move_t empty = {0};
    if (h->count == 0) return empty; 
    return h->moves[--h->count];
}

bool history_is_empty(const history_t *h) {
    return h->count == 0;
}

