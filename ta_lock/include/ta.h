#ifndef TA_H
#define TA_H


#define MAX_HELP_TIME 5

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


void *run_ta(void *param);


//Print message indicating the student number and help time
//Simulate helping by calling sleep() system call.
void help_student(int helptime, int number);

#endif
