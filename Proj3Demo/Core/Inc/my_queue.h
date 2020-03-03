#ifndef QUEUE_H
#define QUEUE_H

#include "customers.h"

#define MIN_ENTER_QUEUE_TIME  (60)
#define MAX_ENTER_QUEUE_TIME  (240)
#define DIFF_ENTER_QUEUE_TIME (180)
//static QueueS CustomerQueue;

//static int master_timer;
/**
 * Struct to represent a single queue node
 * Queue will be singly linked
 * [CustomerS*] customer - Pointer to customer struct which will hold the information for each individual customer
 * [Queue_NodeS*] next_node - Pointer to the next node, the next node will be served before the current node
 * */
typedef struct Queue_Node_S
{
    CustomerS* customer;
    struct Queue_Node_S* next_node;
} Queue_NodeS;

/**
 * Struct to hold information regarding a queue
 * [unsigned int] size - Amount of items in the queue
 * [Queue_NodeS*] front_node - Pointer to a queue node that represents the front of the queue (last in)
 * [Queue_NodeS*] back_node - Pointer to a queue node that represents the front of the queue (last in)
 * */
typedef struct Queue_S
{
    // Metrics
    unsigned int max_depth;
    unsigned int max_wait_time;
    
    // Active information
    unsigned int size;
    unsigned int time_for_new_customer;
    unsigned int current_wait_time; // This is the wait time for a customer to be served when they join to get served
    Queue_NodeS* front_node;
    Queue_NodeS* back_node;
} QueueS;

void InitQueue(QueueS* QueuePtr,unsigned int random_time);
void Enqueue(QueueS* QueuePtr, Queue_NodeS* NodePtr);
CustomerS* Dequeue(QueueS* QueuePtr);
void DestroyQueue(QueueS* QueuePtr); // probably to be removed
void Add_Customer(QueueS* queue_ptr,unsigned int random_time);
unsigned int generate_time_for_new_cust(unsigned int random_time);

#endif
