#ifndef DEFINATION_H
#define DEFINATION_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VERTES 100


//邻接矩阵
typedef struct Adjacency_matrix
{
    int Vertex_num;
    int Matrix[MAX_VERTES][MAX_VERTES];
}Am;


#endif