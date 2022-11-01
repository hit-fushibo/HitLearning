#include"Traversal_of_undirected_graphs.h"
#include "Stack.h"
#include"Que.h"
#include"Tree.h"

// ----------  Adjacency_matrix  ---------- //



int DFS_Am_rec(Am *G,int cre,int visited[],int test[],int num,T*root)
{
    for(int i=0;i<=G->Vertex_num;i++)
    {
        if(G->Matrix[cre][i]==1)
        {
            int flag=0;
            for(int j=1;j<=test[0];j++)
            {
                if(i==test[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                test[++test[0]]=i;
                visited[num]=i;
                InsertChild(root,i);
                num=DFS_Am_rec(G,i,visited,test,num+1,LastChild(root));
            }
        }
    }
    return num;
}

//无向图邻接矩阵的递归深度优先算法
int* Un_DFS_Am_Rec(Am *G,int *len,T **r)
{
    printf("please enter begin node number:\n");
    int begin=0;
    scanf("%d",&begin);
    int test[MAX_VERTES+1]={0};
    test[0]=1;
    test[1]=begin;
    int *visited=(int *)malloc(sizeof(int)*MAX_VERTES);
    visited[0]=begin;
    T *root=(T*)malloc(sizeof(T));
    root->data=begin;
    root->brother=NULL;
    root->child=NULL;
    int num=DFS_Am_rec(G,begin,visited,test,1,root);
    *len=num;
    *r=root;
    return visited;
}

//无向图邻接矩阵的循环深度优先算法
int* Un_DFS_Am_Cir(Am *G,int *len,T **r)
{
    //规定压栈时，先压节点编号，在压当前访问到的列编号

    S *s=(S *)malloc(sizeof (S));
    Creat(s);
    TS *ts=(TS *)malloc(sizeof(TS));
    TCreat(ts);
    T* root=(T*)malloc(sizeof(T)),*temp=root;
    int test[MAX_VERTES+1]={0};
    test[0]=1;
    int *visit=(int *)malloc(sizeof(int)*MAX_VERTES);
    int num=0,cre_node=0,cre_num=0;
    printf("please enter begin node number:\n");
    scanf("%d",&cre_node);
    visit[num++]=cre_node;
    test[1]=cre_node;
    root->data=cre_node;
    root->brother=NULL;
    root->child=NULL;
    while(1)
    {
        int i,j,flag;
        for( i=cre_num;i<=G->Vertex_num;i++)
        {
            if(G->Matrix[cre_node][i]==1)
            {
                flag=0;
                for( j=1;j<=test[0];j++)
                {
                    if(i==test[j])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    test[++test[0]]=i;
                    visit[num]=i;
                    num++;
                    InsertChild(temp,i);
                    break;
                }
            }
        }

        if(i>G->Vertex_num)
        {
            if(s->top==-1)
            {
                break;
            }
            else
            {
                cre_num=Top(s);Pop(s);
                cre_node=Top(s);Pop(s);
                temp=TTop(ts);TPop(ts);
            }
        }
        else
        {
            Push(s,cre_node);
            Push(s,i+1);
            TPush(ts,temp);
            cre_node=i;
            cre_num=0;
            temp=LastChild(temp);
        }
    }
    *len=num;
    *r=root;
    return visit;
}

//无向图邻接矩阵的广度优先搜索算法
int* Un_BFS_Am(Am *G,int *len,T **r)
{
    int cre_node=0;
    int num=0;
    Q *q=(Q*)malloc(sizeof(Q));
    CreatQueue(q);
    TQ* tq=(TQ*)malloc(sizeof(TQ));
    TCreatQueue(tq);
    T* root=(T*)malloc(sizeof(T)),*temp=root;
    root->child=NULL;
    root->brother=NULL;
    int test[MAX_VERTES+1]={0};
    int *visit=(int *)malloc(sizeof(int)*MAX_VERTES);
    printf("please enter begin node number:\n");
    scanf("%d",&cre_node);
    test[0]++;test[1]=cre_node;
    visit[num++]=cre_node;
    EnQueue(q,cre_node);
    TEnQueue(tq,root);
    while (QueueEmpty(q))
    {
        temp=TQueueHead(tq);TDeQueue(tq);
        cre_node=QueueHead(q);DeQueue(q);
        temp->data=cre_node;
        int i=0,flag=0,j=0;
        for(i=0;i<=G->Vertex_num;i++)
        {
            if(G->Matrix[cre_node][i])
            {
                flag=0;
                for(j=1;j<=test[0];j++)
                {
                    if(i==test[j])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    test[++test[0]]=i;
                    visit[num]=i;
                    num++;
                    InsertChild(temp,i);
                    EnQueue(q,i);
                    TEnQueue(tq,LastChild(temp));
                }
            }
        }
    }
    *len=num;
    *r=root;
    return visit;
}



// ----------  Adjacency_tables  ---------- //


//无向图邻接表的递归深度优先算法
int DFS_At_rec(At*G,int cre,int visited[],int test[],int num)
{
    En *temp=G->Vertexs[cre].Firstedge;
    while (temp)
    {
        int flag=0,j=0;
        for(j=1;j<=test[0];j++)
        {
            if(temp->Adjvex==test[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            test[++test[0]]=temp->Adjvex;
            visited[num]=temp->Adjvex;
            num=DFS_At_rec(G,temp->Adjvex,visited,test,num+1);
        }
        temp=temp->Next;
    }
    return num;
}


int* Un_DFS_At_Rec(At *G,int *len)
{
    printf("please enter begin node number:\n");
    int begin=0;
    scanf("%d",&begin);
    int test[MAX_VERTES+1]={0};
    test[0]=1;
    test[1]=begin;
    int *visited=(int *)malloc(sizeof(int)*MAX_VERTES);
    visited[0]=begin;
    int num=DFS_At_rec(G,begin,visited,test,1);
    for(int i=0;i<num;i++)
    {
        printf("%d ",visited[i]);
    }
    printf("\n");
    *len=num;
    return visited;
}


//无向图邻接表的循环深度优先算法
int* Un_DFS_At_Cir(At *G,int *len)
{
    //规定压栈时，先压节点编号，在压当前访问到的列编号

    S *s=(S *)malloc(sizeof (S));
    Creat(s);
    int test[MAX_VERTES+1]={0};
    test[0]=1;
    int *visit=(int *)malloc(sizeof(int)*MAX_VERTES);
    int num=0,cre_node=0,cre_num=0;
    printf("please enter begin node number:\n");
    scanf("%d",&cre_node);
    visit[num++]=cre_node;
    test[1]=cre_node;
    while (1)
    {
        int i,j,flag;
        En *temp=G->Vertexs[cre_node].Firstedge;
        for(i=0;i<cre_num;i++)
        {
            temp=temp->Next;
        }
        while (temp)
        {
            flag=0;
            for(j=1;j<=test[0];j++)
            {
                if(temp->Adjvex==test[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                test[++test[0]]=temp->Adjvex;
                visit[num++]=temp->Adjvex;
                break;
            }
            temp=temp->Next;
        }
        if(!temp)
        {
            if(s->top==-1)
            {
                break;
            }
            else
            {
                cre_num=Top(s);Pop(s);
                cre_node=Top(s);Pop(s);
            }
        }
        else
        {
            Push(s,cre_node);
            Push(s,cre_num);
            cre_node=temp->Adjvex;
            cre_num=0;
        }
    }
    for(int i=0;i<num;i++)
    {
        printf("%d ",visit[i]);
    }
    printf("\n");
    *len=num;
    return visit;
}


//无向图邻接表的广度优先搜索算法
int* Un_BFS_At(At *G,int *len)
{
    int cre=0;
    int num=0;
    Q *q=(Q *)malloc(sizeof(Q));
    CreatQueue(q);
    int test[MAX_VERTES+1]={0};
    int *visit=(int *)malloc(sizeof(int)*MAX_VERTES);
    printf("please enter begin node number:\n");
    scanf("%d",&cre);
    test[0]++;test[1]=cre;
    visit[0]=cre;
    EnQueue(q,cre);
    while(QueueEmpty(q))
    {
        cre=QueueHead(q);DeQueue(q);
        int i=0,flag=0,j=0;
        En *temp=G->Vertexs[cre].Firstedge;
        while (temp)
        {
            flag=0;
            for(j=1;j<=test[0];j++)
            {
                if(temp->Adjvex==test[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                test[++test[0]]=temp->Adjvex;
                visit[num++]=temp->Adjvex;
                EnQueue(q,temp->Adjvex);
            }
            temp=temp->Next;
        }
    }
    for(int i=0;i<num;i++)
    {
        printf("%d ",visit[i]);
    }
    printf("\n");
    *len=num;
    return visit;
}

//获取每个顶点的度
int* Un_GetDegree_At(At *G,int *len)
{
    int *degree=(int *)malloc(sizeof(int)*(G->Vertex_num+1));
    int i=0,j=0;
    En *temp=0;
    for(i=0;i<=G->Vertex_num;i++)
    {
        j=0;
        temp=G->Vertexs[i].Firstedge;
        while (temp)
        {
            j++;
            temp=temp->Next;
        }
        degree[i]=j;
    }
    *len=G->Vertex_num+1;
    return degree;
}

//邻接矩阵转邻接表
void Am_to_At(Am* G1,At *G2)
{
    Un_Init_At(G2);
    int i=0,j=0;
    for(i=0;i<=G1->Vertex_num;i++)
    {
        Un_NewNode_At(G2);
    }
    for(i=0;i<=G1->Vertex_num;i++)
    {
        for(j=i+1;j<=G1->Vertex_num;j++)
        {
            if(G1->Matrix[i][j]==1)
            {
                Un_SetSucc_At(G2,i,j);
            }
        }
    }
}

//邻接表转邻接矩阵
void At_to_Am(At *G1,Am*G2)
{
    Un_Init_Am(G2);
    int i=0,j=0;
    for(i=0;i<=G2->Vertex_num;i++)
    {
        Un_NewNode_Am(G2);
    }
    for(i=0;i<=G1->Vertex_num;i++)
    {
        En *temp=G1->Vertexs[i].Firstedge;
        while (temp)
        {
            Un_SetSucc_Am(G2,i,temp->Adjvex);
            temp=temp->Next;
        }
    }
}

