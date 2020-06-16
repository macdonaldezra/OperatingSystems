#include "string.h"
#include "schedule.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

Node *listHead = NULL;
int tid = 0;

// Utility function to swap contents of two Node structs.
void swap(Node *a, Node *b) {
    Task *temp = a->task;
    a->task = b->task;
    b->task = temp;
}

// Sort Node tasks using bubble sort algorithm, ordering tasks by their
// burst in ascending order.
void bubbleSort() {
    int swapped;

    if (listHead == NULL)
        return;

    Node *leftPtr;
    Node *rightPtr = NULL;

    do {
        swapped = 0;
        leftPtr = listHead;
        
        while (leftPtr->next != rightPtr) {
            if (leftPtr->task->burst > leftPtr->next->task->burst) {
                swap(leftPtr, leftPtr->next);
                swapped = 1;
            }
            leftPtr = leftPtr->next;
        }
        rightPtr = leftPtr;
    } while (swapped);
}



// Adds a task at the end of the list maintained by this scheduler.
// uses insert method from list.h to add a task at the end of the list. 
void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = (char *) malloc(100);
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = tid;
    tid++;
    insert(&listHead, newTask);
}

// Schedules the tasks in the list ordered by shortest job in ascending
// order.
void schedule() {
    traverse(listHead);

    bubbleSort();

    Node *temp = listHead;
    while (temp != NULL) {
        run(temp->task, temp->task->burst);
        printf("Task [%s] completed.\n", temp->task->name);
        delete(&listHead, listHead->task);
        temp = temp->next;
    }
}
