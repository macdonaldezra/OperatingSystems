/**
 * Scheduler.c
 *
 * Schedule the tasks in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "schedule.h"

int main(int argc, char *argv[])
{   
	//open the task file
	//read each task line from the file
	//extract name, priority, and burst
	//add the task into the list calling add(name, priority, burst) function from schedule.h
	//repeat above 3 steps for each task in the file.
	//close the task file.
	//schedule all tasks in the list by calling schedule() function from schedule.h
	if (argc < 2) {
		printf("Must pass a file as a parameter.\n");
		return 0;
	}
	
	FILE *fp;
	fp = fopen(argv[1], "r");	
	if (fp == NULL) {
		printf("Unable to open file named: %s\n", argv[1]);
		return 0;
	}
	char buff[64];

	char *token, *taskName;
	taskName = 0;
	int priority, burst;
	while (fgets(buff, 64, fp) != NULL) {
		taskName = strtok(buff, ",");
		token = strtok(NULL, ",");
		priority = atoi(token);
		token = strtok(NULL, ",\n");
		burst = atoi(token);

		add(taskName, priority, burst);
		memset(buff, '\0', 64);
	}

	fclose(fp);

	schedule();

    return 0;
}
