#ifndef PTABLE_H
#define PTABLE_H

#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page_table {
    int frame;
    int valid;
};

typedef struct page_table page_table_t;

//Initialize page table and associated variables.
//If you are implementing your page table using pointer, do dynamic memory allocation for
//the pointer here.
void init_ptable();

//Reset page table and associated variables.
//If you are implementing your page table using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_ptable();

//Set the total number of physical frames available in the physical memory that this page table 
//needs to deal with. init_pmemory() function of 'pmemory.h' must call this function to inform
//the page table how many physical frames are available in the physical memory
void set_total_number_of_frames(int tnframes);

//Set the frame_number value at page number index of page table.
void update_ptable(int page_number, int frame_number);

//Invalidate a page table entry if it contains the frame number.
int invalidate_ptable(int frame_number);

//Return the frame number against the page number, if it is not a page fault.
//Update page fault and page hit statistcs appropriately.
int check_ptable(int page_number);

//Return page fault statistics.
int get_page_faults();

//Return page hit statistics.
int get_page_hits();

//Return either an empty frame number or an appropriate frame number following FIFO page
//replacement strategy.
//Call invalidate_ptable() to invalidate the page table entry with chosen frame number.
//Call invalidate_tlb() from 'tlb.h' to invalidate the tlb entry with chosen frame number.
int get_next_frame_number();


#endif
