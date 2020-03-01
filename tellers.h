#ifndef TELLERS_H
#define TELLERS_H

#include "breaks.h"

typedef enum Status_E
{
    Busy,
    Idle,
    Break,
} StatusE;
/**
 * Struct for an individual teller
 * [unsigned int] Total_Served       - Amount of customers served by teller
 * [unsigned int] Total_Time_Served  - Amount of time a teller has spent serving a customer
 * [unsigned int] Total_Time_Waiting - Amount of time teller spends waiting to serve a customer
 * 
 * [BreakS*] Break                   - Pointer to a break for a teller
 * [StatusE] Status                  - Enum to represent the current status of the teller
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
    StatusE Status;
    unsigned int Time_Until_Break;
} TellerS;


#endif