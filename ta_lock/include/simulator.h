#ifndef SIMULATOR_H
#define SIMULATOR_H


#define SEM_TA_NAME "/TA"
#define SEM_STUDENT_NAME "/STUDENT"


#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

//Initializes pthread mutex lock
//Opens both STUDENT and TA semaphores
//Initializes all students id
void init();

//Destroys pthread mutex lock
//Unlinks both STUDENT and TA semaphores
void cleanup();

//Creates all STUDENT threads
void create_students();

//Creates TA thread
void create_ta();

int main();


#endif


