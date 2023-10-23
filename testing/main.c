#include "tm_avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
int myComparator(void *left,void *right)
{
    int *leftInt,*rightInt;
    leftInt=(int *)left;
    rightInt=(int *)right;
    return (*leftInt) - (*rightInt);
}
int main()
{
    AVLTreeInOrderIterator iterator;
    int *x;
    int num;
    AVLTree *tree;
    int success,ch;
    tree=createAVLTree(&success, myComparator);
    if(success==false)
    {
        printf("Unable To Create Tree, Low On Memory\n");
        return 0;
    }
    while(1)
    {
        printf("1. Insert Into AVL Tree\n");
        printf("2. Search From AVl Tree\n");
        printf("3. In Order Traversal\n");
        printf("4. Remove From AVl Tree\n");
        printf("5. EXIT\n");
        printf("Enter Your Choice : ");
        scanf("%d",&ch);
        fflush(stdin);
        if(ch==1)
        {
            printf("Enter Number To Be Inserted Into Tree : ");
            scanf("%d",&num);
            fflush(stdin);
            x=(int *)malloc(sizeof(int));
            *x=num;
            insertIntoAVLTree(tree, (void *)x, &success);
            if(success) printf("%d inserted into tree\n",*x);
            else printf("Unable To Insert\n");

        }
        if(ch==2)
        {
            printf("Enter Number To Be Searched From AVl Tree : ");
            scanf("%d",&num);
            fflush(stdin);
            x=getFromAVLTree(tree, &num, &success);
            if(success) printf("%d Found In AVL Tree\n",*x);
            else printf("Unable To Find %d In AVL Tree\n",num);
        }
        if(ch==3)
        {
            printf("In Order Iteration Starts\n");
            iterator=getAVLTreeInOrderIterator(tree, &success);
            if(success)
            {
                while(hasNextElementInAVLTree(&iterator))
                {
                    x=(int *)getNextElementFromAVLTree(&iterator, &success);
                    printf("%d\n",*x);
                }
            }
        }
        if(ch==4)
        {
            printf("Enter Number To Be Removed From AVl Tree : ");
            scanf("%d",&num);
            fflush(stdin);
            x=removeFromAVLTree(tree, &num, &success);
            if(success) printf("%d Removed From AVL Tree\n",*x);
            else printf("Unable To Remove %d In AVL Tree\n",num);

        }
        if(ch==5) break;
    }
    return 0;
}
