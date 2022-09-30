#ifndef _SORT_H_
#define _SORT_H_

#include"information_management.h"



//a：要排序的数组，length：数组长度
void MergeSort(STU *a,int i,int j,int subjects);
void swap(STU *a,int i,int j);
int cmp(float i,float j);

void RandData(STU *pa, int num);
void RandName(char *a);
void RandId(char *a);
#endif