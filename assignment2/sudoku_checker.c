// Author: Ezra MacDonald
// Course: CSCI 360
// Compile Command: gcc sudoku_checker.c -lpthread -o sudoku_checker

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PUZZLE_SIZE 9
#define NUMBER_OF_THREADS 27
#define LINE_MAX_LENGTH 100


int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1]; 	// Im memory representation of a sudoku puzzle solution
int status_map[NUMBER_OF_THREADS];       	// Status maps updated by corresponding worker thread


// Data structure to pass parameters to each worker thread 
typedef struct {
	int thread_no;
	int x; // row
	int y; // col
} parameters;


// Array of worker thread parameter pointers, main thread passes an appropriate  
// parameter pointer to a corresponding worker thread
parameters worker_params[NUMBER_OF_THREADS];
// Array of worker threads, main thread needs to wait for all worker threads to 
// finish before it compiles the final result 
pthread_t workers[NUMBER_OF_THREADS];

// Shows in memory content of a sudoku puzzle solution
void show_puzzle();

// Reads the solution of a sudoku puzzle line by line from a given FILE pointer
// Parses individual values (separated by comma) from each line and puts it at a corresponding location in memory
// Reports error if reading fails
void read_from_file(FILE* sudoku_file);

// Checks whether the row of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Sets the appropriate status value in status_map.
void* row_worker(void* param);

// Checks whether the column of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Sets the appropriate status value in status_map.
void* col_worker(void* param);

// Checks whether the subgrid of the sudoku puzzle solution referred by the param contains all the digits from 1 to 9
// Sets the appropriate status value in status_map.
void* subgrid_worker(void* param);


// Checks whether sudoku puzzle solution input file name is passed as an argument or not
// Reports error and quits, if the input file name is missing.
// Opens the input file.
// Reads from the input file and loads the solution in memory calling read_from_file() function.
// Shows the solution from memory calling show_puzzle() function.
// Creates worker thread parameters
// Creates worker thread passing appropriate parameters and worker function.
// Integrates results produced by worker threads.
// Allocates and frees memory whenever necessary.
int main(int argc, char** argv) {
	// Check for valid number of arguments.
	if (argc < 2) {
		printf("Must pass solved sudoku puzzle as a paramter.\n");
		return 0;
	}

	// open file
	FILE *ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
	}
	
	// read from file and display sudoko puzzle
	read_from_file(ifp);
	fclose(ifp);
	show_puzzle();

	printf("*******************************************************************\n");

	// initialize status_map to hold all valid values.
	for (int q = 0; q < NUMBER_OF_THREADS; q++) { status_map[q] = 1; }

	int status; // value to hold error code if pthread_create fails
	int i, j; // iterator values for determining validation starting indices 
	for (i = 0; i < PUZZLE_SIZE; i++) {
		worker_params[i].thread_no = i; // set thread_no for 
		worker_params[i].x = i; // set starting row
		worker_params[i].y = 0; // set starting column to 0
		// create thread and check if thread creation failed
		status = pthread_create(&workers[i], NULL, row_worker, &worker_params[i]);
		if (status != 0) {
			printf("pthread_create row_worker returned an error code %d\n", status);
			exit(-1);
		}
	}

	j = 0; // hold column starting index
	// initialize column workers
	for (; i < PUZZLE_SIZE*2; i++) {
		worker_params[i].thread_no = i;
		worker_params[i].x = 0; // set starting row to 0
		worker_params[i].y = j; // set starting column
		j++;
		status = pthread_create(&workers[i], NULL, col_worker, &worker_params[i]);
		if (status != 0) {
			printf("pthread_create col_worker returned an error code %d\n", status);
			exit(-1);
		}
	}

	int colStart = 0; // hold column starting index for subgrid worker
	j = 0; // hold row starting index for subgrid worker
	// initialize subgrid workers
	for (; i < NUMBER_OF_THREADS; i++) {
		worker_params[i].thread_no = i;
		worker_params[i].x = j;
		worker_params[i].y = colStart;
		// Increment starting index by 3 until we reach 9, then set colStart = 0
		// and increment starting row (j) by 3.
		colStart = colStart + 3;
		if (colStart == 9) {
			j = j + 3;
			colStart = 0;
		}
		status = pthread_create(&workers[i], NULL, subgrid_worker, &worker_params[i]);
		if (status != 0) {
			printf("pthread_create subgrid_worker returned an error code %d\n", status);
			exit(-1);
		}
	}


	int valid  = 1; // flag to hold validity of puzzle. 
	for (int k = 0; k < NUMBER_OF_THREADS; k++) { // 
		status = pthread_join(workers[k], NULL);
		if (status != 0) {
			printf("pthread_join returned an error code %d\n", status);
			exit(-1);
		}
		if (status_map[k] == 0) {
			valid = 0;
			
		}
	}

	if (valid) {
		printf("**********************************************************************\n");
		printf("........................... Valid Solution ...........................\n");
		printf("**********************************************************************\n");
	} else {
		printf("**********************************************************************\n");
		printf("........................... Invalid Solution .........................\n");
		printf("**********************************************************************\n");
	}

	return 0;
}

void read_from_file(FILE* sudoku_file) {
	char buffer[25];
	int i = 0;
	while (!feof(sudoku_file) && i < PUZZLE_SIZE) {
		int j = 0;

		fgets(buffer, 26, sudoku_file);
		char *num = strtok(buffer, ",");
		while (num != NULL && j < PUZZLE_SIZE) {
			puzzle[i][j] = atoi(num);
			num = strtok(NULL, ",\n");
			j++;
		}

		i++;
	}
}

void show_puzzle() {
	for (int i = 0; i < PUZZLE_SIZE; i++) {
		for (int j = 0; j < PUZZLE_SIZE; j++) {
			printf("%d ", puzzle[i][j]);
		}
		printf("\n");
	}
}

void* row_worker(void* param) {
	parameters *tinfo = param;
	int row = tinfo->x;

	int checkArr[9];
	for (int k = 0; k < PUZZLE_SIZE; k++) { checkArr[k] = 0; }

	printf("Thread %d is checking row %d\n", tinfo->thread_no, row);

	int ind;
	for (int i = 0; i < PUZZLE_SIZE; i++) {
		ind = puzzle[row][i]-1;
		if ((checkArr[ind] != 1) && (0 <= ind) && (ind <= 8)) {
            checkArr[ind] = 1;
        }
    }

	for (int j = 0; j < PUZZLE_SIZE; j++) {
		if (checkArr[j] == 0) {
			status_map[tinfo->thread_no] = 0;
		}
	}

	printf("Status of row %d is %d found by thread %d.\n", row, 
			status_map[tinfo->thread_no], tinfo->thread_no);

	return NULL;
}

void* col_worker(void* param) {
	parameters *tinfo = param;
	int col = tinfo->y;

	int checkArr[9];
	for (int k = 0; k < PUZZLE_SIZE; k++) { checkArr[k] = 0; }

	printf("Thread %d is checking col %d\n", tinfo->thread_no, col);

	int ind;
	for (int i = 0; i < PUZZLE_SIZE; i++) {
		ind = puzzle[i][col]-1;
		if ((checkArr[ind] != 1) && (0 <= ind) && (ind <= 8)) {
            checkArr[ind] = 1;
	    }
    }

	for (int j = 0; j < PUZZLE_SIZE; j++) {
		if (checkArr[j] == 0) {
			status_map[tinfo->thread_no] = 0;
		}
	}

	printf("Status of col %d is %d found by thread %d.\n", col, 
			status_map[tinfo->thread_no], tinfo->thread_no);

	return NULL;
}


void* subgrid_worker(void* param) {
	parameters *tinfo = param;
	int row = tinfo->x;
	int col = tinfo->y;

	int checkArr[9];
	for (int k = 0; k < PUZZLE_SIZE; k++) { checkArr[k] = 0; }

	printf("Thread %d is checking subgrid with starting (row, column): (%d, %d)\n", 
			tinfo->thread_no, row, col);

	int ind;
	for (int i = row; i < row+3; i++) {
		for (int j = col; j < col+3; j++) {
			ind = puzzle[i][j]-1;
			if ((checkArr[ind] != 1) && (0 <= ind) && (ind <= 8)) {
                checkArr[ind] = 1;
            }
		}
	}

	for (int j = 0; j < PUZZLE_SIZE; j++) {
		if (checkArr[j] == 0) {
			status_map[tinfo->thread_no] = 0;
		}
	}

	printf("Status of subgrid with starting (row, column): (%d, %d) is %d found by thread %d.\n", 
			row, col, status_map[tinfo->thread_no], tinfo->thread_no);

	return NULL;
}
