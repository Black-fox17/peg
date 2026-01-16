#include "students.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    linked_list_t *list = read_students("students.txt");
    if (!list) return 1;
    print_linked_list(list);
    destroy_linked_list(list);
    return 0;
}