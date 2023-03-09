#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void InsertSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *))
{
    for(int i=1; i<length;i++)
    {
       ElemType cur = a[i];
       int j= i-1;
       //while(j>=0 && A[j]>cur)
       while(j>=0 && cmp(a+j, &cur)>0)
       {
           a[j+1] = a[j];
           j--;
       }
       a[j+1] = cur;
    }
}