#ifndef TELLERS_H
#define TELLERS_H

#include "breaks.h"
/**
 * Struct for an individual teller
 * [unsigned int] Total_Served       - Amount of customers served by teller
 * [unsigned int] Total_Time_Served  - Amount of time a teller has spent serving a customer
 * [unsigned int] Total_Time_Waiting - Amount of time teller spends waiting to serve a customer
 * 
 * [BreakS*] Break                   - Pointer to a break for a teller
 * [unsigned char] Serving           - Boolean variable to represent if the teller is serving a custerom - 
 *                                     0 if not serving
 *                                     1 if serving
 * [unsigned int] Time_Until_Break   - Amount of time until the teller can take a break 
 * */
typedef struct Teller_S
{
    // Metrics
    unsigned int Total_Served;
    unsigned int Total_Time_Served;
    unsigned int Total_Time_Waiting;

    // Active Information    
    BreakS* Break; 
    unsigned char Serving;
    unsigned int Time_Until_Break;
} TellerS;


#endif