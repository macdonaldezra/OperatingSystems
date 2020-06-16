#include "../include/list.h"


void insert(Node **head, Task *task) {
    // create new node to insert to linked list
    Node **tracer = head;
    Node *newNode = malloc(sizeof(Node));
    newNode->task = task;
    newNode->next = NULL;

    // iterate to end of list and insert newNode
    while(*tracer) {
        tracer = &(*tracer)->next;
    }
    *tracer = newNode;
}


void delete(Node **head, Task *task) {
    if (*head == NULL) {
        return;
    }

    Node *tracer = *head;
    // Case: task is at the beginning of the list.
    if (tracer->task->tid == task->tid) {
        *head = tracer->next;
        free(tracer->task->name);
        free(tracer->task);
        free(tracer);
        return;
    }

    Node *prev = NULL;
    // iterate over list until we find one with matching task id.
    while (tracer->next != NULL) {
        prev = tracer;
        tracer = tracer->next;
        if (tracer->task->tid == task->tid) {
            break;
        }
    }

    // delete note at middle or end of list and connect disconnected nodes.
    if (tracer->task->tid == task->tid) {
        Node *temp = NULL;
        if (tracer->next != NULL) {
            temp = tracer->next;
        }
        free(tracer->task->name);
        free(tracer->task);
        free(tracer);
        prev->next = temp;
        if (temp != NULL && temp->next != NULL) {
            tracer = temp->next;
        }
    }
}

void traverse(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *itr = head;
    while (itr != NULL) {
        printf("[%s] [%d] [%d]\n", itr->task->name, itr->task->priority, itr->task->burst);
        itr = itr->next;
    }
}
