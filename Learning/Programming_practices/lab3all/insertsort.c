#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
void InsertSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=1; i<n;i++)
    {
       ElemType cur = A[i];
       int j= i-1;
       //while(j>=0 && A[j]>cur)
       while(j>=0 && cmp(A+j, &cur)>0)
       {
           A[j+1] = A[j];
           j--;
       }
       A[j+1] = cur;
    }
}
