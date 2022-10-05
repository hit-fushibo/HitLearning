#include<stdio.h>

int main (int argc,char *argv[])
{
    int a[16]={10,2,14,7,8,12,15,11,0,4,1,13,3,9,6,5};
    int i=0,j,k=0;
    for(i=0;i<16;i++)
    {
        k+=a[i];
    }
    printf("%d",k);
    return 0;
}