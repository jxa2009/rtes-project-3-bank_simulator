#include "customers.h"

/**
 * Allocates memory for customer and generates random interactino time for them
 * Inputs: None
 * Returns: Pointer to new customer
 * */
CustomerS* Generate_Customer(void)
{
    CustomerS* new_customer = (CustomerS*) malloc(sizeof(CustomerS));
    new_customer->interaction_time = Generate_Interaction_Time();
    return new_customer;
}

/**
 * Randomly generates an interaction time for customers (between 30 seconds and 4 minutes)
 * Inputs: None
 * Returns: Random time
 * */
static unsigned int Generate_Interaction_Time(void)
{
    unsigned int random_time = RNG FUNCTION FOR RANDOM TIME
    return (random_time % DIFF_INTERACTION_TIME) + MIN_INTERACTION_TIME;
}