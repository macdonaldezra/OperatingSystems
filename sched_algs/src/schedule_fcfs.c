#include "string.h"
#include "schedule.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

Node *listHead = NULL;
int tid = 0;

// Add a task at the end of linked list whose head is given by listHead.
// Uses insert method from list.h to add a task at the end of the list. 
void add(char *name, int priority, int burst) {
    // create new task
    Task *newTask = malloc(sizeof(Task));
    newTask->name = (char *) malloc(100);
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = tid;

    tid++;
    insert(&listHead, newTask);
}

// schedules the tasks in the list and implements first-come-first-serve
void schedule() {
    traverse(listHead);
    
    // iterate over list from start to finish and delete nodes once they are
    // run.
    while (listHead != NULL) {
        run(listHead->task, listHead->task->burst);
        printf("Task [%s] completed.\n", listHead->task->name);
        delete(&listHead, listHead->task);
    }
}
