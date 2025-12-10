/*
    Himadri Saha & Md Nezad
    EECE 4821 Computer Architecture
    HW 5 - Evaluating cache performance

    run_sim.c:
    - function to run simulation based on files and sim type
    - outputs # of misses
    - used for each file and sim type in main

    TODO:
    - Annotate all trace lines with hit / miss and output them into ./hw5_results

*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hw5.h"

int run_sim(const char *cache_map_type, const char *trace_filepath) {
    /* Initalize counters, check cache type and get file */ 
    char op;
    int addr;
    int block_number;
    int cache_index;
    int tag;
    int miss_counter = 0;
    if (strcmp(cache_map_type, "dm") != 0 && strcmp(cache_map_type, "twoway") != 0 && strcmp(cache_map_type, "full") != 0) {
        printf("ERROR: Unsupported cache mapping type: %s\n", cache_map_type);
        return -1;
    }
    FILE *fp_trace = fopen(trace_filepath, "r");
    if (!fp_trace) {
        printf("ERROR: Cannot open trace file: %s\n", trace_filepath);
        return -1;
    }

    /* Initalize cache and other vars for simulation - based on cache_map_type*/
    DM_Cache my_dm_cache;
    TwoWayCache my_twoway_cache;
    FullyAssociativeCache my_full_cache;
    if (strcmp(cache_map_type, "dm") == 0) {
        for (int i = 0; i < DM_CACHE_LINES; i++) {
            my_dm_cache.valid[i] = 0;
            my_dm_cache.tag[i] = -1;
        }
    }
    else if (strcmp(cache_map_type, "twoway") == 0) {
        for (int i = 0; i < TWOWAY_SET; i++) {
            for (int j = 0; j < TWOWAY_WAY; j++) {
                my_twoway_cache.valid[i][j] = 0;
                my_twoway_cache.tag[i][j] = -1;
                my_twoway_cache.lru[i][j] = 0;
            }
        }
    }
    else {
        for (int i = 0; i < FULL_CACHE_LINES; i++) {
            my_full_cache.valid[i] = 0;
            my_full_cache.tag[i] = -1;
            my_full_cache.lru[i] = 0;
        }
    }
    char trace_line[64];
    int access_num = 0;
    bool is_hit;

    /* Prepare annotated trace file */
    char output_filename[128];
    sprintf(output_filename, "./hw5_results/%s_%s_annotated.txt", trace_filepath, cache_map_type);
    FILE *fp_annotated_trace = fopen(output_filename, "w");

    /* Run simulation */
    printf("Running simulation - %s\n", cache_map_type);
    while (fgets(trace_line, sizeof(trace_line), fp_trace)) {
        // reset per-access state
        is_hit = false;
        
        /* Direct Mapped */
        if (strcmp(cache_map_type, "dm") == 0) {
            // Compute vars - DM
            sscanf(trace_line, " %c: %d", &op, &addr);
            block_number = addr / 2;
            cache_index = block_number % DM_CACHE_LINES;         
            tag = block_number / DM_CACHE_LINES;

            // Determine Hit or Miss - DM
            if (my_dm_cache.valid[cache_index] == 1 && my_dm_cache.tag[cache_index] == tag) {
                is_hit = true;
            }
            else {
                is_hit = false;
                miss_counter++;

                my_dm_cache.valid[cache_index] = 1;
                my_dm_cache.tag[cache_index] = tag;
            }
        }

        /* Two Way associtive */
        else if (strcmp(cache_map_type, "twoway") == 0) {
            // Compute vars - twoway
            sscanf(trace_line, " %c: %d", &op, &addr);
            block_number = addr / 2;
            int set = block_number % TWOWAY_SET;
            cache_index = set;         
            tag = block_number / TWOWAY_SET;
            int hit_way = -1;

            /* Determine Hit */ 
            for (int way = 0; way < TWOWAY_WAY; way++) {
                if (my_twoway_cache.valid[set][way] == 1 &&
                    my_twoway_cache.tag[set][way] == tag) {

                    is_hit = true;
                    hit_way = way;

                    // Update LRU: hit way becomes MRU (0), other way becomes LRU (1)
                    my_twoway_cache.lru[set][way] = 0;
                    my_twoway_cache.lru[set][1 - way] = 1;

                    break;
                }
            }

            /* Determine Miss */
            if (!is_hit) {
                miss_counter++;

                // 1. Try to find an INVALID way
                int replaced = -1;
                for (int way = 0; way < TWOWAY_WAY; way++) {
                    if (my_twoway_cache.valid[set][way] == 0) {

                        my_twoway_cache.valid[set][way] = 1;
                        my_twoway_cache.tag[set][way] = tag;

                        // LRU update: this way becomes MRU
                        my_twoway_cache.lru[set][way] = 0;
                        my_twoway_cache.lru[set][1 - way] = 1;

                        replaced = way;
                        break;
                    }
                }

                // 2. use LRU replacement
                if (replaced == -1) {
                    int lru_way = (my_twoway_cache.lru[set][0] == 1) ? 0 : 1;

                    my_twoway_cache.valid[set][lru_way] = 1;
                    my_twoway_cache.tag[set][lru_way] = tag;

                    // This way becomes MRU
                    my_twoway_cache.lru[set][lru_way] = 0;
                    my_twoway_cache.lru[set][1 - lru_way] = 1;
                }
            }
        }

        /* Fully associtive */
        else {
            // Compute Vars - fully associtive
            sscanf(trace_line, " %c: %d", &op, &addr);
            block_number = addr / 2;
            tag = block_number;
            is_hit = false;
            int hit_line = -1;

            // Determine HIT
            for (int line = 0; line < FULL_CACHE_LINES; line++) {
                if (my_full_cache.valid[line] == 1 &&
                    my_full_cache.tag[line] == tag) {
                    is_hit = true;
                    hit_line = line;

                    // LRU update: this line becomes MRU
                    for (int i = 0; i < FULL_CACHE_LINES; i++) {
                        if (my_full_cache.lru[i] < my_full_cache.lru[line]) {
                            my_full_cache.lru[i]++;
                        }
                    }
                    my_full_cache.lru[line] = 0;

                    break;
                }
            }

            // Determine miss
            if (!is_hit) {
                miss_counter++;
                int placed = -1;

                // 1. Try to place in an invalid line first
                for (int line = 0; line < FULL_CACHE_LINES; line++) {
                    if (my_full_cache.valid[line] == 0) {
                        my_full_cache.valid[line] = 1;
                        my_full_cache.tag[line] = tag;

                        // LRU update for insert: this becomes MRU
                        for (int i = 0; i < FULL_CACHE_LINES; i++) {
                            if (my_full_cache.lru[i] < my_full_cache.lru[line]) {
                                my_full_cache.lru[i]++;
                            }
                        }
                        my_full_cache.lru[line] = 0;

                        placed = line;
                        break;
                    }
                }

                // 2. All lines valid replace the GLOBAL LRU line
                if (placed == -1) {
                    // Find line with maximum LRU value
                    int lru_line = 0;
                    for (int line = 1; line < FULL_CACHE_LINES; line++) {
                        if (my_full_cache.lru[line] > my_full_cache.lru[lru_line]) {
                            lru_line = line;
                        }
                    }

                    // Replace LRU line
                    my_full_cache.valid[lru_line] = 1;
                    my_full_cache.tag[lru_line] = tag;

                    // LRU update: replaced line becomes MRU
                    for (int i = 0; i < FULL_CACHE_LINES; i++) {
                        if (my_full_cache.lru[i] < my_full_cache.lru[lru_line]) {
                            my_full_cache.lru[i]++;
                        }
                    }
                    my_full_cache.lru[lru_line] = 0;
                }
            }
        }

        // Annotate trace file
        access_num++;
        const char *hm = is_hit ? "hit" : "miss";
        fprintf(fp_annotated_trace,
            "%c: %d -> %s (tag %d, index %d)\n",
            op, addr, hm, tag, cache_index);
    }
    fclose(fp_trace);

    return miss_counter;
}