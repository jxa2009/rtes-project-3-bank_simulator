#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tellers.h"
#include "my_queue.h"
#include "customers.h"

//static TellerS teller;
//static int master_timer;

/**
 * Initialization of a teller struct
 * [TellerS*] teller - pointer to a teller
 * [uint16_t] id     - Id number to initialize the teller with
 * */
void init_teller(TellerS* teller,uint16_t id, unsigned int random_time)
{
    teller->total_served = 0;
    teller->total_time_served = 0;
    teller->total_time_waiting = 0;
    teller->teller_id = id;
    teller->busy_time = 0;
    teller->break_info = (BreakS*) pvPortMalloc(sizeof(BreakS));
    teller->status = idle;
    teller->time_until_break = generate_time_until_break(random_time);
    teller->max_transaction_time = 0;
    teller->max_wait_time = 0;
    teller->time_finished_task = 0;
}


