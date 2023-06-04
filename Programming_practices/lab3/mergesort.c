#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void MergeSort(ElemType *a,int i,int j,int (*cmp)(ElemType *,ElemType *))
{
    int k,l,h,v;
    if(j<=i)
    {
      return;
    }
    k = (j+i)/2;
    MergeSort(a, i,k, cmp);
    MergeSort(a, k+1,j,cmp);
    ElemType * temp = (ElemType *)malloc((j-i+1)*sizeof(ElemType));
    v=0;
    l=i;
    h=k+1;
    while(l<=k && h<=j)
    {
        //if(A[l]<=A[h])
        if(cmp(a+l, a+h)<=0)
        {
            temp[v]=a[l];
            l++;
            v++;
        }
        else
        {
            temp[v] = a[h];
            h++;
            v++;
        }
    }
    if(l<=k)
    {
        memcpy(temp+v, a+l, (k-l+1)*sizeof(ElemType));
    }
    if(h<=j)
    {
        memcpy(temp+v, a+h, (j-h+1)*sizeof(ElemType));
    }
    memcpy(a+i, temp, (j-i+1)*sizeof(ElemType));
    free(temp);
}