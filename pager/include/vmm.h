#ifndef VVM_H
#define VMM_H

#define PAGE_NUMBER_MASK 0x0000FF00
#define OFFSET_MASK 0x000000FF

#define BUFFER_SIZE 10

//Extract the page number from the logical address
int extract_page_number(int logical_address);

//Extract the offset from the logical address
int extract_offset(int logical_address);

//Initialize physical memory, page table and tlb by calling init_xx() from each module.
void init();

//Clean up physical memory, page table and tlb by calling cleanup_xx() from each module.
void cleanup();

//Check whether both backing store path name and logical address file name has been supplied or not.
//Open the backing store file in appropriate mode.
//Open the logical address file.
//Initialize physical memory, page table and tlb by calling init().
//Read each logical address from the address file and do the followings
//			Extract the page number from the logical address calling extract_page_number().
//			Extract the offset from the logical address calling extract_offset().
//			Attempt to get the physical frame number from translation look-aside buffer (TLB) first
//			against the page number. Call check_tlb() from "tlb.h".
//			Check for TLB miss. If TLB miss, attempt to get the physical frame number from page table.
//			Call check_ptable() from 'ptable.h".
//			Check for page table fault. If page table fault, load the page from the backing store to a physical frame and
//			update both page table and TLB for future hit. Call load_page() from 'pmemory.h' for this
// 			purpose.
//			Get the value of the byte that is addressed by the frame number and offset at
//			the physical memory. Call get_value() from 'pmemory.h'.
//When the translations of all logical addresses are complete, print the following statistics in separate lines:
//Page Hits, Page Faults, TLB Hits, and TLB Faults.
//Clean up physical memory, page table, and tlb calling cleanup().
//Close all opened files.
int main(int argc, char** argv);

#endif
