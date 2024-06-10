/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name: Walker Todd
 * 9/27/22
 * HONOR CODE: Walker Todd
 */

#include "p1-check.h"

int main (int argc, char **argv)
{
    //Checking for multiple parameters and arguements
    if(argc > 3){
        usage_p1(argv);
        exit(1);
    }

    bool helperflag = false;
    char* fileName;
    FILE* textfile;
    elf_hdr_t hdr;
   
    bool commandLineBool = parse_command_line_p1(argc, argv, &helperflag, &fileName);
    
    //If the title of the file was not entered
    if(fileName == NULL){
            usage_p1(argv);
            exit(1);
    }
    
    //If file does not exists
    if(!(textfile = fopen(fileName, "r")))
    {
        printf("%s","Failed to read file\n");
        exit(1);
    }

    //Opening the File
    textfile = fopen(fileName, "r");

    //Actually opening and reading the header
    bool headerValue = read_header(textfile, &hdr);

    //This is checking for a no option input but still checking the file provided
    // and deciding what error to throw
    if(!commandLineBool){
        if(!headerValue){
             printf("%s","Failed to read file\n");
             exit(1);
        }
        exit(1);
    }

    //Checking the validity of the header
    if(!headerValue){
        printf("%s","Failed to read file\n");
        exit(1);
    }
    dump_header(hdr);

    return EXIT_SUCCESS;
}

