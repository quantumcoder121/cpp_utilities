#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    // syntax errors
    if (argc != 3 && argc != 4){
        printf("usage: ./comp <compiler> <filename> [outputfilename]\n");
        exit(1);
    }

    int rc;

    rc = fork();

    if (rc < 0) {
        // fork failed
        printf("error: fork failed due to system overload\n");
        exit(1);
    }
    
    else if (rc == 0) {

        // child process for compiling the code
        
        char *myargs[5];

        myargs[0] = strdup(argv[1]); // compiler program (can be g++ or s++)
        myargs[1] = strdup("-o"); // output file indicator
        
        // output file name
        if (argc == 3) myargs[2] = strdup(argv[2]);
        else myargs[2] = strdup(argv[3]);

        // making the c file name using dynamic memory allocation
        int str_len = snprintf(NULL, 0, "%s.cpp", argv[2]);
        char* c_filename = malloc(str_len + 1);
        snprintf(c_filename, str_len + 1, "%s.cpp", argv[2]);
        
        myargs[3] = strdup(c_filename); // c file name
        myargs[4] = NULL; // end of array

        execvp(myargs[0], myargs); // running program
        
        // checking for compilation errors
        printf("error: compilation error\n");
        exit(1);
    }
    
    else {

        // parent process for executing the output file
        
        wait(NULL); // waiting for compilation to complete
        
        char *myargs[2];

        // making the output file name using dynamic memory allocation
        char* out_filename;
        if (argc == 3){
            int str_len = snprintf(NULL, 0, "./%s", argv[2]);
            out_filename = malloc(str_len + 1);
            snprintf(out_filename, str_len + 1, "./%s", argv[2]);
        }
        else {
            int str_len = snprintf(NULL, 0, "./%s", argv[3]);
            out_filename = malloc(str_len + 1);
            snprintf(out_filename, str_len + 1, "./%s", argv[3]);
        }

        myargs[0] = strdup(out_filename); // output file name
        myargs[1] = NULL; // end of array

        execvp(myargs[0], myargs); // running program

        // checking for execution errors
        printf("error: execution error\n");
        exit(1);        
    }

    return 0;
}