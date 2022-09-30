#ifndef _SORT_H_
#define _SORT_H_

#define INT 0
#define FLOAT 1
#define DOUBLE 2
#define STUDENT 3

typedef struct STU
{
    char  id[20];
    char  name[20];
    float score[5];
    float total;
}STU;

typedef STU  ElemType;

void outputElemType(int i);
//a：要排序的数组，length：数组长度，cmp：函数指针
void SelectSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *));
void BubbleSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *));
void InsertSort(ElemType *a,int length,int (*cmp)(ElemType *,ElemType *));
void MergeSort(ElemType *a,int i,int j,int (*cmp)(ElemType *,ElemType *));
void QuickSort(ElemType *a, int i, int j, int (*cmp)(ElemType *, ElemType *));
int Partition(ElemType *a, int i, int j,int (*cmp)(ElemType *, ElemType *));

void swap(ElemType *a,int i,int j);
#endif