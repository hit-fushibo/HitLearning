#ifndef DEFINITION_H
#define DEFINITION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLENGTH 100

typedef struct bintree
{
    int data;
    struct bintree *lchild;
    struct bintree *rchild;
} BTreeNode;

typedef struct BtStack
{
    BTreeNode data[MAXLENGTH];
    int top;
} BtStack;


#endif