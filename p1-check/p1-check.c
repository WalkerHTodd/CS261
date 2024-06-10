/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: Walker Todd
 * 9/27/22
 * HONOR CODE: Walker Todd
 * Recieved help with some of the formatting of the output from TAs Alyssa, and Alexander
 * Specificly MINI ELF, Program headers and entry point output
 */

#include "p1-check.h"

/**********************************************************************
 *                         REQUIRED FUNCTIONS
 *********************************************************************/

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    //If file is null
    if(file == NULL || hdr == NULL){
        return false;
    }

    //Header is too short
    if((fread(hdr, sizeof(elf_hdr_t), 1, file)) != 1){
        return false;
    }
    //Incorrect magic checker
    if(hdr->magic != 4607045){
        return false;
    }
    return true;
}

/**********************************************************************
 *                         OPTIONAL FUNCTIONS
 *********************************************************************/

void usage_p1 (char **argv)
{
    printf("Usage: %s <option(s)> mini-elf-file\n", argv[0]);
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
}

bool parse_command_line_p1 (int argc, char **argv, bool *print_header, char **filename)
{
    char c;
    bool result;
    while((c = getopt(argc,argv,"-hH:")) != -1){
        switch(c){
            case 'h':
                result = true;
                break;
            case 'H':
                *print_header = true;
                result = true;
                break;
            default:
                 result = false;
                 break;
        }
        *filename = optarg;
    }
    return result;
}

void dump_header (elf_hdr_t hdr) {
    
unsigned char* arrayValues =  &hdr;

for (int i = 0; i < sizeof(elf_hdr_t); i++) {
    if(i==0) {
        printf("%02x", arrayValues[i]);
    }else if(i==8){
        printf("  %02x", arrayValues[i]);
    }  else {
        printf(" %02x", arrayValues[i]);
    }
}
    printf("\nMini-ELF version %d\n", hdr.e_version);
    printf("Entry point %#x\n", hdr.e_entry);
    printf("There are %d program headers, starting at offset %d (%#x)", hdr.e_num_phdr, hdr.e_phdr_start, hdr.e_phdr_start);

    if(hdr.e_symtab != 0){
        printf("\nThere is a symbol table starting at offset %d (%#x)",hdr.e_symtab, hdr.e_symtab);
    } else {
        printf("\n%s", "There is no symbol table present");
    }

    if(hdr.e_strtab != 0){
        printf("\nThere is a string table starting at offset %d (%#x)\n",hdr.e_strtab ,hdr.e_strtab );

    } else {
        printf("\n%s", "There is no string table present\n");

    }
}

