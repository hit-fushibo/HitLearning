#include"fileop.h"

void ReadInfix(FILE * fp,char * In)
{
    FILE * p=fp;
    int i=0;
    char a;
    for(;a!='#';)
    {
        a=fgetc(p);
    }
    fscanf(p,"%c",&a);
    for(;a!='#';)
    {
        In[i]=a;
        i++;
        fscanf(p,"%c",&a);
    }
    In[i]='\0';
    fclose(fp);
}