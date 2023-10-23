//  Created by Jatin Sahijwani on 14/05/22.
#include "tm_avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "tm_sll.h"
#ifndef __tm_avl_tree__c
#define __tm_avl_tree__c 123
AVLTree * createAVLTree(bool *success,int (*predicate)(void *,void *))
{
    AVLTree *avlTree;
    if(success) *success=false;
    avlTree=(AVLTree *)malloc(sizeof(AVLTree));
    if(avlTree==NULL || predicate==NULL) return NULL;
    avlTree->start=NULL;
    avlTree->size=0;
    avlTree->predicate=predicate;
    if(success) *success=true;
    return avlTree;
}
int getSizeOfAVLTree(AVLTree *avlTree)
{
    if(avlTree==NULL) return 0;
    if(avlTree->start==NULL) return 0;
    return avlTree->size;
}
void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
    Stack *stack;
    AVLTreeNode *j,*t;
    int weight,succ;
    if(success) *success=false;
    if(avlTree==NULL) return;
    if(avlTree->start==NULL)
    {
        t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
        t->ptr=ptr;
        t->left=NULL;
        t->right=NULL;
        avlTree->start=t;
        avlTree->size++;
        if(success) *success=true;
        return;
    }
    stack=createStack(&succ);
    if(succ==false) return;
    j=avlTree->start;
    while(1)
    {
        weight=avlTree->predicate(ptr,j->ptr);
        if(weight==0) return;
        pushOnStack(stack, j, &succ);
        if (succ==false)
        {
            destroyStack(stack);
            return;
        }
        if(weight<0)
        {
            if(j->left==NULL)
            {
                t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
                if(t==NULL) return;
                t->ptr=ptr;
                t->left=NULL;
                t->right=NULL;
                j->left=t;
                break;
            }
            else j=j->left;
        }
        else
        {
             if(j->right==NULL)
             {
                 t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
                 if(t==NULL) return;
                 t->ptr=ptr;
                 t->left=NULL;
                 t->right=NULL;
                 j->right=t;
                 break;
             }
             else j=j->right;
        }
    }
    if(success) *success=true;
    avlTree->size++;
    balanceAVLTree(stack);
    destroyStack(stack);
    return;
}
AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success)
{
    int succ;
    AVLTreeNode *t;
    AVLTreeInOrderIterator avlTreeInOrderIterator;
    avlTreeInOrderIterator.node=NULL;
    avlTreeInOrderIterator.stack=NULL;
    if(success) *success=false;
    if(avlTree==NULL) return avlTreeInOrderIterator;
    if(avlTree->start==NULL)
    {
        if(success) *success=true;
        return avlTreeInOrderIterator;
    }
    avlTreeInOrderIterator.stack=createStack(&succ);
    if(succ==false) return avlTreeInOrderIterator;
    t=avlTree->start;
    while(t!=NULL)
    {
        pushOnStack(avlTreeInOrderIterator.stack, (void *)t, &succ);
        if(succ==false)
        {
            destroyStack(avlTreeInOrderIterator.stack);
            avlTreeInOrderIterator.stack=NULL;
            return avlTreeInOrderIterator;
        }
        t=t->left;
    }
    avlTreeInOrderIterator.node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator.stack, &succ);
    if(success) *success=true;
    return avlTreeInOrderIterator;
}
bool hasNextElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
    if(avlTreeInOrderIterator==NULL) return false;
    if(avlTreeInOrderIterator->node==NULL) return false;
    return true;
}
void * getNextElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
{
    AVLTreeNode *j,*t;
    int succ;
    if(success) *success=false;
    if(avlTreeInOrderIterator==NULL) return NULL;
    if(avlTreeInOrderIterator->node==NULL) return NULL;
    j=avlTreeInOrderIterator->node;
    t=j->right;
    while(t!=NULL)
    {
        pushOnStack(avlTreeInOrderIterator->stack, (void *)t, &succ);
        if(succ==false)
        {
            destroyStack(avlTreeInOrderIterator->stack);
            avlTreeInOrderIterator->stack=NULL;
            avlTreeInOrderIterator->node=NULL;
            if(success) *success=true;
            return j->ptr;
        }
        t=t->left;
    }
    if(isStackEmpty(avlTreeInOrderIterator->stack))
    {
        destroyStack(avlTreeInOrderIterator->stack);
        avlTreeInOrderIterator->stack=NULL;
        avlTreeInOrderIterator->node=NULL;
    }
    else
    {
        avlTreeInOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator->stack, &succ);
    }
    if(success) *success=true;
    return j->ptr;
}
void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
    int weight;
    AVLTreeNode *t;
    if(success) *success=false;
    if(avlTree==NULL || avlTree->start==NULL) return NULL;
    t=avlTree->start;
    while(t!=NULL)
    {
        weight=avlTree->predicate(ptr,t->ptr);
        if(weight==0)
        {
            if(success) *success=true;
            return t->ptr;
        }
        if(weight<0) t=t->left;
        if(weight>0) t=t->right;
    }
    return NULL;
}
void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
    AVLTreeNode *t = NULL,*j = NULL,*e = NULL,*f = NULL;
    AVLTreeNode **p2p;
    void *foundPtr;
    int weight;
    if(success) *success=false;
    if(avlTree==NULL || avlTree->start==NULL) return NULL;
    t=avlTree->start;
    while(t!=NULL)
    {
        weight=avlTree->predicate(ptr,t->ptr);
        if(weight==0) break;
        j=t;
        if(weight<0) t=t->left; else t=t->right;
    }
    if(t==NULL) return NULL;
    foundPtr=t->ptr;
    if(t==avlTree->start) p2p=&(avlTree->start);
    else if(j->left==t) p2p=&(j->left);
    else p2p=&(j->right);
    if(t->left==t->right) *p2p=NULL;
    else
    {
        if(t->right!=NULL)
        {
            for(e=t->right;e->left!=NULL;e=e->left) f=e;
            if(e==t->right) e->left=t->left;
            else
            {
                f->left=e->right;
                e->left=t->left;
                e->right=t->right;
            }
            *p2p=e;
        }
        else
        {
            for(e=t->left;e->right!=NULL;e=e->right) f=e;
            if(e==t->left) e->right=t->right;
            else
            {
                f->right=e->left;
                e->left=t->left;
                e->right=t->right;
            }
            *p2p=e;
        }
    }
    free(t);
    avlTree->size--;
    if(success) *success=true;
    return foundPtr;
}
int getHeightOfAVLTree(AVLTreeNode *root)
{
    int leftTreeHeight,rightTreeHeight;
    if(root==NULL) return 0;
    leftTreeHeight=getHeightOfAVLTree(root->left);
    rightTreeHeight=getHeightOfAVLTree(root->right);
    return (leftTreeHeight>rightTreeHeight)?leftTreeHeight+1:rightTreeHeight+1;
}

#endif
