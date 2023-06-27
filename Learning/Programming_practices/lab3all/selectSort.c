#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void SelectSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=0; i<n-1; i++)
    {
        int j=i;
        for(int k=i+1; k<n; k++)
        {
            //if(A[j]>A[k])     //only use for scalar array
            if(cmp(A+j, A+k)>0)
            {
                j=k;
            }
        }
        Swap(A,i,j);
    }
}
