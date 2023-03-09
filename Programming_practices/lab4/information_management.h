#ifndef _INFORMATION_MANAGEMENT_H_
#define _INFORMATION_MANAGEMENT_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


typedef struct STU
{
    char  id[20];
    char  name[20];
    float score[5];
}STU;


void PrintStudentInf(STU data);
void PrintClassInf(STU * classdata,int num);

void StudentData(STU * data,int size);
void SubjectData(STU * data,int size);
void DataRank(STU * data,int size);

int NameSearch(STU *data,char * name,int size);
int IdSearch(STU *data,char *id,int size);

void ControlInfPrint(void);
int ControNumGet(void);

#endif