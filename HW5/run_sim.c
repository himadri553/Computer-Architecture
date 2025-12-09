/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    run_sim.c:
    - function to run simulation based on files and sim type
    - outputs # of misses
    - used for each file and sim type in main

    TODO:
    - Integrated this into main and show that it can work with dm for one file
    - add all cache types struct (or maybe make one that can be used for all?)
    - integrated all other types of sim_type (see hsahas_stuff/hs5_brainstorm.txt)

*/
#include <stdio.h>
#include <stdbool.h>

// Cache struct - access each line like this: my_cache.valid[line_to_access]
#define CACHE_LINES 8
typedef struct {
    int valid[CACHE_LINES];
    int tag[CACHE_LINES];
} Cache;

int run_sim(const char *cache_map_type, const char *trace_filepath) {
    // Initalize counters, check cache type and get file
    int miss_counter = 0;
    // ...
    FILE *fp_trace = fopen(trace_filepath, "r");

    // Initalize cache and other vars for simulation
    Cache my_cache;
    for (int i = 0; i < CACHE_LINES; i++) {
        my_cache.valid[i] = 0;
        my_cache.tag[i] = -1;
    }
    char trace_line[64];
    int access_num = 0;
    bool is_hit;

    /* Run simulation */
    printf("Running simulation - %s", cache_map_type);
    while (fgets(trace_line, sizeof(trace_line), fp_trace)) {
        
    }

    return miss_counter;
}