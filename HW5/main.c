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

/* Main runner */
int main() {
    printf("HW5 - Cache Simulation\n");

    /* Run all sims */ 
    counter_dm_native = run_sim("dm", "./naive4-trace.txt");
    counter_dm_smart = run_sim("dm", "./smart4-trace.txt");
    counter_twoway_native = run_sim("twoway", "./naive4-trace.txt");
    counter_twoway_smart = run_sim("twoway", "./smart4-trace.txt");
    counter_full_native = run_sim("full", "./naive4-trace.txt");   
    counter_full_smart = run_sim("full", "./smart4-trace.txt");

    /* Display table */ 
    FILE *fp_results_table = fopen("./hw5_results/miss_table.txt", "w");
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

    fclose(fp_results_table);

    return 0;
}
