#include "pmemory.h"
#include "ptable.h"
#include "tlb.h"
#include "vmm.h"


signed char *physical_memory;


//Initialize physical memory and associated variables.
//If you are implementing your physical memory using pointer, do dynamic memory allocation for
//the pointer here.
//Inform page table module 'ptable.h'the total number of physical frames are being used in this 
//physical memory module by calling set_total_frame_numbers() function from 'ptable.h'.
int init_pmemory() {
    physical_memory = calloc(FRAME_SIZE*NUMBER_OF_FRAMES, sizeof(signed char));
    memset(physical_memory, -1, FRAME_SIZE);
    set_total_number_of_frames(NUMBER_OF_FRAMES);
    return 1;
}

//Reset physical memory and associated variables.
//If you are implementing your physical memory using pointer, free dynamically allocated memory for
//the pointer here.
void cleanup_pmemory() {
    free(physical_memory);
}

//Return the value of the byte that is addressed by the frame number and offset at
//the physical memory.
signed char get_value(int frame_number, int offset) {
    return physical_memory[frame_number*FRAME_SIZE+offset];
}

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
int load_page(int page_number, FILE* bkstr) {
    int frame = get_next_frame_number();
    fseek(bkstr, (long) page_number*FRAME_SIZE, SEEK_SET);
    fread(physical_memory + FRAME_SIZE*frame, sizeof(signed char), FRAME_SIZE, bkstr);
    update_tlb(page_number, frame);
    update_ptable(page_number, frame);
    return frame;    
}
