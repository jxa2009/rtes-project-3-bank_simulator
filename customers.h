#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Minimum interaction time in terms of seconds
#define MIN_INTERACTION_TIME (30)
// Maximum interaction time in terms of seconds
#define MAX_INTERACTION_TIME (480)
// Difference between the intaction times
#define DIFF_INTERACTION_TIME ((MAX_INTERACTION_TIME)-(MIN_INTERACTION_TIME))
/**
 * Struct to represent a single customer
 * 
 * */
typedef struct Customer_S
{
    unsigned int wait_time; // probably to be removed
    unsigned int interaction_time;
} CustomerS;


CustomerS* Generate_Customer();
static unsigned int Generate_Interaction_Time(void);
void DestroyCustomer(CustomerS* Customer);

#endif