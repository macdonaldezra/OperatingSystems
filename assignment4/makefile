CC = gcc
WFLAG = -Wall
CFLAG = -c -g
GFLAG = -ggdb
IFLAG = -I
LFLAG = -l
INCLUDE=./include
SOURCE =./src
BINARY=./bin
BUILD=./build

all: simulator ta student queue
	${CC} ${WFLAG} ${GFLAG} ${LFLAG}pthread ${BUILD}/simulator.o ${BUILD}/ta.o ${BUILD}/student.o ${BUILD}/queue.o -o ${BINARY}/simulator

simulator: ${SOURCE}/simulator.c ${INCLUDE}/simulator.h
	${CC} ${WFLAG} ${GFLAG} ${CFLAG} ${LFLAG}pthread ${IFLAG} ${INCLUDE} ${SOURCE}/simulator.c -o ${BUILD}/simulator.o

ta: ${SOURCE}/ta.c ${INCLUDE}/ta.h ${INCLUDE}/simulator.h ${INCLUDE}/queue.h
	${CC} ${WFLAG} ${GFLAG} ${CFLAG} ${LFLAG}pthread ${IFLAG} ${INCLUDE} ${SOURCE}/ta.c -o ${BUILD}/ta.o

student: ${SOURCE}/student.c ${INCLUDE}/student.h ${INCLUDE}/simulator.h ${INCLUDE}/queue.h
	${CC} ${WFLAG} ${GFLAG} ${CFLAG}  ${LFLAG}pthread ${IFLAG} ${INCLUDE} ${SOURCE}/student.c -o ${BUILD}/student.o

queue: ${SOURCE}/queue.c ${INCLUDE}/queue.h
	${CC} ${WFLAG} ${GFLAG} ${CFLAG}  ${IFLAG} ${INCLUDE} ${SOURCE}/queue.c -o ${BUILD}/queue.o

.PHONY: clean

clean:
	rm -rf ${BINARY}/*
	rm -rf ${BUILD}/*.o
