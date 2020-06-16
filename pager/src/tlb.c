#include "tlb.h"


int tlb_faults;
int tlb_hits;
int table_index;
tlb_entry_t buffer_entries[TLB_SIZE];

//Initialize tlb and associated variables.
//If you are implementing your tlb using pointer, do dynamic memory allocation for
//the pointer here.
void init_tlb() {
    tlb_faults = 0;
    tlb_hits = 0;
    table_index = 0;
    memset(buffer_entries, 0, TLB_SIZE*sizeof(tlb_entry_t));
}

//Reset tlb and associated variables.
//If you are implementing your tlb using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_tlb() {
    table_index = 0;
    memset(buffer_entries, 0, sizeof(tlb_entry_t)*TLB_SIZE);
}

//Save a tlb_entry with the given page and frame numbers in the tlb.
//Get the appropriate index of tlb to save the entry, call get_next_tlb_index()
//in this regard.
void update_tlb(int page_number, int frame_number) {
    int index = get_next_tlb_index();
    buffer_entries[index].page_number = page_number;
    buffer_entries[index].frame_number = frame_number;
    buffer_entries[index].valid = 1;
}


//Invalidate a tlb_entry with the given frame number, if it exists.
//Return 1, if an invalidation really happens,
//Return -1, otherwise.
int invalidate_tlb(int frame_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (buffer_entries[i].frame_number == frame_number && buffer_entries[i].valid) {
            buffer_entries[i].valid = 0;
            return 1;
        }
    }
    return -1;
}

//Return a frame_number against the page number if such a tlb_entry exists in tlb.
//Return -1, otherwise.
//Update tlb_faults and tlb_hits appropriately.
int check_tlb(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (buffer_entries[i].page_number == page_number && buffer_entries[i].valid) {
            tlb_hits++;
            return buffer_entries[i].frame_number;
        }
    }
    tlb_faults++;
    return -1;
}

//Return tlb_fault statistics.
int get_tlb_faults() {
    return tlb_faults;
}

//Return tlb_hits statistics.
int get_tlb_hits() {
    return tlb_hits;
}

//Return next tlb index that can be used to save a new tlb_entry.
//Implement FIFO replacement strategy when the tlb is full.
int get_next_tlb_index() {
    int index = table_index;
    table_index = (table_index + 1) % TLB_SIZE;
    return index;
}
