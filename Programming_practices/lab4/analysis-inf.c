#include"information_management.h"

void StudentData(STU * data,int size)
{
    int i;
    float average=0;
    for(i=0;i<size;i++)
    {
        average=(data+i)->score[4]/4;
        printf("%s %s %.1f %.1f\n",(data+i)->id,(data+i)->name,(data+i)->score[4],average);
    }
}

void SubjectData(STU * data,int size)
{
    float average[4]={0,0,0,0};
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<size;j++)
        {
            average[i]+=(data+j)->score[i];
        }
        average[i]/=size;
    }
    printf("average score of ics:%.1f\naverage score of PDP:%.1f\naverage score of DS:%.1f\naverage score of DL:%.1f\n",average[0],average[1],average[2],average[3]);
}

void DataRank(STU * data,int size)
{
    int r1=0,r2=0,r3=0,r4=0,r5=0;
    int i=0,j=0;
    for(i=0;i<4;i++)
    {
        char sub[4][4]={"ics","PDP","DS","DL"};
        r1=0;r2=0;r3=0;r4=0;r5=0;
        for(j=0;j<size;j++)
        {
            if(data[j].score[i]<=59)
            {
                r5++;
            }
            else if (data[j].score[i]<=69&&data[j].score[i]>59)
            {
                r4++;
            }
            else if (data[j].score[i]<=79&&data[j].score[i]>69)
            {
                r3++;
            }
            else if (data[j].score[i]<=89&&data[j].score[i]>79)
            {
                r2++;
            }
            else if (data[j].score[i]<=100&&data[j].score[i]>89)
            {
                r1++;
            }
        }
        printf("Data of %s:\n",sub[i]);
        printf("0-59:number:%d,percentage:%.1f %c \n",r5,100*((float)r5/(float)size),37);
        printf("60-69:number:%d,percentage:%.1f %c \n",r4,100*((float)r4/(float)size),37);
        printf("70-79:number:%d,percentage:%.1f %c \n",r3,100*((float)r3/(float)size),37);
        printf("80-89:number:%d,percentage:%.1f %c \n",r2,100*((float)r2/(float)size),37);
        printf("90-100:number:%d,percentage:%.1f %c \n",r1,100*((float)r1/(float)size),37);
    }
}