#include "vmm.h"
#include "ptable.h"
#include "tlb.h"
#include "pmemory.h"

#include <stdio.h>
#include <stdlib.h>

// #define PAGE_NUMBER_MASK 0x0000FF00
// #define OFFSET_MASK 0x000000FF
// #define BUFFER_SIZE 10


//Extract the page number from the logical address
int extract_page_number(int logical_address) {
    return (logical_address & PAGE_NUMBER_MASK) >> 8;
}

//Extract the offset from the logical address
int extract_offset(int logical_address) {
    return (logical_address & OFFSET_MASK);
}

//Initialize physical memory, page table and tlb by calling init_xx() from each module.
void init() {
    init_pmemory();
    init_ptable();
    init_tlb();
}

//Clean up physical memory, page table and tlb by calling cleanup_xx() from each module.
void cleanup() {
    cleanup_pmemory();
    cleanup_ptable();
    cleanup_tlb();
}

 
int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: >bin/vmm <backing_store> <logical_address>\n");
        return 0;
    }

    FILE *storeFile, *addressFile;

    storeFile = fopen(argv[1], "r");
    if (storeFile == NULL) {
        printf("Error! cannot open backing store file <%s>\n", argv[1]);
        exit(1);
    }

    addressFile = fopen(argv[2], "r");
    if (addressFile == NULL) {
        printf("Error! cannot open logical address file <%s>\n", argv[2]);
        exit(1);
    }
    
    init();

    int frame_number;
    int page, offset, temp;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, addressFile) != NULL) {
        temp = atoi(buffer);
        page = extract_page_number(temp);
        offset = extract_offset(temp);
        frame_number = check_tlb(page);
        if (frame_number == -1) {
            frame_number = check_ptable(page);
            if (frame_number == -1) {
                frame_number = load_page(page, storeFile);
            }
        }
        printf("%d\n", get_value(frame_number, offset));
    }

    printf("Page Hits: %d\n", get_page_hits());
    printf("Page Faults: %d\n", get_page_faults());
    printf("TLB Hits: %d\n", get_tlb_hits());
    printf("TLB Faults: %d\n", get_tlb_faults());

    cleanup();

    fclose(storeFile);
    fclose(addressFile);

    return 0;
}