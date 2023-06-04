#include<stdio.h>

long fib(long i);

int main (void)
{
    long i,j;
    i=fib(100);
    j=fib(101);
    double g;
    g=(double)i/(double)j;
    printf("%f",g);
    return 0;
}

long fib(long i)
{
    if(i==1)
    {
        return 1;
    }
    else if(i==2)
    {
        return 1;
    }
    else
    {
        return fib(i-1)+fib(i-2);
    }
}