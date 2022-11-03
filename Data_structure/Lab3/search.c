#include"search.h"


//dijkstra算法
int** Dijkstra(Am* G,int source)
{
    int** result=(int **)malloc(sizeof(int *)*2);
    result[0]=(int *)malloc(sizeof(int)*(G->Vertex_num+1));
    result[1]=(int *)malloc(sizeof(int)*(G->Vertex_num+1));
    int *visited=(int *)malloc(sizeof(int)*(G->Vertex_num+2));
    visited[0]=1;
    visited[1]=source;
    int i=0;
    for(i=0;i<=G->Vertex_num;i++)
    {
        result[0][i]=G->Matrix[source][i];
        result[1][i]=0;
    }
    for(i=0;i<G->Vertex_num;i++)
    {
        int j=0,k=0,l=__INT16_MAX__,m=0,flag=0;
        for(j=0;j<=G->Vertex_num;j++)
        {
            flag=0;
            for(k=1;k<=visited[0];k++)
            {
                if(j==visited[k])
                {
                    flag=1;break;
                }
            }
            if(!flag)
            {
                if(result[0][j]<l)
                {
                    m=j;
                    l=result[0][j];
                }
            }
        }
        visited[++visited[0]]=m;
        for(j=0;j<=G->Vertex_num;j++)
        {
            flag=0;
            for(k=1;k<=visited[0];k++)
            {
                if(j==visited[k])
                {
                    flag=1;break;
                }
            }
            if(!flag)
            {
                if(result[0][m]+G->Matrix[m][j]<result[0][j])
                {
                    result[1][j]=m;
                    result[0][j]=result[0][m]+G->Matrix[m][j];
                }
            }
        }
    }
    return result;
}

//floyd算法
int*** Floyd(Am* G)
{
    int ***result=(int ***)malloc(sizeof(int **)*2);
    result[0]=(int **)malloc(sizeof(int *)*(G->Vertex_num+1));
    result[1]=(int **)malloc(sizeof(int *)*(G->Vertex_num+1));
    
    for(int i=0;i<=G->Vertex_num;i++)
    {
        result[0][i]=(int *)malloc(sizeof(int)*(G->Vertex_num+1));
        result[1][i]=(int *)malloc(sizeof(int)*(G->Vertex_num+1));
        for(int j=0;j<=G->Vertex_num;j++)
        {
            result[0][i][j]=G->Matrix[i][j];
            result[1][i][j]=i;
        }
    }
    for(int i=0;i<=G->Vertex_num;i++)
    {
        for(int j=0;j<=G->Vertex_num;j++)
        {
            for(int k=0;k<=G->Vertex_num;k++)
            {
                if(result[0][i][k]+result[0][k][j]<result[0][i][j])
                {
                    result[0][i][j]=result[0][i][k]+result[0][k][j];
                    result[1][i][j]=k;
                }
            }
        }
    }
    return result;
}