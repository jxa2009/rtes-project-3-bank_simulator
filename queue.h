#ifndef QUEUE_H
#define QUEUE_H

#include "customers.h"

/**
 * Struct to represent a single queue node
 * Queue will be singly linked
 * [CustomerS*] Customer - Pointer to customer struct which will hold the information for each individual customer
 * [Queue_NodeS*] Next_Node - Pointer to the next node, the next node will be served before the current node
 * */
typedef struct Queue_Node_S
{
    CustomerS* Customer;
    struct Queue_Node_S* Next_Node;
} Queue_NodeS;

/**
 * Struct to hold information regarding a queue
 * [unsigned int] size - Amount of items in the queue
 * [Queue_NodeS*] Front_Node - Pointer to a queue node that represents the front of the queue (last in)
 * [Queue_NodeS*] Bacl_Node - Pointer to a queue node that represents the front of the queue (last in)
 * */
typedef struct Queue_S
{
    // Metrics
    unsigned int Max_Depth;
    unsigned int Max_Wait_Time;
    
    // Active information
    unsigned int Size;
    unsigned int Current_Wait_Time;
    Queue_NodeS* Front_Node;
    Queue_NodeS* Back_Node;
} QueueS;

void InitQueue(QueueS* QueuePtr);
void Enqueue(QueueS* QueuePtr, Queue_NodeS* NodePtr);
Queue_NodeS* Dequeue(QueueS* QueuePtr);
void DestroyQueue(QueueS* QueuePtr);


#endif