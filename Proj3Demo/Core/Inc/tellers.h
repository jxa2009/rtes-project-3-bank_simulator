#ifndef TELLERS_H
#define TELLERS_H

#include "breaks.h"
#define NUM_TELLERS (3)
#define TELLER_1 (1)
#define TELLER_2 (2)
#define TELLER_3 (3)
#define MAX_STATUS_STRING (10)
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
    unsigned int max_transaction_time;
    unsigned int max_wait_time;

    // Active Information    
    uint16_t teller_id;
    uint32_t busy_time;
    BreakS* break_info; 
    StatusE status;
    unsigned int time_finished_task; // will be the master timer of when they finished serving customer
    // will be used to calculate how long they've been waiting

    unsigned int time_until_break;
} TellerS;

typedef struct TellerStatus_S
{
    StatusE status;
    char  status_string[MAX_STATUS_STRING];
} TellerStatusS;

static const TellerStatusS Teller_Statuses[] =
{
    {busy, "busy"},
    {idle, "idle"},
    {on_break, "on break"}
};

static int NUM_STATUSES = sizeof(Teller_Statuses) / sizeof(TellerStatusS);
void init_teller(TellerS* teller, uint16_t id, unsigned int random_time);
//void Teller_Task(void *vpParameter); probably to be removed


#endif
