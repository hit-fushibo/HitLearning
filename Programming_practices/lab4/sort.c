#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void MergeSort(STU *a,int i,int j,int subjects)
{
    int k,l,h,v;
    if(j<=i)
    {
      return;
    }
    k = (j+i)/2;
    MergeSort(a, i,k,subjects);
    MergeSort(a, k+1,j,subjects);
    STU * temp = (STU *)malloc((j-i+1)*sizeof(STU));
    v=0;
    l=i;
    h=k+1;
    while(l<=k && h<=j)
    {
        
        if(cmp((a+l)->score[subjects], (a+h)->score[subjects])<=0)
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
        memcpy(temp+v, a+l, (k-l+1)*sizeof(STU));
    }
    if(h<=j)
    {
        memcpy(temp+v, a+h, (j-h+1)*sizeof(STU));
    }
    memcpy(a+i, temp, (j-i+1)*sizeof(STU));
    free(temp);
}

void swap(STU *a,int i,int j)
{
    STU temp;
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

int cmp(float i,float j)
{
    if(i>j)
    {
        return 1;
    }
    else if (i==j)
    {
        return 0;
    }
    else
    {
        return -1;
    }
    
}