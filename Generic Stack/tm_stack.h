//  Created by Jatin Sahijwani on 14/05/22.
#ifndef tm_stack_h
#define tm_stack_h 123
#include "tm_sll.h"
#include "tm_common.h"
typedef struct tm_stack
{
    SinglyLinkedList *singlyLinkedList;
}Stack;
Stack * createStack(bool *success);
void pushOnStack(Stack *stack,void *ptr,bool *success);
void * popFromStack(Stack *stack,bool *success);
int getSizeOfStack(Stack *stack);
void * elementAtTopOfStack(Stack *stack,bool *success);
bool isStackEmpty(Stack *stack);
void clearStack(Stack *stack);
void destroyStack(Stack *stack);
#endif /* tm_stack_h */
