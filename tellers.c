#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tellers.h"
#include "queue.h"
#include "customers.h"

static TellerS teller;
static int master_timer;
/**
 * Initialization of a teller struct
 * [TellerS*] teller - pointer to a teller
 * [uint16_t] id     - Id number to initialize the teller with
 * */
void Init_Teller(TellerS* teller,uint16_t id)
{
    teller->total_served = 0;
    teller->total_time_served = 0;
    teller->total_time_waiting = 0;
    teller->teller_id = id;
    teller->busy_time = 0;
    teller->break_info = (BreakS*) malloc(sizeof(BreakS));
    teller->status = idle;
    teller->time_until_break = 0;
}
void Teller_Task(void *vpParameter)
{
    // probably gonna go and put this in a while(1) loop
    
    if(teller.status == idle)
    {
        // If the teller can, they should go on break
        // The time until break is the time at which the master_timer will be at when they can take a break
        if(teller.time_until_break >= master_timer)
        {
            
            unsigned int init_time_waiting= generate_break_length();
            unsigned int time_waiting = init_time_waiting + master_timer;

            teller.busy_time = time_waiting;
            teller.total_time_waiting = init_time_waiting;
            teller.break_info->num++;
            update_breaks_metrics(&teller.break_info, time_waiting);
            teller.status = on_break;
            teller.time_until_break = master_timer + generate_time_until_break();
        }
        // Lock the queue info

        if(CustomerQueue.size > 0)
        {
            CustomerS* customer = Dequeue(&CustomerQueue);
            teller.total_served++;
            teller.total_time_served += customer->interaction_time;
            teller.busy_time = master_timer + customer->interaction_time;
            teller.status = busy;
            teller.total_time_waiting = master_timer - teller.time_finished_task;
            teller.time_finished_task = 0;

            // Fix the current wait time for when new customers are being added
            CustomerQueue.current_wait_time -= customer->interaction_time;
            free(customer);
        }
        // Unlock queue
    }
    else if (teller.status = busy)
    {
        if(master_timer >= teller.busy_time)
        {
            teller.status = idle;
            teller.time_finished_task = master_timer;
        }
    }
    else // if teller.status == on_break
    {
        if (master_timer >= teller.busy_time)
        {
            teller.status = idle;
            teller.time_finished_task = master_timer;
        }
    }
    
}

static unsigned int generate_time_until_break(void);