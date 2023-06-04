#include<stdlib.h>
#include<stdio.h>
#include"sort.h"

void BubbleSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *))
{
    int i,j;
    for(i=0;i<length-1;i++)
    {
        for(j=0;j<length-1-i;j++)
        {
            if(cmp(a+j,a+j+1)>0)
            swap(a,j,j+1);
        }
    }
}