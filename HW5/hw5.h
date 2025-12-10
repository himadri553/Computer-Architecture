#ifndef HW5_H
#define HW5_H

// Function prototypes and cache structs
int run_sim(const char *cache_map_type, const char *trace_filepath);

#define DM_CACHE_LINES 8
typedef struct {
    int valid[DM_CACHE_LINES];
    int tag[DM_CACHE_LINES];
} DM_Cache;

#define TWOWAY_SET 4
#define TWOWAY_WAY 2
typedef struct {
    int valid[4][2];   
    int tag[4][2];     
    int lru[4][2];     // LRU counters per set (0 or 1)
} TwoWayCache;

#define FULL_CACHE_LINES 8
typedef struct {
    int valid[FULL_CACHE_LINES];      
    int tag[FULL_CACHE_LINES];        
    int lru[FULL_CACHE_LINES];        
} FullyAssociativeCache;

#endif