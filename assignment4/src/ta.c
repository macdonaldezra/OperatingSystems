#include "ta.h"
#include "queue.h"


extern pthread_mutex_t mutex_lock_ws;
extern sem_t* ta_sem;
extern sem_t* students_sem;


void *run_ta(void *param) {
    int queueSize;
    srand(time(NULL));
    int randNumber;
    int studentId;

    while (1) {
        pthread_mutex_lock(&mutex_lock_ws);
        queueSize = queue_size();
        if (queueSize == 0) {
            printf("\nTA is going to sleep, waiting for student to arrive ......\n");
            // Wait until at least one student has been added to queue
            pthread_mutex_unlock(&mutex_lock_ws);
            sem_wait(ta_sem);
            int sem_count;
            sem_getvalue(ta_sem, &sem_count);
            for (int i = 0; i <= sem_count; i++) { sem_wait(ta_sem); }
        } else {
            // Enter critical region
            studentId = dequeue();
            pthread_mutex_unlock(&mutex_lock_ws);
            // Exit critical region
            
            randNumber = (rand() % MAX_HELP_TIME) + 1;
            help_student(randNumber, studentId);
            sem_post(students_sem); // free up TA
        }
    }
    pthread_exit(NULL);
}



// Print message indicating the student number and help time
//Simulate helping by calling sleep() system call.
void help_student(int helptime, int number) {
    printf("TA Helping student <<%d>> for %d seconds.\n", number, helptime);
    sleep(helptime);
}
