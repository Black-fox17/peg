#ifndef HISTORY_H
#define HISTORY_H

#include "move.h"
#include <stdbool.h>

#define MAX_MOVES 200

typedef struct {
    move_t moves[MAX_MOVES];
    int count;
} history_t;

void history_init(history_t *h);
bool history_push(history_t *h, move_t m);
move_t history_pop(history_t *h);
bool history_is_empty(const history_t *h);

#endif
