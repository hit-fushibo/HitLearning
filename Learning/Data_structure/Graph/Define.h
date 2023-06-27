#ifndef DEFINE_H
#define DEFINE_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX_VERTES 100

//树
typedef struct Tree
{
    int data;
    struct Tree* child;
    struct Tree* brother;
}T;

//邻接矩阵
typedef struct Adjacency_matrix
{
    int Vertex_num;
    int Matrix[MAX_VERTES][MAX_VERTES];
}Am;

//顶点节点
typedef struct Vertex_node
{
    int Vertex;
    struct Edge_node * Firstedge;
}Vn;

//边节点
typedef struct Edge_node
{
    int Adjvex;
    struct Edge_node *Next;

}En;

//邻接表
typedef struct Adjacency_tables
{
    int Vertex_num;
    Vn Vertexs[MAX_VERTES];
}At;

//数字栈
typedef struct Stack
{
    int top;
    int data[MAX_VERTES];
}S;



//树栈
typedef struct TStack
{
    int top;
    T* data[MAX_VERTES];
}TS;


//数字队列
typedef struct Que
{
    int data[MAX_VERTES];
    int l;
}Q;


//树队列
typedef struct TQue
{
    T* data[MAX_VERTES];
    int l;
}TQ;

#endif