#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "Define.h"

//   Adjacency_matrix   //

void Un_Init_Am(Am *G);                    //初始化
void Un_NewNode_Am(Am *G);                 //向图G中添加一个新的顶点
void Un_DelNode_Am(Am *G, int v);          //删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
void Un_SetSucc_Am(Am *G, int v1, int v2); //建立边（v1,v2）
void Un_DelSucc_Am(Am *G, int v1, int v2); //删除边（v1,v2）
int *Un_Succ_Am(Am *G, int v);             //返回所有与v邻接的顶点
int Un_IsEdge_Am(Am *G, int v1, int v2);   //判断（v1,v2）是否为G中的边，是返回1，不是返回0

//   Adjacency_tables   //

void Un_Init_At(At *G);                    //初始化
void Un_NewNode_At(At *G);                 //向图G中添加一个新的顶点
void Un_DelNode_At(At *G, int v);          //删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
void Un_SetSucc_At(At *G, int v1, int v2); //建立边（v1,v2）
void Un_DelSucc_At(At *G, int v1, int v2); //删除边（v1,v2）
int *Un_Succ_At(At *G, int v);             //返回所有与v邻接的顶点
int Un_IsEdge_At(At *G, int v1, int v2);   //判断（v1,v2）是否为G中的边，是返回1，不是返回0

#endif