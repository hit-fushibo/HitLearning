#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void BubbleSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-1-i; j++)
        {
            //if(A[j]>A[j+1])
            if(cmp(A+j, A+j+1)>0)
            {
                Swap(A, j, j+1);
            }
        }
    }
}
