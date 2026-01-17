#ifndef STUDENTS_H
#define STUDENTS_H

#include <stddef.h>  // for size_t
#include <stdio.h>   // for FILE
#include <stdbool.h> // for bool

#define MAX_NAME_LENGTH 100

 typedef struct Node {
    int data;
    struct Node *next;
} node_t    ;

typedef struct {
    node_t *head;
    size_t size;
} linked_list_t; 

typedef struct {
    unsigned int exam_code;
    unsigned int ects;
    double score;
} grade_t;


typedef struct {
    char *name;
    unsigned int student_nr;
    unsigned int num_grades;
    grade_t *grades;
} student_t;

double calculate_gpa(const student_t *student);

student_t *parse_student(const char *line);

void insert_student_sorted(linked_list_t *list, node_t *node);

linked_list_t *read_students(const char *filename);


void print_student(const student_t *student);

linked_list_t *create_linked_list(void);

void print_linked_list(linked_list_t *list);

void destroy_linked_list(linked_list_t *list);

void insert_at_head(linked_list_t *list, int data);

void insert_at_tail(linked_list_t *list, int data);

void insert_at_position(linked_list_t *list, int data, size_t position);

void delete_at_head(linked_list_t *list);

void delete_at_tail(linked_list_t *list);

void delete_at_position(linked_list_t *list, size_t position);

void delete_by_value(linked_list_t *list, int data);

node_t *search(linked_list_t *list, int data);

bool get_at(linked_list_t *list, size_t position, int *data);

size_t size(linked_list_t *list);

bool is_empty(linked_list_t *list);

void reverse(linked_list_t *list);

void clear(linked_list_t *list);

void print(linked_list_t *list);

#endif /* STUDENTS_H */
