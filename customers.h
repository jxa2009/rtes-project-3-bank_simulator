#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Struct to represent a single customer
 * 
 * */
typedef struct Customer_S
{
    unsigned int Wait_Time;
    unsigned int Interaction_Time;
} CustomerS;


CustomerS* Generate_Customer();
void DestroyCustomer(CustomerS* Customer);

#endif