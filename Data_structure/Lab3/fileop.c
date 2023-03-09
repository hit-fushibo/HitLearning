#include"fileop.h"

//从文件中读取图
Am *Read(char*name)
{
    Am *G=(Am*)malloc(sizeof(Am));
    InitGraph(G);
    FILE* fp=NULL;
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("error:can't open file!\n");
    }
    else
    {
        int vertex_num=0,edge_num=0,v1=0,v2=0,weight=1;
        fscanf(fp,"%d %d",&vertex_num,&edge_num);
        for(int i=0;i<vertex_num;i++)
        {
            NewNode(G);
        }
        for(int i=0;i<edge_num;i++)
        {
            fscanf(fp,"%d %d %d",&v1,&v2,&weight);
            SetSucc(G,v1,v2,weight);
        }
    }
    return G;
}