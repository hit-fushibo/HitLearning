#include<stdio.h>

int main (Void)
{
    FILE*fp=fopen("code_zip.txt","r");
    unsigned a;
    for(int i=0;i<9;i++)
    {
        fscanf(fp,"%u",&a);
        printf("%u ",a);
    }
    fclose(fp);
    return 0;
}