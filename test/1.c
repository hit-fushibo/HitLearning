#include<stdio.h>

int main (int argc,char *argv[])
{
    char *p;
    char a[5]={"abc"};
    p=a+3;
    if(p==NULL)
    {
        printf("1");
    }
    else
    {
        printf("2");
    }
    return 0;
}