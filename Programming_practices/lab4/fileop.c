#include"fileop.h"

void input_data(int location, STU *data, char *input)
{
    int i = 0;
    char *temp = input;
    char **endstr;
    char tempdata[30] = {0};
    temp += read_data(temp, tempdata);
    strcpy(data[location].id,tempdata);
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    strcpy(data[location].name, tempdata);
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[0] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[1] = 0;
        data[location].score[2] = 0;
        data[location].score[3] = 0;
        data[location].score[4]=data[location].score[0]+data[location].score[1]+data[location].score[2]+data[location].score[3];
        return ;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[1] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[2] = 0;
        data[location].score[3] = 0;
        data[location].score[4]=data[location].score[0]+data[location].score[1]+data[location].score[2]+data[location].score[3];
        return ;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[2] = strtod(tempdata, endstr);
    if (*temp == '\0' || *temp == '\n')
    {
        data[location].score[3] = 0;
        data[location].score[4]=data[location].score[0]+data[location].score[1]+data[location].score[2]+data[location].score[3];
        return ;
    }
    temp += skip_space(temp);
    temp += read_data(temp, tempdata);
    data[location].score[3] = strtod(tempdata, endstr);
    data[location].score[4]=data[location].score[0]+data[location].score[1]+data[location].score[2]+data[location].score[3];
    return ;
}

int txtread(FILE * fp,STU * data,int size)
{
    char Buffer[101]={0};
    size = 0;
    if(fp==NULL)
    {
        return -1;
    }
    else
    {
        while(fgets(Buffer,100,fp) != NULL)
        {
            input_data(size,data,Buffer);
            size++;
        }
    }
    return size;
}

void txtprint(FILE * fp,STU *data,int size)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        fprintf(fp,"%s %s %.1f %.1f %.1f %.1f\n",(data+i)->id,(data+i)->name,(data+i)->score[0],(data+i)->score[1],(data+i)->score[2],(data+i)->score[3]);
    }
}

int read_data(char *a, char *data) 
{

    int i = 0; 
    for (i = 0; *a != '\0' && *a != '\n' && *a != ' ' && i < 30; i++, a++)
    {
        data[i] = *a;
    }
    data[i]='\0';
    return i;
}

int skip_space(char *a) 
{
    int i = 0;
    for (; *a == ' '; a++, i++)
        ;
    return i;
}

int txtsize(FILE * fp)
{
    
    char Buffer[101]={0};
    int size=0;
    
    if(fp==NULL)
    {
        return -1;
    }
    else
    {
        while(fgets(Buffer,100,fp) != NULL)
        {
            size++;
        }
    }
    return size;
}