/**
 * list data structure containing the tasks in the system
 */

#include "task.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    Task *task;
    struct node *next;
} Node;


// inserts a task at the end of a linked list
// should not change head of the linked list
void insert(Node **head, Task *task);

// deletes the given task from the linked list if it exists in the list
void delete(Node **head, Task *task);

// traverse the linked list from head to tail
// print the details of each task in the list
void traverse(Node *head);
