#ifndef GRAPH_H
#define GRAPH_H


#include"Defination.h"

void InitGraph(Am* G);//初始化
int NewNode(Am * G);//向G中添加一个新节点
int DelNode(Am* G,int v);//删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
int SetSucc(Am* G,int v1,int v2,int weight);//建立边（v1，v2）
int DelSucc(Am *G,int v1,int v2);//删除边（v1,v2）
int* Succ(Am *G,int v);//返回所有v指向的顶点
int IsEdge(Am* G,int v1,int v2);//判断（v1,v2）是否为G中的边
int IsPostive(Am *G);//判断G中是否有负权


#endif