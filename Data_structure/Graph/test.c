#include"Undirected_graphs.h"

#include"Undirected_graphs.c"


int main(void)
{
    Am *umg=(Am*)malloc(sizeof(Am));
    Un_Init_Am(umg);
    int vertex_num=0,edge_num=0,i=0,v1=0,v2=0;
    printf("vertex_num edge_num\n");
    scanf("%d %d",&vertex_num,&edge_num);
    for(i=0;i<vertex_num;i++)
    {
        Un_NewNode_Am(umg);
    }
    for(i=0;i<edge_num;i++)
    {
        printf("edge v1--v2\n");
        scanf("%d %d",&v1,&v2);
        Un_SetSucc_Am(umg,v1,v2);
    }

}