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
        getchar();
        getchar();
        exit(8);
    }
    
}

//删除图G中的顶点v(即编号为v的节点),并删除所有与v相连的边
void Un_DelNode_Am(Am *G,int v)
{
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!(U DN M)\n");
        getchar();
        getchar();
        exit(9);
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!(U DN M)\n");
        getchar();
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
        getchar();
        getchar();
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
        getchar();
        getchar();
        exit(8);
    }
}

//返回所有与v邻接的顶点
int * Un_Succ_Am(Am *G,int v)
{
    if((*G).Vertex_num==-1)
    {
        printf("ERROR:empty graph!(U S M)\n");
        getchar();
        getchar();
        exit(9);
    }
    if(!(v>=0&&v<=(*G).Vertex_num))
    {
        printf("ERROR:Invalid parameter!(U S M)\n");
        getchar();
        getchar();
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
        getchar();
        getchar();
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
    if(v<0||v>G->Vertex_num)
    {
        printf("ERROR:Invalid parameter!(U D T)\n");
        getchar();
        getchar();
        exit(8);
    }
    else
    {
        int i=0;
        for(i=v;i<G->Vertex_num;i++)
        {
            G->Vertexs[i]=G->Vertexs[i+1];
        }
        G->Vertex_num--;
        for(i=0;i<=G->Vertex_num;i++)
        {
            En *temp=G->Vertexs[i].Firstedge;
            if(temp->Adjvex==v)
            {
                G->Vertexs[i].Firstedge=NULL;
            }
            while (temp->Next)
            {
                if(temp->Next->Adjvex==v)
                {
                    temp->Next=temp->Next->Next;
                }
            }
        }
    }
}

//建立边（v1,v2）
void Un_SetSucc_At(At *G, int v1, int v2)
{
    if(v1>=0&&v1<=G->Vertex_num&&v2>=0&&v2<=G->Vertex_num)
    {
        En* temp=G->Vertexs[v1].Firstedge;
        En *p;
        if(temp==NULL)
        {
            p=(En *)malloc(sizeof(En));
            G->Vertexs[v1].Firstedge=p;
            temp=p;
            temp->Adjvex=v2;
            temp->Next=NULL;
        }
        else
        {
            while (temp->Next)
            {
                temp=temp->Next;
            }
            p=(En *)malloc(sizeof(En));
            temp->Next=p;
            temp->Next->Adjvex=v2;
            temp->Next->Next=NULL;
        }
        

        temp=G->Vertexs[v2].Firstedge;
        if(temp==NULL)
        {
            p=(En *)malloc(sizeof(En));
            G->Vertexs[v2].Firstedge=p;
            temp=p;
            temp->Adjvex=v1;
            temp->Next=NULL;
        }
        else
        {
            while (temp->Next)
            {
                temp=temp->Next;
            }
            p=(En *)malloc(sizeof(En));
            temp->Next=p;
            temp->Next->Adjvex=v1;
            temp->Next->Next=NULL;
        }
        
    }
    else
    {
        printf("ERROR:Invalid parameter!(U SS T)\n");
        getchar();
        getchar();
        exit(8);
    }
}

//删除边（v1,v2）
void Un_DelSucc_At(At *G, int v1, int v2)
{
    if(v1>=0&&v1<=G->Vertex_num&&v2>=0&&v2<=G->Vertex_num)
    {
        if(Un_IsEdge_At(G,v1,v2))
        {
            En *temp=G->Vertexs[v1].Firstedge;
            if(temp->Adjvex==v2)
            {
                G->Vertexs[v1].Firstedge=G->Vertexs[v1].Firstedge->Next;
            }
            else
            {
                while (temp->Next)
                {
                    if(temp->Next->Adjvex==v2)
                    {
                        temp->Next=temp->Next->Next;
                        break;
                    }
                }
            }

            temp=G->Vertexs[v2].Firstedge;
            if(temp->Adjvex==v1)
            {
                G->Vertexs[v2].Firstedge=G->Vertexs[v2].Firstedge->Next;
            }
            else
            {
                while (temp->Next)
                {
                    if(temp->Next->Adjvex==v1)
                    {
                        temp->Next=temp->Next->Next;
                        break;
                    }
                }
            }
        }
        else
        {
            printf("ERROR:not edge!(U SS T)\n");
            getchar();
            getchar();
            exit(8);
        }
    }
    else
    {
        printf("ERROR:Invalid parameter!(U SS T)\n");
        getchar();
        getchar();
        exit(8);
    }
}

//返回所有与v邻接的顶点
int *Un_Succ_At(At *G, int v)
{
    int *result=(int *)malloc(sizeof(int)*MAX_VERTES);
    int i=1;result[0]=0;
    En *temp=G->Vertexs[v].Firstedge;
    while (temp)
    {
        result[i]=temp->Adjvex;
        i++;
        result[0]++;
    }
    return result;
}

//判断（v1,v2）是否为G中的边，是返回1，不是返回0
int Un_IsEdge_At(At *G, int v1, int v2)
{
    if(v1>=0&&v1<=G->Vertex_num&&v2>=0&&v2<=G->Vertex_num)
    {
        En* temp=G->Vertexs[v1].Firstedge;
        while (temp)
        {
            if(temp->Adjvex==v2)
            break;
        }
        if(temp)
        return 1;
        else
        return 0;
        
    }
    else
    {
        printf("ERROR:Invalid parameter!(U SS T)\n");
        getchar();
        getchar();
        exit(8);
    }
}

//访问序列转访问编号
int* Visit_To_Num(int *visit,int len)
{
    int *num=(int *)malloc(sizeof(int)*len);
    for(int i=0;i<len;i++)
    {
        num[visit[i]]=i;
    }
    return num;
}