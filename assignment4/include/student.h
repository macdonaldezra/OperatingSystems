#ifndef STUDENT_H
#define STUDENT_H

// number of potential students
#define NUMBER_OF_STUDENTS 3

// the maximum number of times a student will loop through the simulation
#define MAX_NUMBER_OF_LOOPS_OF_A_STUDENT 5

// the maximum  time (in seconds) for a STUDENT to program 
#define MAX_PROGRAM_TIME 5

// the number of available seats to sit in for seeking help
#define NUMBER_OF_SEATS	2

//different states of a student
typedef enum {PROGRAMMING, WAITING, GETTING_HELP, UNKNOWN} student_state;

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


//Print message indicating the student id and programming time
//Simulate programming by calling sleep() system call.
void programming(int studentid, int programingtime);


void *run_student(void *param);


#endif
