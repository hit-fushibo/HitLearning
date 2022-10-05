#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sort.h"
#include "bubblesort.c"
#include "insertsort.c"
#include "mergesort.c"
#include "otherfunc.c"
#include "quicksort.c"
#include "selectsort.c"

//#define DeBug
//#define Ubuntu
#define Windows

int DataType = STUDENT;

//比较a与b的大小，a>b返回1，a=b返回0，a<b返回-1
int cmp(ElemType *a, ElemType *b);
//随机化数据数组
void RandData(ElemType *a, int num);
void RandName(char *a);
void RandId(char *a);
//输出数据
void OutputData(ElemType *a, int num);

int main(int argc, char *argv[])
{
    //计算运行时间
    size_t t1, t2;
    //生成数组的长度
    int size;
    //数据数组，orig原本数据，tosort传入排序算法的数据
    ElemType *orig, *tosort;

    //定义函数指针
    int (*cmpare)(ElemType *, ElemType *);
    cmpare = &cmp;

    //命令行参数检验
#ifdef DeBug
    int i;
    printf("%d\n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    printf("finish\n");
#endif

#ifdef Ubuntu
    if (argc < 2)
    {
        printf("error:too few parameters\n");
        exit(1);
    }
    sscanf(argv[1], "%d", &size);
    if (size <= 0)
    {
        printf("error:the parameters is not valid\n");
        exit(1);
    }
#endif

#ifdef Windows
    size = 10000000;
#endif

    //生成随机数组
    orig = (ElemType *)malloc(sizeof(ElemType) * size);
    tosort = (ElemType *)malloc(sizeof(ElemType) * size);
    RandData(orig, size);
    memcpy(tosort, orig, size * sizeof(ElemType));

    //说明数据类型
    outputElemType(DataType);
    printf("size is :%d\n", size);

    //选择排序
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    t1 = clock();
    SelectSort(tosort, size, cmpare);
    t2 = clock();
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    printf("time of SelectSort is:%f s\n", (t2 - t1) / ((double)CLOCKS_PER_SEC));

    //插入排序
    memcpy(tosort, orig, size * sizeof(ElemType));
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    t1 = clock();
    InsertSort(tosort, size, cmpare);
    t2 = clock();
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    printf("time of InsertSort is:%f s\n", (t2 - t1) / ((double)CLOCKS_PER_SEC));

    //冒泡排序
    memcpy(tosort, orig, size * sizeof(ElemType));
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    t1 = clock();
    BubbleSort(tosort, size, cmpare);
    t2 = clock();
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    printf("time of BubbleSort is:%f s\n", (t2 - t1) / ((double)CLOCKS_PER_SEC));

    //归并排序
    memcpy(tosort, orig, size * sizeof(ElemType));
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    t1 = clock();
    MergeSort(tosort, 0, size - 1, cmpare);
    t2 = clock();
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    printf("time of MergeSort is:%f s\n", (t2 - t1) / ((double)CLOCKS_PER_SEC));

    //快速排序
    memcpy(tosort, orig, size * sizeof(ElemType));
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    t1 = clock();
    QuickSort(tosort, 0, size - 1, cmpare);
    t2 = clock();
#ifdef DeBug
    OutputData(tosort, size);
    printf("finish\n");
#endif
    printf("time of QuickSort is:%f s\n", (t2 - t1) / ((double)CLOCKS_PER_SEC));

    //堆排序

    //for test
    // OutputData(tosort,size);
    // printf("1\n");
    return 0;
}

int cmp(ElemType *a, ElemType *b)
{
    if (DataType == INT)
    {
        if (*((int *)a) == *((int *)b))
            return 0;
        else if (*((int *)a) > *((int *)b))
            return 1;
        else
            return -1;
    }
    else if (DataType == FLOAT)
    {
        if (*((float *)a) == *((float *)b))
            return 0;
        else if (*((float *)a) > *((float *)b))
            return 1;
        else
            return -1;
    }
    else if (DataType == DOUBLE)
    {
        if (*((double *)a) == *((double *)b))
            return 0;
        else if (*((double *)a) > *((double *)b))
            return 1;
        else
            return -1;
    }
    else
    {
        STU *pa = (STU *)a;
        STU *pb = (STU *)b;
        if (pa->total == pb->total)
            return 0;
        else if (pa->total > pb->total)
            return 1;
        else
            return -1;
    }
}
void RandData(ElemType *a, int num)
{
    srand((int)time(NULL));
    int i = 0, j = 0;
    if (DataType == INT)
    {
        for (i = 0; i < num; i++)
        {
            *((int *)(a + i)) = rand() % (num);
        }
    }
    else if (DataType == FLOAT)
    {
        for (i = 0; i < num; i++)
        {
            *((float *)(a + i)) = rand() % (10 * num);
        }
    }
    else if (DataType == DOUBLE)
    {
        for (i = 0; i < num; i++)
        {
            *((double *)(a + i)) = rand() % (10 * num);
        }
    }
    else if (DataType == STUDENT)
    {
        for (i = 0; i < num; i++)
        {
            STU *pa = (STU *)(a + i);
            pa->total = 0;
            RandId((char *)(pa->id));
            RandName((char *)(pa->name));
            for (j = 0; j < 5; j++)
            {
                pa->score[j] = ((rand() % 10000) + 1) / ((double)100);
                pa->total += pa->score[j];
            }
        }
    }
}
void RandName(char *a)
{
    srand((int)time(NULL));
    char alphabet[2][26] = {{"qwertyuiopasdfghjklzxcvbnm"}, {"QWERTYUIOPASDFGHJKLZXCVBNM"}};
    int i, length;
    length = rand() % 20 + 1;
    a[0] = alphabet[1][rand() % 26];
    for (i = 1; i < length; i++)
    {
        a[i] = alphabet[0][rand() % 26];
    }
}
void RandId(char *a)
{
    srand((int)time(NULL));
    char number[10] = {"0123456789"};
    int i;
    for (i = 0; i < 20; i++)
    {
        a[i] = number[rand() % 10];
    }
    a[19] = '\0';
}
void OutputData(ElemType *a, int num)
{
    int i;
    if (DataType == INT)
    {
        for (i = 0; i < num; i++)
        {
            printf("%d ", *((int *)(a + i)));
        }
    }
    else if (DataType == FLOAT)
    {
        for (i = 0; i < num; i++)
        {
            printf("%f ", *((float *)(a + i)));
        }
    }
    else if (DataType == DOUBLE)
    {
        for (i = 0; i < num; i++)
        {
            printf("%f ", *((double *)(a + i)));
        }
    }
    else if (DataType == STUDENT)
    {
        for (i = 0; i < num; i++)
        {
            STU *pa = (STU *)a;
            printf("%s %s %f %f %f %f %f %f\n", pa->id, pa->name, pa->score[0], pa->score[1], pa->score[2], pa->score[3], pa->score[4], pa->total);
        }
    }
    printf("\n");
}