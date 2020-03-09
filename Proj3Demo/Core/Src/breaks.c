#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "breaks.h"

void init_breaks(BreakS* break_info)
{
    break_info->num = 0;
    break_info->total = 0;
    break_info->shortest = 99999; // Abitrarily long nubmer
    break_info->longest = 0;
}
/**
 * Updates the metrics of the break info for a teller
 * [BreakS*]  break_info   - Pointer to the break information to be changed
 * [uint32_t] break_length - Length of the break to be taken
 * */
void update_breaks_metrics(BreakS* break_info, uint32_t break_length)
{
    break_info->num++;
    break_info->total += break_length;
    if (break_length < break_info->shortest)
    {
        break_info->shortest = break_length;
    }
    else if ( break_length > break_info->longest)
    {
        break_info->longest = break_length;
    }

}

/**
 * Randomly generate a break length using RNG function of STM32 peripheral
 * Inputs: None
 * Returns: Randomly generated number between 1 minute and 4 minutes
 * */
unsigned int generate_break_length(unsigned int random_time)
{
    return ((random_time % DIFF_BREAK_LENGTH) + MIN_BREAK_LENGTH);
}
/**
 * Randomly generate when a teller can take their next breakusing RNG function of STM32 peripheral
 * Inputs: None
 * Returns: Randomly generated number between 30 minutes and 60 minutes
 * */
unsigned int generate_time_until_break(unsigned int random_time)
{

    return ((random_time % DIFF_TIME_UNTIL_BREAK) + MIN_TIME_UNTIL_BREAK);
}
