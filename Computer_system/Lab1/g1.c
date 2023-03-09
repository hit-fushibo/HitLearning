#include<stdio.h>

int main (void)
{
    long fib[101];
    fib[0]=1;fib[1]=1;
    for(int i=2;i<101;i++)
    {
        fib[i]=fib[i-1]+fib[i-2];
    }
    double g;
    g=(double)fib[99]/(double)fib[100];
    printf("%f",g);
    return 0;
}