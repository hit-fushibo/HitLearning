#include<stdio.h>

int sum(int a[],unsigned len);

int main (void)
{
    int a[10];
    for(int i=0;i<10;i++)
    {
        a[i]=i;
    }
    int sum_of_a;
    sum_of_a=sum(a,0);
    return 0;
}

int sum(int a[],unsigned len)
{
    int i,sum=0;
    for(i=0;i<=len-1;i++)
    {
        sum+=a[i];
    }
    return sum;
}