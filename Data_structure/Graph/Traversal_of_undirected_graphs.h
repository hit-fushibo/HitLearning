#ifndef TRAVERSAL_OF_UNDIRECTED_GRAPHS_H
#define TRAVERSAL_OF_UNDIRECTED_GRAPHS_H

#include"Undirected_graphs.h"

//   Adjacency_matrix   //

int* Un_DFS_Am_Rec(Am *G,int *len,T **r);//无向图邻接矩阵的递归深度优先算法
int* Un_DFS_Am_Cir(Am *G,int *len,T **r);//无向图邻接矩阵的循环深度优先算法
int* Un_BFS_Am(Am *G,int *len,T **r);//无向图邻接矩阵的广度优先搜索算法

//   Adjacency_tables   //
int* Un_DFS_At_Rec(At *G,int *len);//无向图邻接表的递归深度优先算法
int* Un_DFS_At_Cir(At *G,int *len);//无向图邻接表的循环深度优先 算法
int* Un_BFS_At(At *G,int *len);//无向图邻接表的广度优先搜索算法
int* Un_GetDegree_At(At *G,int *len);//获取每个顶点的度

void Am_to_At(Am* G1,At *G2);//邻接矩阵转邻接表
void At_to_Am(At *G1,Am*G2);//邻接表转邻接矩阵
int* Visit_To_Num(int *visit,int len);//访问序列转访问编号

#endif