#include "students.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    printf("Creating empty linked list\n");
    linked_list_t *list = create_linked_list();
    printf("List created. Size: %zu\n\n", list->size);

    printf("Testing insert_at_head\n");
    insert_at_head(list, 10);
    printf("Inserted 10 at head: ");
    print_linked_list(list);
    
    insert_at_head(list, 20);
    printf("Inserted 20 at head: ");
    print_linked_list(list);
    
    insert_at_head(list, 30);
    printf("Inserted 30 at head: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Testing insert_at_tail\n");
    insert_at_tail(list, 5);
    printf("Inserted 5 at tail: ");
    print_linked_list(list);
    
    insert_at_tail(list, 1);
    printf("Inserted 1 at tail: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Testing insert_at_position\n");
    insert_at_position(list, 15, 2);
    printf("Inserted 15 at position 2: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Testing delete_at_head\n");
    delete_at_head(list);
    printf("Deleted head: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Testing delete_at_tail\n");
    delete_at_tail(list);
    printf("Deleted tail: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Testing delete_at_position\n");
    delete_at_position(list, 1);
    printf("Deleted position 1: ");
    print_linked_list(list);
    printf("Current size: %zu\n\n", list->size);

    printf("Cleaning up basic list\n");
    destroy_linked_list(list);
    printf("List destroyed\n\n");

    printf("Testing parse_student with sample line\n");
    const char *test_line = "Test Student,99999,2,201:4:87.5,202:3:91.0";
    student_t *student = parse_student(test_line);
    if (student) {
        print_student(student);
        free(student->grades);
        free(student->name);
        free(student);
    } else {
        printf("Failed to parse student\n");
    }

    printf("Testing read_students from test_students.txt\n");
    linked_list_t *students_list = read_students("test_students.txt");
    
    if (students_list) {
        printf("Successfully read students file\n");
        printf("Total entries in list: %zu\n\n", students_list->size);
        
        printf("Student data from file:\n");
        node_t *current = students_list->head;
        int count = 1;
        while (current) {
            printf("Entry %d (stored as data value: %d)\n", count++, current->data);
            current = current->next;
        }
        
        destroy_linked_list(students_list);
        printf("\nStudents list destroyed\n");
    } else {
        printf("Failed to read students file\n");
    }

    printf("\n=== ALL TESTS COMPLETED ===\n");
    return 0;
}