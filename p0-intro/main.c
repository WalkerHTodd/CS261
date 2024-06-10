/*
 * CS 261: Intro project driver
 *
 * Name: 
 */

#include "p0-intro.h"

int main (int argc, char **argv)
{
    // argc number of arguements
    // argv Array of strings
    char c;

    bool gflag = false;

    bool cflag = false;
    char* cArg = NULL;

    bool tflag = false;
    char* tArg  = NULL;

    bool uflag = false;
    char* uArg  = NULL;
    //Using a flag and arguement storage spot to determine what to use.
    //if the flag is on then i do it and use the dedicated arguement
    while((c = getopt(argc,argv,"-gc:t:u:")) != -1){
        switch(c){
            case 'g':
                gflag = true;
                break;
            case 'c':
                cflag = true;
                cArg = optarg;
                break;

            case 't':
                tflag = true;
                tArg = optarg;
                break;

            case 'u':
                uflag = true;
                uArg = optarg;
                break;
            default:
                printf("Invalid argument.\n");
                exit(1);
        }
    }
    //Does hello world if none of the flags are true
    if(!gflag && !cflag && !tflag && !uflag){
        printf("Hello, world!\n");
    }


    //Goodbye mode ("-g")
    if(gflag){
        printf("Goodbye!\n");
    }


    // Cat mode ("-c <file>")
    if(cflag) {
        FILE* textfile;
        char line[100];

        //Null checker
        if(cArg == NULL){
            printf("Invalid argument.\n");
            exit(1);
        }
        //Checking to see if the file exists

        if(!(textfile = fopen(cArg, "r")))
        {
            printf("Invalid file.\n");
            exit(1);
        } 

        textfile = fopen(cArg, "r");
        while(fgets(line, 128, textfile)){
            printf(line);
        }
        fclose(textfile);
    }
        
    

    
    //Triodd mode ("-t <n>")
    if(tflag == true){
        //Null check
        if(tArg == NULL){
            printf("Invalid argument.\n");
        }
        //Converting a string into an integer to be interated
        int n = strtol(tArg, NULL, 10);
        for(int i = 1; i <= n; i++){
            //If both divided by 3 and odd
            if(i % 2 != 0 && i % 3 == 0){
                printf("triodd\n");
              // if not even
            } else if(i % 2 != 0){
                printf("odd\n");
              // if divided by 3
            } else if(i % 3 == 0){
                printf("tri\n");
             } else{
                printf("%d\n",i);
             }
        }
    }

    // Uniq mode ("-u <file>")
    if(uflag == true){
        FILE* textfile;
        char line[100] = "";
        char temp[100] = "";
        size_t size;

        if(uArg == NULL){
            printf("Invalid argument.\n");
            exit(1);
        }
        //Checking to see if the file exists
         if(!(textfile = fopen(uArg, "r")))
        {
            printf("Invalid file.\n");
            exit(1);
        } 
        //Opening the File
        textfile = fopen(uArg, "r");
        while(fgets(line, 128, textfile)){
            // This is what compares the buffer/previous line to the
            // new line that is being grabbed
            if(strncmp(line,temp, 100) != 0) {
                printf(line);
            }
            size = sizeof (line);
            //Copies the previous line into the buffer to be compared later
            snprintf(temp, size, "%s", line);
          }
        fclose(textfile);
    }

    return EXIT_SUCCESS;
}
