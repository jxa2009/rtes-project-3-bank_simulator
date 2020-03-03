#ifndef TELLERS_H
#define TELLERS_H

#include "breaks.h"

typedef enum Status_E
{
    busy,
    idle,
    on_break,
} StatusE;
/**
 * Struct for an individual teller
 * [unsigned int] total_served       - Amount of customers served by teller
 * [unsigned int] total_time_served  - Amount of time a teller has spent serving a customer
 * [unsigned int] total_time_waiting - Amount of time teller spends waiting to serve a customer
 * 
 * [uint16_t]     teller_id          - Id to identify which teller it corresponds to
 * [uint32_t]     busy_time          - A value which indicates how long it will be busy for
 * [BreakS*]      break_info         - Pointer to a break for a teller
 * [StatusE]      status             - Enum to represent the current status of the teller
 * [unsigned int] time_until_break   - Amount of time until the teller can take a break 
 * */
typedef struct Teller_S
{
    // Metrics
    unsigned int total_served;
    unsigned int total_time_served;
    unsigned int total_time_waiting;

    // Active Information    
    uint16_t teller_id;
    uint32_t busy_time;
    BreakS* break_info; 
    StatusE status;
    unsigned int time_finished_task; // will be the master timer of when they finished serving customer
    // will be used to calculate how long they've been waiting

    unsigned int time_until_break;
} TellerS;

void Init_Teller(TellerS* teller, uint16_t id);
//void Teller_Task(void *vpParameter); probably to be removed


#endif
