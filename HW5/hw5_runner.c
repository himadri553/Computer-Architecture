/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    hw5_runner.c
    - File to be run for hw5
    - make sure that native4-trace.txt and smart4-trace.txt is in the same directory

*/
#include <stdio.h>

/* Global Variables */ 

/* Main runner */
int main () {
    // Import files, check if they are valid
    FILE *fp_naive4 = fopen("naive4-trace.txt", "r");
    FILE *fp_smart4 = fopen("smart4-trace.txt", "r");
    if (fp_naive4 == NULL) {
        perror("Error opening naive4 file");
        return 1;
    }
    else if (fp_smart4 == NULL) {
        perror("Error opening smart4 file");
        return 1;
    }
    
    // native4 simulation
    printf("Starting native4 simulation");
    char native4_line[64];
    // var for chache init
    while (fgets(native4_line, sizeof(native4_line), fp_naive4)) {
        /*
            TODO:
            - add logic to determine hit or miss
            - counter for misses and hits for table
        */
       // Get block number, 
    }

    // smart4 simulation
    printf("Starting smart4 simulation");
    char smart4_line[64];
    while (fgets(smart4_line, sizeof(smart4_line), fp_smart4)) {

    }

    // Output table

    // Close files end function
    fclose(fp_naive4);
    fclose(fp_smart4);
    return 0;
}
