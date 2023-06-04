#include"information_management.h"

int NameSearch(STU *data,char * name,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(strcmp(name,(data+i)->name)==0)
        {
            return i;
        }
    }
    return -1;
}
int IdSearch(STU *data,char *id,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(strcmp(id,(data+i)->id)==0)
        {
            return i;
        }
    }
    return -1;
}