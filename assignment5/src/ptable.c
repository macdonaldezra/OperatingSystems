#include "ptable.h"
#include "tlb.h"


int page_faults;
int page_hits;
int next_frame;
int max_frames;
page_table_t page_entries[PAGE_TABLE_SIZE];


//Initialize page table and associated variables.
//If you are implementing your page table using pointer, do dynamic memory allocation for
//the pointer here.
void init_ptable() {
    page_faults = 0;
    page_hits = 0;
    next_frame = 0;
    memset(page_entries, 0, sizeof(page_table_t)*PAGE_TABLE_SIZE);
}

//Reset page table and associated variables.
//If you are implementing your page table using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_ptable() {
    next_frame = 0;
}

// Set the total number of physical frames available in the physical memory that this page table 
// needs to deal with. init_pmemory() function of 'pmemory.h' must call this function to inform
// the page table how many physical frames are available in the physical memory
void set_total_number_of_frames(int tnframes) {
    max_frames = tnframes;
}

//Set the frame_number value at page number index of page table.
void update_ptable(int page_number, int frame_number) {
    page_entries[page_number].frame = frame_number;
    page_entries[page_number].valid = 1;
}

//Invalidate a page table entry if it contains the frame number.
int invalidate_ptable(int frame_number) {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (page_entries[i].frame == frame_number && page_entries[i].valid) {
            page_entries[i].valid = 0;
            return 1;
        }
    }
    return -1;
}

// Return the frame number against the page number, if it is not a page fault.
// Update page fault and page hit statistcs appropriately.
int check_ptable(int page_number) {
    if (page_entries[page_number].valid) {
        page_hits++;
        return page_entries[page_number].frame;
    }
    page_faults++;
    return -1;
}

//Return page fault statistics.
int get_page_faults() {
    return page_faults;
}

//Return page hit statistics.
int get_page_hits() {
    return page_hits;
}

//Return either an empty frame number or an appropriate frame number following FIFO page
//replacement strategy.
//Call invalidate_ptable() to invalidate the page table entry with chosen frame number.
//Call invalidate_tlb() from 'tlb.h' to invalidate the tlb entry with chosen frame number.
int get_next_frame_number() {
    int frame_number = next_frame;
    next_frame = (next_frame + 1) % max_frames;

    int valid = invalidate_ptable(frame_number);
    if (valid) {
        invalidate_tlb(frame_number);
    }

    return frame_number;
}
