/*
 * CS 261 PA2: Mini-ELF loader
 *
 * Name: Walker Todd
 * I have neither given nor recieved outside help from anyone: Walker Todd
 * Recieved TA Help from: Sarah Pinkstaff and Ryley White in online sessions
 * Dump Memory - Unaligned Integration tests: Showing a blank space with empty memory and geting the right offset in loops
 */

#include "p2-load.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_phdr (FILE *file, uint16_t offset, elf_phdr_t *phdr)
{
    //If file is null
    if(!phdr || !file || !offset){
        return false;
    }

    if(fseek(file, offset, SEEK_SET) != 0){
         return false;
    }
    //Header is too short
    if((fread(phdr, sizeof(elf_phdr_t), 1, file)) != 1){

        return false;
    }
    //Incorrect magic checker
    if(phdr->magic != 0xDEADBEEF){
        return false;
    }
    if(!phdr->p_vaddr && phdr->p_vaddr != 0){
        //Unaligned is getting caught here
        return false;
    }
    return true;
}

bool load_segment (FILE *file, byte_t *memory, elf_phdr_t phdr) {
    if(!file|| !memory || phdr.p_vaddr > 4096) {
        return false;
    }
    //Fixing Unaligned bit nowi  have to figure out how to empty space
    if(!phdr.p_vaddr && phdr.p_vaddr != 0){
        return false;
    }
    if(fseek(file, phdr.p_offset, SEEK_SET) != 0) {
        return false;
    }
    if(phdr.p_filesz != 0) {
        if (fread(&memory[phdr.p_vaddr], phdr.p_filesz, 1, file) != 1) {
            return false;
        }
    }

    return true;
}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void usage_p2 (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
    printf("  -a      Show all with brief memory\n");
    printf("  -f      Show all with full memory\n");
    printf("  -s      Show the program headers\n");
    printf("  -m      Show the memory contents (brief)\n");
    printf("  -M      Show the memory contents (full)\n");
}

bool parse_command_line_p2 (int argc, char **argv,
        bool *print_header, bool *print_segments,
        bool *print_membrief, bool *print_memfull,
        char **filename) {
    char c;
    bool result = false;
    while((c = getopt(argc,argv,"-hHsmMaf:")) != -1){
        switch(c){
            case 'h':
                return false;
            case 'H':
                *print_header = true;
                result = true;
                break;
            case 's':
                *print_segments = true;
                result = true;
                break;
            case 'm':
                *print_membrief = true;
                result = true;
                break;
            case 'M':
                *print_memfull = true;
                result = true;
                break;
            case 'a':
                *print_header = true;
                *print_segments = true;
                *print_membrief = true;
                result = true;
                break;
            case 'f':
                *print_header = true;
                *print_segments = true;
                *print_memfull = true;
                result = true;
                break;
                
        }
        *filename = optarg;
    }

    return result;
}

void dump_phdrs (uint16_t numphdrs, elf_phdr_t phdr[])
{
    printf(" Segment   Offset    VirtAddr  FileSize  Type      Flag\n");      

    for(int i = 0; i < numphdrs; i++){
        elf_phdr_t temp = phdr[i];

        printf("  %02d       0x%04x    0x%04x    0x%04x", i, temp.p_offset, temp.p_vaddr, temp.p_filesz);
        printf("    ");

        elf_segtype_t memType = temp.p_type;
        switch(memType){
            case DATA:
                printf("DATA");
                printf("      ");
                break;
            case CODE:
                printf("CODE");
                printf("      ");
                break;
            case STACK:
                printf("STACK");
                printf("     ");
                break;
            case HEAP:
                printf("HEAP");
                printf("      ");
                break;
            case UNKNOWN:
                printf("UNKNOWN");
                printf("      ");
                break;
        }


        switch(temp.p_flag){
            case 1:
                printf("  X\n");
                break;
            case 2:
                printf(" W \n");
                break;
            case 3:
                printf(" WX\n");
                break;
            case 4:
                printf("R  \n");
                break;
            case 5:
                printf("R X\n");
                break;
            case 6:
                printf("RW \n");
                break;
            case 7:
                printf("RWX\n");
                break;
        }
    }
}

void dump_memory (byte_t *memory, uint16_t start, uint16_t end) {
  printf("Contents of memory from %04x to %04x:", start, end);
  //TA Help Here
    for(int i = start - (start % 16); i < end; i++){
        if(start == end){
            return;
        }
        if((i % 16) != 0){
            printf(" ");
        } 
        if((i % 8) == 0 && (i % 16) ==8){
            printf(" ");
        }

        if((i % 16) == 0){
            printf("\n");
            printf("  %04x  ", i);
        }

        if(i < start) {
            printf("  ");
        } else {
            printf("%02x", memory[i]);
        }
    }
      printf("\n");
}
