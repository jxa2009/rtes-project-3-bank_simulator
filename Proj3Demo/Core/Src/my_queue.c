#include <stdio.h>
#include <stdlib.h>

#include "my_queue.h"
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
void init_queue(QueueS* QueuePtr,unsigned int random_time)
{
    //Metric information init
    QueuePtr->max_depth = 0;
    QueuePtr->max_wait_time = 0;

    //Active information init
    QueuePtr->size = 0;
    QueuePtr->current_wait_time = generate_time_for_new_cust(random_time);
    QueuePtr->front_node = NULL;
    QueuePtr->back_node = NULL;
}

/**
 * Adds an item to the end of the queue 
 * [QueueS*] QueuePtr - Pointer to a queue to add item to
 * [QueueS*] NodePtr  - Pointer to a node to add the back of the queue (back of the line)
 *  Returns: NULL
 * */
void enqueue(QueueS* QueuePtr, Queue_NodeS* NodePtr)
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
        QueuePtr->back_node = NodePtr;
    }
    QueuePtr->size++;   
}

/**
 * Removes the node from the front of the linked list
 * [QueueS* QueuePtr] - Pointer to a queue
 * Returns:
 *          Pointer to the removed data from node OR NULL if empty queue
 * */
CustomerS* dequeue(QueueS* QueuePtr)
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
void add_customer(QueueS* queue_ptr,unsigned int random_time)
{
    // Allocate Node
    Queue_NodeS* new_node = (Queue_NodeS*) malloc(sizeof(Queue_NodeS));

    // Create new customer to be added
    CustomerS* new_customer = Generate_Customer(random_time);
    new_node->customer = new_customer;
    enqueue(queue_ptr, new_node);

   queue_ptr->current_wait_time += new_customer->interaction_time;
    if (queue_ptr->size > queue_ptr->max_depth)
    {
        queue_ptr->max_depth = queue_ptr->size;
    }

    if (queue_ptr->current_wait_time > queue_ptr->max_wait_time)
    {
        queue_ptr->max_wait_time = queue_ptr->current_wait_time;
    }

}


/**
 * Generates a time between 1 minute and 4 minutes
 * Inputs: None
 * Outputs: The time generated
 * */
unsigned int generate_time_for_new_cust(unsigned int random_time)
{
    return (random_time % DIFF_INTERACTION_TIME) + MIN_ENTER_QUEUE_TIME;
}

/**
 * Determines if the given queue is empty
 * Inputs: None
 * Returns: 1 if queue is empty 0 if not
 * */
int is_empty(QueueS* queue_ptr)
{
    if(queue_ptr->size == 0)
    {
        return 1;
    }
    return 0;
}
