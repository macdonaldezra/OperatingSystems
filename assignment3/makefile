# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall
OBJ=build
INC=include
SRC=src
RSC=resource
BIN=bin

all: fcfs sjf priority rr priority_rr 
	@echo "Executables fcfs, sjf, priority, rr, and priority_rr have been built successfully"

fcfs: scheduler.o list.o cpu.o schedule_fcfs.o
	$(CC) $(CFLAGS) -I${INC} -o ${BIN}/fcfs ${OBJ}/scheduler.o ${OBJ}/schedule_fcfs.o ${OBJ}/list.o ${OBJ}/cpu.o

sjf: scheduler.o list.o cpu.o schedule_sjf.o
	$(CC) $(CFLAGS) -I${INC} -o ${BIN}/sjf ${OBJ}/scheduler.o ${OBJ}/schedule_sjf.o ${OBJ}/list.o ${OBJ}/cpu.o


priority: scheduler.o list.o cpu.o schedule_priority.o
	$(CC) $(CFLAGS) -I${INC} -o ${BIN}/priority ${OBJ}/scheduler.o ${OBJ}/schedule_priority.o ${OBJ}/list.o ${OBJ}/cpu.o


rr: scheduler.o list.o cpu.o schedule_rr.o
	$(CC) $(CFLAGS) -I${INC} -o ${BIN}/rr ${OBJ}/scheduler.o ${OBJ}/schedule_rr.o ${OBJ}/list.o ${OBJ}/cpu.o


priority_rr: scheduler.o list.o cpu.o schedule_priority_rr.o
	$(CC) $(CFLAGS) -I${INC} -o ${BIN}/priority_rr ${OBJ}/scheduler.o ${OBJ}/schedule_priority_rr.o ${OBJ}/list.o ${OBJ}/cpu.o


scheduler.o: ${SRC}/scheduler.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/scheduler.o ${SRC}/scheduler.c

schedule_fcfs.o: ${SRC}/schedule_fcfs.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/schedule_fcfs.o ${SRC}/schedule_fcfs.c

schedule_sjf.o: ${SRC}/schedule_sjf.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/schedule_sjf.o ${SRC}/schedule_sjf.c

schedule_priority.o: ${SRC}/schedule_priority.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/schedule_priority.o ${SRC}/schedule_priority.c

schedule_rr.o: ${SRC}/schedule_rr.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/schedule_rr.o ${SRC}/schedule_rr.c

schedule_priority_rr.o: ${SRC}/schedule_priority_rr.c ${INC}/schedule.h ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/schedule_priority_rr.o ${SRC}/schedule_priority_rr.c


list.o: ${SRC}/list.c ${INC}/list.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/list.o ${SRC}/list.c

cpu.o: ${SRC}/cpu.c ${INC}/cpu.h ${INC}/task.h
	$(CC) $(CFLAGS) -c -I${INC} -o ${OBJ}/cpu.o ${SRC}/cpu.c

clean:
	rm -rf ${OBJ}/*.o
	rm -rf ${BIN}/*



