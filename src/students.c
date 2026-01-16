#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"


static Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

linked_list_t *create_linked_list(void) {
    linked_list_t *list = (linked_list_t*)malloc(sizeof(linked_list_t));
    if (list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void print_linked_list(linked_list_t *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void insert_at_head(linked_list_t *list, int data) {
    if (list == NULL) {
        return;
    }
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void insert_at_tail(linked_list_t *list, int data) {
    if (list == NULL) {
        return;
    }
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void insert_at_position(linked_list_t *list, int data, size_t position) {
    if (list == NULL || position > list->size) {
        return;
    }
    if (position == 0) {
        return insert_at_head(list, data);
    }
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    Node *current = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

void delete_at_head(linked_list_t *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
}

void delete_at_tail(linked_list_t *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        list->size--;
        return;
    }
    Node *current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    list->size--;
}

void delete_at_position(linked_list_t *list, size_t position) {
    if (list == NULL || list->head == NULL || position >= list->size) {
        return;
    }
    if (position == 0) {
        return delete_at_head(list);
    }
    Node *current = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->size--;
}

void destroy_linked_list(linked_list_t *list) {
    if (list == NULL) {
        return;
    }
    list_clear(list);
    free(list);
}

void list_clear(linked_list_t *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}




student_t *parse_student(const char *line) {
    student_t *s = malloc(sizeof(student_t));
    if (!s) return NULL;

    memset(s, 0, sizeof(student_t));

    unsigned int idx = 0;
    int n = 0;

    if (sscanf(line, "%100[^,],%u,%u,%n",
               s->name, &s->student_number, &s->num_grades, &n) != 3) {
        free(s);
        return NULL;
    }

    s->grades = malloc(s->num_grades * sizeof(grade_t));
    if (!s->grades) {
        free(s);
        return NULL;
    }

    idx = n;
    for (unsigned int i = 0; i < s->num_grades; i++) {
        if (sscanf(line + idx, "%u:%u:%f,%n",
                   &s->grades[i].exam_code,
                   &s->grades[i].ects,
                   &s->grades[i].score, &n) < 3) {
            free_student(s);
            return NULL;
        }
        idx += n;
        s->gpa += s->grades[i].score;
    }

    s->gpa /= s->num_grades;
    return s;
}

void insert_student_sorted(linked_list_t *list, node_t *node) {
    if (list == NULL || node == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = node;
        list->size++;
        return;
    }
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    list->size++;
}

linked_list_t read_students(FILE *file) {
    linked_list_t *list = create_linked_list();
    if (!list) return NULL;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        student_t *s = parse_student(line);
        if (!s) {
            destroy_linked_list(list);
            return NULL;
        }
        node_t *node = create_node(s);
        if (!node) {
            destroy_linked_list(list);
            free_student(s);
            return NULL;
        }
        insert_student_sorted(list, node);
    }
    return list;
}

