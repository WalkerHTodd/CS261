/*
 * CS 261: Main driver
 *
 * Name: Walker Todd
 * I have neither given nor recieved outside help from anyone: Walker Todd
 * Recieved TA Help from: Sarah Pinkstaff and Ryley White in online sessions
 * Ryley White helped me with the sizing of my for loop specificily the i * (sizeof) part
 */

#include "p1-check.h"
#include "p2-load.h"

int main (int argc, char **argv)
{
    if(argc > 6){
        usage_p2(argv);
        exit(1);
    }
        
    bool* helperFlag = false;
    bool* segmentsFlag = false;
    bool* membriefFlag = false;
    bool* memfullFlag = false;

    char* fileName = NULL;
    FILE* textfile = NULL;
    elf_hdr_t hdr;
    elf_phdr_t pdhrValues;

    bool parseValue = parse_command_line_p2(argc, argv, &helperFlag, &segmentsFlag, &membriefFlag, &memfullFlag, &fileName);
    
    if(!parseValue && helperFlag){
        usage_p2(argv);
        exit(1);
    }

    //If the title of the file was not entered
    if(membriefFlag && memfullFlag || !fileName){
            usage_p2(argv);
            exit(1);
    }
    
    //If file does not exists
    if(!(textfile = fopen(fileName, "r")))
    {
        //Extra Params Fixing
        if(argc >= 4){
            usage_p2(argv);
            exit(1);
        }
        printf("%s","Failed to read file\n");
        exit(1);
    }

    //Actually opening and reading the header
    if(!read_header(textfile, &hdr)){
            printf("%s","Failed to read file\n");
            exit(1);
    }

    byte_t* memory = (byte_t*) calloc(MEMSIZE, hdr.e_num_phdr);
    
    //How to increment in between the phdrValues?
    // Size of segments as we increment between?
    elf_phdr_t phdr[hdr.e_num_phdr];

    for(int i = 0; i < hdr.e_num_phdr; i++) {
        // Write TA note about how they helped me with the size
        if(!read_phdr(textfile, hdr.e_phdr_start + (i * sizeof(elf_phdr_t)), &phdr[i])){
            //Where unaligned is being thrown
            //Fixed
            printf("%s","Failed to read file\n");
            exit(1);
        }
        if(!load_segment(textfile, memory, phdr[i])){
            //Where unaligned is being thrown after fixing in phdr
            // tEMPORAIRLY FIXED
            printf("%s","Failed to read file\n");
            exit(1);
        }
    }

    if(helperFlag){
        dump_header(hdr);
    }
    
   if(segmentsFlag){
        dump_phdrs(hdr.e_num_phdr, phdr);
    }

    if(memfullFlag){
        dump_memory(memory, 0, MEMSIZE);
    }

    if(membriefFlag){
    for(int i = 0; i < hdr.e_num_phdr; i++) {
            dump_memory(memory,  phdr[i].p_vaddr, phdr[i].p_filesz + phdr[i].p_vaddr);
        }
    }

    // fclose(textfile);
    free(memory);

    return EXIT_SUCCESS;
}

