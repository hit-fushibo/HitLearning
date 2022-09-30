#include<stdlib.h>
#include<stdio.h>
#include"sort.h"

void SelectSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *))
{
    int i,j;
    for(i=0;i<length-1;i++)
    {
        for(j=i+1;j<length;j++)
        {
            if(cmp(a+i,a+j)>0)
            {
                swap(a,i,j);
            }
        }
    }
}