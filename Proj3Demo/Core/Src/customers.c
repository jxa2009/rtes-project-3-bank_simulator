#include "customers.h"

/**
 * Allocates memory for customer and generates random interactino time for them
 * Inputs: None
 * Returns: Pointer to new customer
 * */
CustomerS* Generate_Customer(unsigned int random_time)
{
    CustomerS* new_customer = (CustomerS*) pvPortMalloc(sizeof(CustomerS));
    new_customer->interaction_time = generate_interaction_time(random_time);
    return new_customer;
}

/**
 * Randomly generates an interaction time for customers (between 30 seconds and 4 minutes)
 * Inputs: None
 * Returns: Random time
 * */
static unsigned int generate_interaction_time(unsigned int random_time)
{
    return (random_time % DIFF_INTERACTION_TIME) + MIN_INTERACTION_TIME;
}
