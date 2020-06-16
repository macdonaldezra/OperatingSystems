#include "string.h"
#include "schedule.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

Node *listHead = NULL;
Node *roundRobinHead = NULL;
int tid = 0;

// Swap the tasks of two nodes
void swap(Node *a, Node *b) {
    Task *temp = a->task;
    a->task = b->task;
    b->task = temp;
}

// Bubble Sort sorts elements by their task priority in descending order
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
            if (leftPtr->task->priority < leftPtr->next->task->priority) {
                swap(leftPtr, leftPtr->next);
                swapped = 1;
            }
            leftPtr = leftPtr->next;
        }
        rightPtr = leftPtr;
    } while (swapped);
}


// adds a task at the end of the list maintained by this scheduler
// uses insert method from list.h to add a task at the end of the list 
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

void addRoundRobin(char *name, int priority, int burst, int tid) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = (char *) malloc(100);
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = tid;
    insert(&roundRobinHead, newTask);
}

// runs round robin on a subset pointed to by roundRobinHead
void roundRobin() {
    Node *temp = roundRobinHead;
    while (roundRobinHead != NULL) {
        while (temp != NULL) {
            if (temp->task->burst <= QUANTUM) {
                run(temp->task, temp->task->burst);
                printf("Task [%s] finished.\n", temp->task->name);
                delete(&roundRobinHead, temp->task);
            } else {
                temp->task->burst = temp->task->burst - QUANTUM;
                run(temp->task, QUANTUM);
            }
            temp = temp->next;
        }
        temp = roundRobinHead;
    }
}

// schedules the tasks in the list,
// implements shortest job first
void schedule() {
    // output each job
    traverse(listHead);

    // sort files
    bubbleSort();

    // schedule tasks until the linked list is empty. 
    Node *temp = listHead;

    // schedule and execute tasks
    while (temp != NULL) {
        // if ordered tasks have same priority, enter them into sublist and 
        // call roundRobin on set of tasks with equal priority 
        if ((temp->next != NULL) && (temp->task->priority == temp->next->task->priority)) {
            // if priorities are the same, 
            while (temp->task->priority == temp->next->task->priority) {
                addRoundRobin(temp->task->name, temp->task->priority, temp->task->burst, temp->task->tid);
                delete(&listHead, temp->task);
                temp = temp->next;
            }
            addRoundRobin(temp->task->name, temp->task->priority, temp->task->burst, temp->task->tid);
            delete(&listHead, temp->task);
            roundRobin();
            temp = temp->next;
        }
        run(temp->task, temp->task->burst);
        printf("Task [%s] completed.\n", temp->task->name);
        delete(&listHead, temp->task);
        temp = temp->next;
    }
}
