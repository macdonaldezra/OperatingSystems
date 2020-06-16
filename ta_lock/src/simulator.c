#include "queue.h"
#include "simulator.h"
#include "student.h"
#include "ta.h"

// the numeric id of each student
int student_id[NUMBER_OF_STUDENTS];

// the thread identifier for TA thread
pthread_t ta;

// the thread identifiers for the STUDENT threads
pthread_t students[NUMBER_OF_STUDENTS];

// the STUDENT semaphore on which the TA will wait and be waked up 
sem_t* students_sem;

// the TA semaphore on which the students will wait and be waked up
sem_t* ta_sem;

// the mutex lock for the shared queue
pthread_mutex_t mutex_lock_ws;


//Initializes pthread mutex lock
//Opens both STUDENT and TA semaphores
//Initializes all students id
void init() {
    pthread_mutex_init(&mutex_lock_ws, NULL);
    
    if ((ta_sem = sem_open(SEM_TA_NAME, O_CREAT, 0660, 0)) == SEM_FAILED) {
        printf("Unable to initialize TA semaphore.\n");
        exit(1);
    }

    if ((students_sem = sem_open(SEM_STUDENT_NAME, O_CREAT, 0660, 0)) == SEM_FAILED) {
        printf("Unable to initialize Student semaphore.\n");
        exit(1);
    }

    for (int i = 1; i <= NUMBER_OF_STUDENTS; i++) {
        student_id[i-1] = i;
    }
}

//Destroys pthread mutex lock
//Unlinks both STUDENT and TA semaphores
void cleanup() {
    pthread_mutex_destroy(&mutex_lock_ws);
    int status = sem_unlink(SEM_TA_NAME);
    if (status != 0) {
        printf("sem_unlink on TA Name returned error code: %d\n", status);
        exit(1);
    }
    status = sem_unlink(SEM_STUDENT_NAME);
    if (status != 0) {
        printf("sem_unlink on Student Name returned error code: %d\n", status);
        exit(1);
    }
}

//Creates all STUDENT threads
void create_students() {
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        int status = pthread_create(&students[i], NULL, run_student, &student_id[i]);
        if (status != 0) {
			printf("pthread_create run_student returned error code: %d\n", status);
			exit(1);
		}
    }
}

//Creates TA thread
void create_ta() {
    int status = pthread_create(&ta, NULL, run_ta, NULL);
    if (status != 0) {
        printf("pthread_create run_ta returned error code: %d\n", status);
        exit(1);
    }
}


int main() {
    init();
    create_ta();
    create_students();

    int status = 0;
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        status = pthread_join(students[i], NULL);
        if (status != 0) {
			printf("pthread_join returned an error code %d\n", status);
			exit(-1);
		}
    }

    status = pthread_cancel(ta);
    cleanup();
    
    return 0;
}
