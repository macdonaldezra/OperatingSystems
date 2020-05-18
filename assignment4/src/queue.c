#include "queue.h"

Node *back = 0;
Node *front = 0;
int size = 0;

//Adds the student id at the back of the queue.
void enqueue(int st_id) {
    // create new node
    Node *newStudent = malloc(sizeof(Node));
    newStudent->next = 0;
    newStudent->id = st_id;
    newStudent->prev = 0;
    size++;
    
    // if list is empty, set front = back = newStudent
    if (front == 0) {
        newStudent->next = 0;
        back = newStudent;
        front = newStudent;
    } else {
        newStudent->next = back;
        back->prev = newStudent;
        back = newStudent;
    }
}


//Removes a student id from the head of the queue
int dequeue() {
    if (size == 0) {
        return -1;
    }

    int st_id = front->id;
    Node *temp = front;
    front = front->prev;

    if (size == 1) {
        back = 0;
    }
    free(temp);
    size--;
    return st_id;
}


//Returns the current size of the queue.
int queue_size() {
    return size;
}