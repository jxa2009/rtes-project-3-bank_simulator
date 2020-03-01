#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "customers.h"

static QueueS CustomerQueue;

/**
 * GENERAL QUEUE FLOW
 * Is a thread -
 *      Every X time (randomly generated) - Will Perform Add_Customer
 *          Mallocs a node -
 *          Creates a customer
 *          Enqueues the customer
 * */


/**
 * Initializes the queue struct
 * Sets values to 0 or NULL
 * [QueueS*] QueuePtr - Pointer to a queue to initialize
 * Returns: NULL
 * */
void InitQueue(QueueS* QueuePtr)
{
    //Metric information init
    QueuePtr->Max_Depth = 0;
    QueuePtr->Max_Wait_Time = 0;

    //Active information init
    QueuePtr->Size = 0;
    QueuePtr->Current_Wait_Time = 0;
    QueuePtr->Front_Node = NULL;
    QueuePtr->Back_Node = NULL;
}

/**
 * Adds an item to the end of the queue 
 * [QueueS*] QueuePtr - Pointer to a queue to add item to
 * [QueueS*] NodePtr  - Pointer to a node to add the back of the queue (back of the line)
 *  Returns: NULL
 * */
void Enqueue(QueueS* QueuePtr, Queue_NodeS* NodePtr)
{
    if (QueuePtr->Size == 0)
    {
        NodePtr->Next_Node = NULL;
        QueuePtr->Back_Node = NodePtr;
        QueuePtr->Front_Node = NodePtr;
    }
    else
    {
        NodePtr->Next_Node = NULL;
        QueuePtr->Back_Node->Next_Node = NodePtr;
        
    }
    QueuePtr->Size++;   
}

/**
 * Removes the node from the front of the linked list
 * [QueueS* QueuePtr] - Pointer to a queue
 * Returns:
 *          Pointer to the removed data from node OR NULL if empty queue
 * */
CustomerS* Dequeue(QueueS* QueuePtr)
{
    // If the queue is a single item
    if (QueuePtr->Size > 0)
    {
        Queue_NodeS* Old_Head = QueuePtr->Front_Node;
        CustomerS* Customer = Old_Head->Customer;
        if(QueuePtr->Size == 1)
        {
            QueuePtr->Front_Node = NULL;
            QueuePtr->Back_Node = NULL;
        }
        else if (QueuePtr->Size > 1)
        {
            QueuePtr->Front_Node = QueuePtr->Front_Node->Next_Node;
        }
        QueuePtr->Size--;
        return Customer;
    }
    return NULL;
}

/**
 * Adds a customer to the static Queue object
 * Inputs: None
 * Returns: None
 * */
void Add_Customer()
{
    // Allocate Node
    Queue_NodeS* New_Node = malloc(sizeof(Queue_NodeS));

    // Create new customer to be added
    CustomerS* New_Customer = Generate_Customer();
    New_Node->Customer = New_Customer;

    Enqueue(&CustomerQueue, New_Node);
}
