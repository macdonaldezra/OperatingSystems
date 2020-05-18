//*************************************************************
// * Simple UNIX Shell
// * @author: Ezra MacDonald
// * compiled with: gcc -Wall lab1 -o lab1.c
// ************************************************************

#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LENGTH 80 // The maximum length of the commands


int main(void) {
    char *args[MAX_LENGTH/2+1]; // arguments to hold parsed commands
    char *args2[MAX_LENGTH/2+1]; // args for pipe
    char prevCommand[MAX_LENGTH] = "";
    // initialize pointers to 0
    for (int q = 0; q < MAX_LENGTH/2+1; q++) {
        args[q] = 0;
        args2[q] = 0;
    }

    while (1) {
        char command[MAX_LENGTH]; // holds command string
        int ampersand, pipeFlag, input, output, exclaim;
        ampersand = pipeFlag = input = output = exclaim = 0; // flags for <, >, &, |        

        // Read in command from the user
        printf("ssh>> ");
        fflush(stdout);
        fgets(command, MAX_LENGTH, stdin);

        // Parse provided commands
        if (strcmp(command, "exit\n") == 0)
            break;
        else if (strcmp(command, "!!\n") == 0) {
            strcpy(command, prevCommand);
        } else {
            strcpy(prevCommand, command);
        }

        int i = 0;
        char *token = strtok(command, " \n");
        char *fileName = 0;

        // Read in to token first then arg[i]
        // Throw away < > | & operators
        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                input = 1;
                fileName = strtok(NULL, " \n");
            } else if (strcmp(token, ">") == 0) {
                output = 1;
                fileName = strtok(NULL, " \n");
            } else if (strcmp(token, "|") == 0) {
                pipeFlag = 1;
                int p = 0;
                // read in remainder of command to args2
                token = strtok(NULL, " \n");
                while (token != NULL) {
                    args2[p] = token;
                    token = strtok(NULL, " \n");
                    p = p + 1;
                }
                args[p] = NULL;
                break;
            } else if (strcmp(token, "&") == 0) {
                ampersand = 1;
            } else {
                args[i] = token;
                i = i + 1;
            }
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;

        if (input) {
            pid_t pid = fork(); // fork process
            if (pid == 0) { // check that fork is child process
                int iDesc = open(fileName, O_RDONLY); // open file in read mode
                dup2(iDesc, STDIN_FILENO);
                close(iDesc);
                execvp(args[0], args); // change process image
                // below will execute only if the above call to execvp failed
                printf("Error: unable to execute command.\n");
                exit(EXIT_FAILURE);
            }
            if (!ampersand)
                waitpid(pid, NULL, 0);
        } else if (output) {
            pid_t pid = fork();
            if (pid == 0) {
                int iDesc = open(fileName, O_WRONLY | O_CREAT, 0644); // open or create file for writing
                dup2(iDesc, STDOUT_FILENO); // write to file
                close(iDesc); // close file descriptor
                execvp(args[0], args); // change process image
                printf("Error: unable to execute command.\n");
                exit(EXIT_FAILURE);
            }
            if (!ampersand)
                waitpid(pid, NULL, 0);
        } else if (pipeFlag) {
            pid_t pid = fork();
            if (pid == 0) {
                int pipefd[2]; // initialize pipe argument to hold read/write descriptor
                // create pipe and check validity   
                if (pipe(pipefd) == -1) {
                    printf("Error: Unable to execute pipe.\n");
                    exit(EXIT_FAILURE);
                }
                pid = fork();
                if (pid == 0) {
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO); // copy read end descriptor to standard input
                    
                    close(pipefd[1]); // close write end descriptor
                    execvp(args[0], args); // execute arguments before pipe
                    printf("Error: unable to execute command.\n");
                    exit(EXIT_FAILURE);
                } else {
                    close(pipefd[1]);
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]); // close read end descriptor
                    // copy write end descriptor to standard output
                    execvp(args2[0], args2); // execute arguments after pipe
                    printf("Error: unable to execute command.\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (!ampersand)
                waitpid(pid, NULL, 0);
        } else {
            // if no flags have been raised, fork child process and execute command
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                printf("Error: unable to execute command.\n");
                exit(EXIT_FAILURE);
            }
            if (!ampersand)
                waitpid(pid, NULL, 0);
        }
   }
    return 0;
}
