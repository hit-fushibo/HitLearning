#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void Swap(ElemType *a, int i, int j)
{
    ElemType temp;
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}
