#include "string.h"
#include "schedule.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

Node *listHead = NULL;
int tid = 0;

// Add a task at the end of the list maintained by this scheduler.
// Uses insert method from list.h to add a task at the end of the list. 
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


// Schedules the tasks in the list, and runs each task for amount of bursts
// given by QUANTUM.
void schedule() {
    traverse(listHead);
    Node *temp = listHead;
    while (listHead != NULL) {
        while (temp != NULL) {
            if (temp->task->burst <= QUANTUM) {
                run(temp->task, temp->task->burst);
                printf("Task [%s] completed.\n", temp->task->name);
                delete(&listHead, temp->task);
            } else {
                temp->task->burst = temp->task->burst - QUANTUM;
                run(temp->task, QUANTUM);
            }
            temp = temp->next;
        }
        temp = listHead;
    }
}
