#include<stdio.h>

int main (int argc,char *argv[])
{
    printf("%s",argv[2]);
    FILE *fp=fopen(argv[2],"r");
    if(fp==NULL)
    {
        perror("error ");
        
    }
    return 0;
}