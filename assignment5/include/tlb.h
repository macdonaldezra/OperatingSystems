#ifndef TLB_H
#define TLB_H

#define TLB_SIZE 16

#include <stdio.h>
#include <string.h>

struct tlb_entry {
	int page_number;
	int frame_number;
	int valid;
};

typedef struct tlb_entry tlb_entry_t;

//Initialize tlb and associated variables.
//If you are implementing your tlb using pointer, do dynamic memory allocation for
//the pointer here.
void init_tlb();

//Reset tlb and associated variables.
//If you are implementing your tlb using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_tlb();

//Save a tlb_entry with the given page and frame numbers in the tlb.
//Get the appropriate index of tlb to save the entry, call get_next_tlb_index()
//in this regard.
void update_tlb(int page_number, int frame_number);

//Invalidate a tlb_entry with the given frame number, if it exists.
//Return 1, if an invalidation really happens,
//Return -1, otherwise.
int invalidate_tlb(int frame_number);

//Return a frame_number against the page number if such a tlb_entry exists in tlb.
//Return -1, otherwise.
//Update tlb_faults and tlb_hits appropriately.
int check_tlb(int page_number);

//Return tlb_fault statistics.
int get_tlb_faults();

//Return tlb_hits statistics.
int get_tlb_hits();

//Return next tlb index that can be used to save a new tlb_entry.
//Implement FIFO replacement strategy when the tlb is full.
int get_next_tlb_index();

#endif
