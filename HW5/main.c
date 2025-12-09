/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    main.c
    - File to be run for hw5
    - make sure that native4-trace.txt and smart4-trace.txt is in this directory

*/
#include <stdio.h>
#include <stdbool.h>
#include "hw5.h"

/* Global */ 
// Counters
int counter_dm_native = 0;
int counter_dm_smart = 0;
int counter_twoway_native = 0;
int counter_twoway_smart = 0;
int counter_full_native = 0;
int counter_full_smart = 0;

// Cache struct - access each line like this: my_cache.valid[line_to_access]
#define CACHE_LINES 8
typedef struct {
    int valid[CACHE_LINES];
    int tag[CACHE_LINES];
} Cache;

/* Main runner */
int main() {
    // Run all sims
    printf("DM Native misses: %d\n", counter_dm_native);
    counter_dm_native = run_sim("dm", "native4-trace.txt");

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
