#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void MergeSort(ElemType *A, int i, int j, int (*cmp)(ElemType *, ElemType *))
{
    int k,l,h,v;
    if(j<=i)
    {
      return;
    }
    k = (j+i)/2;
    MergeSort(A, i,k, cmp);
    MergeSort(A, k+1,j,cmp);
    ElemType * temp = (ElemType *)malloc((j-i+1)*sizeof(ElemType));
    v=0;
    l=i;
    h=k+1;
    while(l<=k && h<=j)
    {
        //if(A[l]<=A[h])
        if(cmp(A+l, A+h)<=0)
        {
            temp[v]=A[l];
            l++;
            v++;
        }
        else
        {
            temp[v] = A[h];
            h++;
            v++;
        }
    }
    if(l<=k)
    {
        memcpy(temp+v, A+l, (k-l+1)*sizeof(ElemType));
    }
    if(h<=j)
    {
        memcpy(temp+v, A+h, (j-h+1)*sizeof(ElemType));
    }
    memcpy(A+i, temp, (j-i+1)*sizeof(ElemType));
    free(temp);
}
