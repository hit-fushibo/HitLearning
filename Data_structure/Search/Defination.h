#ifndef DEFINATION_H
#define DEFINATION_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define UNDIFINE __INT32_MAX__

typedef struct tree
{
    int data;
    struct tree* lchild;
    struct tree* rchild;
}T;




#endif 