#include"Undirected_graphs.h"

//   Adjacency_matrix   //

//初始化
void Un_Init_Am(Am *G)
{
    (*G).Vertex_num=-1;
}

//向图G中添加一个新的顶点
void Un_NewNode_Am(Am *G)
{
    if((*G).Vertex_num+1<MAX_VERTES)
    {
        (*G).Vertex_num++;
        for(int i=0;i<(*G).Vertex_num;i++)
        {
            (*G).Matrix[i][(*G).Vertex_num]=0;
            (*G).Matrix[(*G).Vertex_num][i]=0;
        }
        (*G).Matrix[(*G).Vertex_num][(*G).Vertex_num]=0;
    }
    else
    {
        printf("ERROR:no more space!(U NN M)\n");
        exit(8);
    }
    
}

//删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
void Un_DelNode_Am(Am *G,int v)
{
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!(U DN M)\n");
        exit(9);
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!(U DN M)\n");
        exit(8);
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
    }
    (*G).Vertex_num--;
}

//建立边（v1,v2）
void Un_SetSucc_Am(Am *G,int v1,int v2)
{
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        (*G).Matrix[v1][v2]=1;
        (*G).Matrix[v2][v1]=1;
    }
    else
    {
        printf("ERROR:Invalid parameter!(U SS M)\n");
        exit(8);
    }
}

//删除边（v1,v2）
void Un_DelSucc_Am(Am *G,int v1,int v2)
{
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        (*G).Matrix[v1][v2]=0;
        (*G).Matrix[v2][v1]=0;
    }
    else
    {
        printf("ERROR:Invalid parameter!(U DS M)\n");
        exit(8);
    }
}

//返回所有与v邻接的顶点
int * Un_Succ_Am(Am *G,int v)
{
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!(U S M)\n");
        exit(9);
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!(U S M)\n");
        exit(8);
    }
    
    int ctn=1,i=0;
    int *result=(int *)malloc(sizeof(int)*MAX_VERTES);
    result[0]=0;
    for(i=0;i<=(*G).Vertex_num;i++)
    {
        if((*G).Matrix[v][i]==1)
        {
            result[ctn]=i;
            ctn++;
            result[0]++;
        }
    }

}

//判断（v1,v2）是否为G中的边，是返回1，不是返回0
int Un_IsEdge_Am(Am *G ,int v1,int v2)
{
    if(v1<=(*G).Vertex_num&&v1>=0&&v2<=(*G).Vertex_num&&v2>=0)
    {
        return (*G).Matrix[v1][v2];
    }
    else
    {
        printf("ERROR:Invalid parameter!(U IE M)\n");
        exit(8);
    }
}


//   Adjacency_tables   //

//初始化
void Un_Init_At(At *G)
{
    G->Vertex_num=-1;
}

//向图G中添加一个新的顶点
void Un_NewNode_At(At *G)
{
    G->Vertex_num++;
    G->Vertexs[G->Vertex_num].Firstedge=NULL;
    G->Vertexs[G->Vertex_num].Vertex=G->Vertex_num;
}

//删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
void Un_DelNode_At(At *G, int v)
{

}

//建立边（v1,v2）
void Un_SetSucc_At(At *G, int v1, int v2)
{

}

//删除边（v1,v2）
void Un_DelSucc_At(At *G, int v1, int v2)
{

}

//返回所有与v邻接的顶点
int *Un_Succ_At(At *G, int v)
{

}

//判断（v1,v2）是否为G中的边，是返回1，不是返回0
int Un_IsEdge_At(At *G, int v1, int v2)
{

}
