/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    hw5_runner.c
    - File to be run for hw5
    - make sure that native4-trace.txt and smart4-trace.txt is in this directory

*/
#include <stdio.h>
#include <stdbool.h>

/* Global */ 
#define CACHE_LINES 8

// Counters
int counter_dm_native = 0;
int counter_dm_smart = 0;
int counter_twoway_native = 0;
int counter_twoway_smart = 0;
int counter_full_native = 0;
int counter_full_smart = 0;

typedef struct {
    int valid[CACHE_LINES];
    int tag[CACHE_LINES];
} Cache;

/* Main runner */
int main() {
    // Import files, check if they are valid
    FILE *fp_naive4 = fopen("naive4-trace.txt", "r");
    FILE *fp_smart4 = fopen("smart4-trace.txt", "r");
    if (fp_naive4 == NULL) {
        perror("Error opening naive4 file - make sure that native4-trace.txt and smart4-trace.txt is in this directory\n");
        return 1;
    }
    else if (fp_smart4 == NULL) {
        perror("Error opening smart4 file - make sure that native4-trace.txt and smart4-trace.txt is in this directory\n");
        return 1;
    }

    // Initalize Cache 
    Cache my_cache;
    for (int i = 0; i < CACHE_LINES; i++) {
        my_cache.valid[i] = 0;
        my_cache.tag[i] = -1;
    }

    /*
        native4 simulation - DIRECT-MAPPED
    */
    printf("Starting native4 simulation - DIRECT-MAPPED\n");
    char native4_line[64];
    int access_num = 0;
    bool is_hit;
    while (fgets(native4_line, sizeof(native4_line), fp_naive4)) {       
        // Extract line and compute block info (Index correlates with which cache line the block maps to)
        char op;
        int addr;
        sscanf(native4_line, " %c: %d", &op, &addr);
        int block_number = addr / 2;
        int index = block_number % CACHE_LINES;         
        int tag = block_number / CACHE_LINES;
        
        // Determine Hit or Miss and update cache accordingly 
        if (my_cache.valid[index] == 1 && my_cache.tag[index] == tag) {
            is_hit = true;
        }
        else {
            is_hit = false;
            counter_dm_native++;

            my_cache.valid[index] = 1;
            my_cache.tag[index] = tag;
        }
        
        // Access printout for debugging
        access_num++;
        printf("Access: %d, Block: %d, Index: %d, Tag: %d ", access_num, block_number, index, tag);
        if (is_hit) {
            printf("HIT");
        }
        else {
            printf("MISS");
        }
        printf("\n");
        
    }
    fclose(fp_naive4);
    fclose(fp_smart4);

    /* Display table */ 
    FILE *fp_results_table = fopen("hw5_results.txt", "w");
    fprintf(fp_results_table, "HW5 Simulation results - # of misses\n");
    fprintf(fp_results_table, "-----------------------------------------------------------\n");
    fprintf(fp_results_table, "%-25s %-15s %-15s\n", "", "Naive", "Smart");
    fprintf(fp_results_table, "-----------------------------------------------------------\n");
    fprintf(fp_results_table, "%-25s %-15d %-15d\n",
        "Direct mapped",
        counter_dm_native,
        counter_dm_smart);  
    fprintf(fp_results_table, "-----------------------------------------------------------\n"); 
    fprintf(fp_results_table, "%-25s %-15d %-15d\n",
        "Two-way set associative",
        counter_twoway_native,
        counter_twoway_smart);
    fprintf(fp_results_table, "-----------------------------------------------------------\n"); 
    fprintf(fp_results_table, "%-25s %-15d %-15d\n",
        "Fully-associative",
        counter_full_native,
        counter_full_smart); 

    return 0;
}
