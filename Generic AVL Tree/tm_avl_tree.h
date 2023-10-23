//  Created by Jatin Sahijwani on 14/05/22.
#ifndef tm_avl_tree_h
#define tm_avl_tree_h
#include "tm_common.h"
#include "tm_stack.h"
typedef struct tm_avl_tree_node
{
    struct tm_avl_tree_node *left;
    struct tm_avl_tree_node *right;
    void *ptr;
}AVLTreeNode;
typedef struct tm_avl_tree
{
    struct tm_avl_tree_node *start;
    int (*predicate)(void *,void *);
    int size;
}AVLTree;
typedef struct tm_avl_tree_in_order_iterator
{
    AVLTreeNode *node;
    Stack *stack;
}AVLTreeInOrderIterator;
AVLTree * createAVLTree(bool *success,int (*predicate)(void *,void *));
void destroyAVLTree(AVLTree *avlTree);
int getSizeOfAVLTree(AVLTree *avlTree);
void clearAVLTree(AVLTree *avlTree);
void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success);
void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success);
void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success);
AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success);
bool hasNextElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator);
void * getNextElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success);
int getHeightOfAVLTree(AVLTreeNode *root);
#endif /* tm_avl_tree_h */
