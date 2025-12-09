#ifndef HW5_H
#define HW5_H

// Function prototypes and cache structs
int run_sim(const char *cache_map_type, const char *trace_filepath);
#define DM_CACHE_LINES 8
typedef struct {
    int valid[DM_CACHE_LINES];
    int tag[DM_CACHE_LINES];
} DM_Cache;

#endif