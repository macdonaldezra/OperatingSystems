#ifndef PMEMORY_H
#define PMEMORY_H

#define FRAME_SIZE 256
#define NUMBER_OF_FRAMES 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize physical memory and associated variables.
//If you are implementing your physical memory using pointer, do dynamic memory allocation for
//the pointer here.
//Inform page table module 'ptable.h'the total number of physical frames are being used in this 
//physical memory module by calling set_total_frame_numbers() function from 'ptable.h'.
int init_pmemory();

//Reset physical memory and associated variables.
//If you are implementing your physical memory using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_pmemory();

//Return the value of the byte that is addressed by the frame number and offset at
//the physical memory.
signed char get_value(int frame_number, int offset);

//Load the page referred by the page number from the backing store to a physical frame.
//Find a physical frame number calling get_next_frame_number() from 'ptable.h', where this page will be loaded.
//Function get_next_frame_number() returns a frame number that is either empty  or 
//can be replaced using appropriate page replacement strategy.
//Page replacement is decided by page table module'ptable.h' since it holds all page related statistics.
//However, actual loading of the page from the backing store to the physical memory is performed here
//in physical memory module.
//Update the page number and the associated frame number at tlb by calling update_tlb() from 'tlb.h'
//Update the page number and the associated frame number at page table by calling update_ptable()
//from 'ptable.h'.
int load_page(int page_number, FILE* bkstr);


#endif
