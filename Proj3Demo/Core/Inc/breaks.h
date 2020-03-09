#ifndef BREAKS_H
#define BREAKS_H

#define MIN_TIME_UNTIL_BREAK  (1800)
#define MAX_TIME_UNTIL_BREAK  (3600)
#define DIFF_TIME_UNTIL_BREAK (1800)

#define MIN_BREAK_LENGTH     (60)
#define MAX_BREAK_LENGTH     (240)
#define DIFF_BREAK_LENGTH    (180)

/**
 * Struct holding the information for a break that a teller will have
 * [unsigned int] num      - Number of breaks taken
 * [unsigned int] total    - Total amount of time across all breaks taken 
 * [unsigned int] average  - Average amount of time taken per break
 * [unsigned int] shortest - Shortest amount of time taken for a break
 * [unsigned int] longest  - Longest amount of time taken for a break
 * */
typedef struct Break_S
{
    // Metrics for breaks for a teller
    unsigned int num; 
    unsigned int total;
    unsigned int shortest;
    unsigned int longest;

} BreakS;

void init_breaks(BreakS* break_info);
void update_breaks_metrics(BreakS* break_info, uint32_t break_length);
unsigned int generate_break_length(unsigned int random_time);
unsigned int generate_time_until_break(unsigned int random_time);
#endif
