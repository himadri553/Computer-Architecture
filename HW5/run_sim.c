/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    run_sim.c:
    - function to run simulation based on files and sim type
    - outputs # of misses
    - used for each file and sim type in main

    TODO:
    - add all cache types struct (or maybe make one that can be used for all?)
    - integrated all other types of sim_type (see hsahas_stuff/hs5_brainstorm.txt)

*/
#include <stdio.h>
#include <stdbool.h>
#include "hw5.h"

int run_sim(const char *cache_map_type, const char *trace_filepath) {
    // Initalize counters, check cache type and get file
    int miss_counter = 0;
    // ...
    FILE *fp_trace = fopen(trace_filepath, "r");
    if (!fp_trace) {
        printf("ERROR: Cannot open trace file: %s\n", trace_filepath);
        return -1;
    }

    // Initalize cache and other vars for simulation
    DM_Cache my_cache;
    for (int i = 0; i < DM_CACHE_LINES; i++) {
        my_cache.valid[i] = 0;
        my_cache.tag[i] = -1;
    }
    char trace_line[64];
    int access_num = 0;
    bool is_hit;

    /* Run simulation */
    printf("Running simulation - %s\n", cache_map_type);
    while (fgets(trace_line, sizeof(trace_line), fp_trace)) {
        // DM - Compute vars
        char op;
        int addr;
        sscanf(trace_line, " %c: %d", &op, &addr);
        int block_number = addr / 2;
        int index = block_number % DM_CACHE_LINES;         
        int tag = block_number / DM_CACHE_LINES;

        // Determine Hit or Miss and update cache accordingly 
        if (my_cache.valid[index] == 1 && my_cache.tag[index] == tag) {
            is_hit = true;
        }
        else {
            is_hit = false;
            miss_counter++;

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
    fclose(fp_trace);

    return miss_counter;
}

