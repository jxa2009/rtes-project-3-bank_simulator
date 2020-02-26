#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

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
 * [QueueS*] NodePtr  - Pointer to a node to add the front of the queue (back of the line)
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

