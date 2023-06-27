#include"information_management.h"

void PrintStudentInf(STU data)
{
    printf("%s %s %.1f %.1f %.1f %.1f\n",data.id,data.name,data.score[0],data.score[1],data.score[2],data.score[3]);
}
void PrintClassInf(STU * classdata,int num)
{
    int i;
    STU  data;
    for(i=0;i<num;i++)
    {
        data =*(classdata+i);
        printf("%s %s %.1f %.1f %.1f %.1f \n",data.id,data.name,data.score[0],data.score[1],data.score[2],data.score[3]);
    }
}