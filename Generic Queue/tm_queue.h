#ifndef tm_queue_h
#define tm_queue_h 123
#include "tm_sll.h"
#include "tm_common.h"
typedef struct tm_queue
{
    SinglyLinkedList *singlyLinkedList;
}Queue;
Queue * createQueue(bool *success);
void addToQueue(Queue *queue,void *ptr,bool *success);
void * removeFromQueue(Queue *queue,bool *success);
int getSizeOfQueue(Queue *queue);
void * elementAtFrontOfQueue(Queue *queue,bool *success);
bool isQueueEmpty(Queue *queue);
void clearQueue(Queue *queue);
void destroyQueue(Queue *queue);
#endif /* tm_queue_h */
