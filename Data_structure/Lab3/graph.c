#include"graph.h"

//初始化
void InitGraph(Am* G)
{
    G->Vertex_num=-1;
}

//向G中添加一个新节点
int NewNode(Am * G)
{
    int flag=0;
    if((*G).Vertex_num+1<MAX_VERTES)
    {
        (*G).Vertex_num++;
        for(int i=0;i<(*G).Vertex_num;i++)
        {
            (*G).Matrix[i][(*G).Vertex_num]=__INT16_MAX__;
            (*G).Matrix[(*G).Vertex_num][i]=__INT16_MAX__;
        }
        (*G).Matrix[(*G).Vertex_num][(*G).Vertex_num]=__INT16_MAX__;
        flag=1;
    }
    else
    {
        printf("ERROR:no more space!\n");
    }
    return flag;
}

//删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
int DelNode(Am* G,int v)
{
    int flag=0;
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!\n");
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!\n");
    }
    if(v!=(*G).Vertex_num)
    {
        int i,j;
        for(i=0;i<=(*G).Vertex_num;i++)
        {
            for(j=v;j<(*G).Vertex_num;j++)
            {
                (*G).Matrix[i][j]=(*G).Matrix[i][j+1];
            }
        }
        for(j=0;j<=(*G).Vertex_num;j++)
        {
            for(i=v;i<(*G).Vertex_num;i++)
            {
                (*G).Matrix[i][j]=(*G).Matrix[i+1][j];
            }
        }
        (*G).Vertex_num--;
        flag=1;
    }
    return flag;
}

//建立边（v1，v2）
int SetSucc(Am* G,int v1,int v2,int weight)
{
    int flag=0;
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        (*G).Matrix[v1][v2]=weight;
        flag=1;
    }
    else
    {
        printf("ERROR:Invalid parameter!\n");
    }
    return flag;
}

//删除边（v1,v2）
int DelSucc(Am *G,int v1,int v2)
{
    int flag=0;
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        (*G).Matrix[v1][v2]=0;
        flag=1;
    }
    else
    {
        printf("ERROR:Invalid parameter!\n");

    }
    return flag;
}

//返回所有v指向的顶点
int* Succ(Am *G,int v)
{
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!\n");
        return NULL;
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!\n");
        return NULL;
    }
    
    int ctn=1,i=0;
    int *result=(int *)malloc(sizeof(int)*MAX_VERTES);
    result[0]=0;
    for(i=0;i<=(*G).Vertex_num;i++)
    {
        if((*G).Matrix[v][i]>=1)
        {
            result[ctn]=i;
            ctn++;
            result[0]++;
        }
    }
    return result;
}

//判断（v1,v2）是否为G中的边
int IsEdge(Am* G,int v1,int v2)
{
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        return (*G).Matrix[v1][v2];
    }
    else
    {
        printf("ERROR:Invalid parameter!\n");
        return -1;
    }
}