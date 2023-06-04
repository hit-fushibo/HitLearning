#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void build_max_heap(ElemType A[], int n, int (*cmp)(ElemType *, ElemType *));
void max_heapify(ElemType A[], int nSize,int i, int (*cmp)(ElemType *, ElemType *));

void HeapSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    int nSize = n;
    build_max_heap(A,nSize, cmp);
    for(int i=n-1; i>0; i--)
    {
        Swap(A,0,i);
        nSize--;
        max_heapify(A, nSize, 0,cmp);
    }
}


void build_max_heap(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i= n/2-1; i>=0;i--)
    {
        max_heapify(A, n, i, cmp);
    }
}


void max_heapify(ElemType *A, int nSize,int i, int (*cmp)(ElemType *, ElemType *))
{
    int l = 2*i+1;
    int r = 2*i+2;
    if(l>=nSize)
    {
        return;
    }
    int Max = i;
    //if(A[i]<A[l])
    if(cmp(A+i, A+l)<0)
    {
        Max = l;
    }
    //if(r<nSize && A[r]>A[Max])
    if(r<nSize && cmp(A+r, A+Max)>0)
    {
        Max = r;
    }
    if(i==Max)
    {
        return;
    }
    Swap(A,i, Max);
    max_heapify(A, nSize, Max, cmp);
}
