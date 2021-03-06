Operating Systems:
------------------
A collection of scripts and packages developed with OS libraries in C.

Installation:
-------------
Each respective directory contains a project that can be compiled and executed from the command line. Ensure that
both bin/ and build/ directories have been created before running a given makefile. Each program has been tested
using either user input or test files.

cmd_util:
-------------
 A simple command line utility in C, that includes fork, pipe and basic command execution.

sudoku_check:
-------------
Program validates Sudoku puzzles using multitherating. Program expects valid Sudoku solution file 
to be passed as a parameter, where the file has the following format:

5,3,4,6,7,8,9,1,2 <br/>
6,7,2,1,9,5,3,4,8 <br/>
1,9,8,3,4,2,5,6,7 <br/>
8,5,9,7,6,1,4,2,3 <br/>
4,2,6,8,5,3,7,9,1 <br/>
7,1,3,9,2,4,8,5,6 <br/>
9,6,1,5,3,7,2,8,4 <br/>
2,8,7,4,1,9,6,3,5 <br/>
3,4,5,2,8,6,1,7,9 <br/>

sched_algs:
-------------
A series of scheduling algorithms implemented in C.

Implemented scheduling algorithms include:
    First Come First Serve (FCFS)
    Priority
    Priority Round Robin (PRR)
    Round Robin (RR)
    Shortest Job First (SJF)

Program expects a file including a list of tasks to be passed as
input, with the following format:

T1, 4, 20 <br/>
T2, 3, 25 <br/>
T3, 3, 25 <br/>
T4, 5, 15 <br/>
T5, 5, 20 <br/>
T6, 1, 10 <br/>
T7, 3, 30 <br/>
T8, 10, 25 <br/>

to_lock:
-------------
Program simulates a Teachers Assistant with a waiting room serving Students
using Mutex's and Semaphores.

pager:
-------------
Program simulates integrating Translation Lookaside Buffer, Page Table, Physical
Memory and Virtual Memory in C. Program is evaluated on two input files - a binary
file representing program memory and a file containing a list of memory addresses
that would be called during program execution.
