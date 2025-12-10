# HW 5 - Evaluating cache performance
## Himadri Saha & Md Nezad
### EECE 4821 Computer Architecture

### How to Run using GCC
You can run main.exe as is or use `gcc .\main.c .\run_sim.c -o main ` to build a .exe file to run.

## Mapping Policies Implementation
### Direct-Mapped
Each block maps to only one cache line using index = block % 8, and on a miss the line is overwritten. 

### Two Way Set Associative
Each block maps to one of 2 ways in a set, hit checks both ways, miss replaces invalid way first, otherwise uses LRU inside the set.

### Fully Associative
A block can go in any of the 8 lines, the code searches the entire cache for a hit, on miss fills first invalid line, otherwise replaces the global LRU line.
