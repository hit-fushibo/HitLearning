#include<stdio.h>
#include<stdlib.h>

int main (int argc,char *argv[])
{
    int *a=(int *)malloc(sizeof(int));
    free(a);
    if(a==NULL)
    {
        printf("1");
    }
    
    return 0;
}