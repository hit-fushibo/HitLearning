#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void QuickSort(ElemType *a,int i,int j,int (*cmp)(ElemType *,ElemType *))
{
    if(j<=i){return;}
    //int pos = i+rand()%(j-i+1);
    //swap(a,i,pos);
    int k = Partition(a,i,j,cmp);
    QuickSort(a,i,k-1,cmp);
    QuickSort(a,k+1,j,cmp);
}

int Partition(ElemType *a, int i, int j,int (*cmp)(ElemType *, ElemType *))
{
    int low,high;
    low = i+1;
    high =j;
    while(low <= high )
    {
        while(low <=j && cmp(a+low, a+i)<=0)
        {
            low++;
        }
        while(high > i && cmp(a+high, a+i)>=0)
        {
            high--;
        }
        if(low<high)
        {
            swap(a, low, high);
        }
    }
    swap(a, i, high);
    return high;
}