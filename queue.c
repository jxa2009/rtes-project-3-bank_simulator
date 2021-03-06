#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "customers.h"


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
    QueuePtr->max_depth = 0;
    QueuePtr->max_wait_time = 0;

    //Active information init
    QueuePtr->size = 0;
    QueuePtr->current_wait_time = generate_time_for_new_cust();;
    QueuePtr->front_node = NULL;
    QueuePtr->back_node = NULL;
}

/**
 * Adds an item to the end of the queue 
 * [QueueS*] QueuePtr - Pointer to a queue to add item to
 * [QueueS*] NodePtr  - Pointer to a node to add the back of the queue (back of the line)
 *  Returns: NULL
 * */
void Enqueue(QueueS* QueuePtr, Queue_NodeS* NodePtr)
{
    if (QueuePtr->size == 0)
    {
        NodePtr->next_node = NULL;
        QueuePtr->back_node = NodePtr;
        QueuePtr->front_node = NodePtr;
    }
    else
    {
        NodePtr->next_node = NULL;
        QueuePtr->back_node->next_node = NodePtr;
        
    }
    QueuePtr->size++;   
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
    if (QueuePtr->size > 0)
    {
        Queue_NodeS* old_head = QueuePtr->front_node;
        CustomerS* customer = old_head->customer;
        if(QueuePtr->size == 1)
        {
            QueuePtr->front_node = NULL;
            QueuePtr->back_node = NULL;
        }
        else if (QueuePtr->size > 1)
        {
            QueuePtr->front_node = QueuePtr->front_node->next_node;
        }
        QueuePtr->size--;
        free(old_head);
        return customer;
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
    Queue_NodeS* new_node = malloc(sizeof(Queue_NodeS));

    // Create new customer to be added
    CustomerS* new_customer = Generate_Customer();
    new_node->customer = new_customer;
    Enqueue(&CustomerQueue, new_node);
    CustomerQueue.size++;
    CustomerQueue.current_wait_time += new_customer->interaction_time;
    if (CustomerQueue.size > CustomerQueue.max_depth)
    {
        CustomerQueue.max_depth = CustomerQueue.size;
    }

    if (CustomerQueue.current_wait_time > CustomerQueue.max_wait_time)
    {
        CustomerQueue.max_wait_time = CustomerQueue.current_wait_time;
    }

}

void Queue_Task(void* vpParameter)
{
    if(master_timer >= CustomerQueue.wait_time )
    {

    // Lock queue
    unsigned int time_for_new_cust = generate_time_for_new_cust();
    CustomerQueue.wait_time = time_for_new_cust + master_timer;
    Add_Customer();
    // Unlock queue
    }
    
}

/**
 * Generates a time between 1 minute and 4 minutes
 * Inputs: None
 * Outputs: The time generated
 * */
static unsigned int generate_time_for_new_cust(void)
{
    unsigned int random_time = rng function
    return (random_time % DIFF_INTERACTION_TIME) + MIN_ENTER_QUEUE_TIME;
}
