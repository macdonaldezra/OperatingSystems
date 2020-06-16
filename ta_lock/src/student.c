#include "student.h"
#include "queue.h"

extern pthread_mutex_t mutex_lock_ws;
extern sem_t* ta_sem;
extern sem_t* students_sem;



// Print message indicating the student id and programming time
// Simulate programming by calling sleep() system call.
void programming(int studentid, int programingtime) {
    printf("\t\tStudent %d is programming for %d seconds\n", studentid, programingtime);
    sleep(programingtime);
}


void *run_student(void *param) {
    int studentNo = *((int *) param);
    int helpRequested = 0;
    srand(time(NULL));
    int randNumber;
    int queueSize;
    student_state StudentStatus = UNKNOWN;

    while (helpRequested < MAX_NUMBER_OF_LOOPS_OF_A_STUDENT) {
        if (StudentStatus != WAITING) {
            randNumber = (rand() % MAX_PROGRAM_TIME) + 1;
            programming(studentNo, randNumber);
            StudentStatus = PROGRAMMING;
        }
        pthread_mutex_lock(&mutex_lock_ws);
        queueSize = queue_size();
        pthread_mutex_unlock(&mutex_lock_ws);
        if (queueSize < NUMBER_OF_SEATS) {
            // if TA is asleep, wake them up
            // enter critical region
            pthread_mutex_lock(&mutex_lock_ws);
            enqueue(studentNo);
            pthread_mutex_unlock(&mutex_lock_ws);
            // exit critical region
            helpRequested++;
            sem_post(ta_sem);

            StudentStatus = WAITING;
            printf("\t\tStudent <%d> takes a seat to get help, total %d student (s) waiting for help.\n", studentNo, queueSize+1);
            sem_wait(students_sem); // Wait for a TA

            StudentStatus = GETTING_HELP;
            printf("\t\tStudent <<<%d>>> is getting help.\n", studentNo);
        }
    }
    pthread_exit(NULL);
}