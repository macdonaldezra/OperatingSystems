CC = gcc
WFLAG = -Wall
CFLAG = -c
IFLAG = -I
GFLAG = -ggdb
INC = include
BIN = bin
BLD = build
SRC = src

all: vmm pmemory tlb ptable
	${CC} ${WFLAG} ${GFLAG} ${BLD}/vmm.o ${BLD}/pmemory.o ${BLD}/tlb.o ${BLD}/ptable.o -o ${BIN}/vmm

vmm: ${SRC}/vmm.c ${INC}/vmm.h
	${CC} ${WFLAG} ${CFLAG} ${GFLAG} ${IFLAG}${INC} ${SRC}/vmm.c -o ${BLD}/vmm.o

pmemory: ${SRC}/pmemory.c ${INC}/pmemory.h
	${CC} ${WFLAG} ${CFLAG} ${GFLAG} ${IFLAG}${INC} ${SRC}/pmemory.c -o ${BLD}/pmemory.o

tlb: ${SRC}/tlb.c ${INC}/tlb.h
	${CC} ${WFLAG} ${CFLAG} ${GFLAG} ${IFLAG}${INC} ${SRC}/tlb.c -o ${BLD}/tlb.o

ptable: ${SRC}/ptable.c ${INC}/ptable.h
	${CC} ${WFLAG} ${CFLAG} ${GFLAG} ${IFLAG}${INC} ${SRC}/ptable.c -o ${BLD}/ptable.o



.PHONY = clean

clean:
	rm -rf ${BIN}/*
	rm -rf ${BLD}/*
