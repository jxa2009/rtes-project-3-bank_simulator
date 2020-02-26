#ifndef BREAKS_H
#define BREAKS_H
/**
 * Struct holding the information for a break that a teller will have
 * [unsigned int] Num      - Number of breaks taken
 * [unsigned int] Total    - Total amount of time across all breaks taken 
 * [unsigned int] Average  - Average amount of time taken per break
 * [unsigned int] Shortest - Shortest amount of time taken for a break
 * [unsigned int] Longest  - Longest amount of time taken for ab reak
 * 
 * [unsigned int] Length   - Time remaining on break
 * 
 * */
typedef struct Break_S
{
    // Metrics for breaks for a teller
    unsigned int Num; 
    unsigned int Total;
    unsigned int Shortest;
    unsigned int Longest;

    // Active information
    unsigned int Length;
} BreakS;

#endif