#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void outputElemType(int i)
{
    if(i == INT)
    {
        printf("datatype is int \n");
    }
    else if(i == FLOAT)
    {
        printf("datatype is float \n");
    }
    else if(i == DOUBLE)
    {
        printf("datatype is double \n");
    }
    else if(i == STUDENT)
    {
        printf("datatype is student \n");
    }
}

void swap(ElemType *a,int i,int j)
{
    ElemType temp;
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}