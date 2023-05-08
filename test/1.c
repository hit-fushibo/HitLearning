#include<stdio.h>
#include<stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int i=0,flag=1,j=1;
    int * returndig = 0;
    for(i=0;i<digitsSize;i++)
    {
        if(digits[i]!=9)
        {
            flag=0;
            break;
        }
    }
    //printf("%d %d\n",flag,digitsSize);
    *returnSize=digitsSize+flag;
    returndig = (int *)malloc(sizeof(int)*(digitsSize+flag));
    if(flag==0)
    {
        for(int i = 0 ;i<digitsSize;i++)
        {
            returndig[i] = digits[i];
        }
        returndig[digitsSize-1]+=1;
        for(int i=digitsSize-1;i>0;i--)
        {
            printf("%d ",i);
            if(returndig[i]>=10)
            {
                returndig[i]%=10;
                returndig[i-1]+=1;
            }
        }
    }
    else
    {
        returndig[0]=1;
        for(int i=1;i<(digitsSize+flag);i++)
            returndig[i]=0;
    }
    return returndig;
}

int main (void)
{
    int test[]={1,2};
    int len=sizeof(test)/sizeof(int);
    int relen=0;
    int * p =plusOne(test,len,&relen);
    for (int i=0;i<relen;i++)
    {
        printf("%d ",p[i]);
    }

    return 0;
    
}