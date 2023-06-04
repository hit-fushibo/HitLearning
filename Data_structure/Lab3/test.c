#include"fileop.h"

#include"search.c"
#include"graph.c"
#include"fileop.c"

int main(void)
{
    Am* G=(Am *)malloc(sizeof(Am));
    InitGraph(G);
    int **dijkstra_result,***floyd_result;
    int source=0;
    char filename[100]={0};
    printf("please enter open file: ");
    gets(filename);
    G=Read(filename);
    printf("source node\n");
    scanf("%d",&source);
    dijkstra_result=Dijkstra(G,source);
    for(int i=0;i<=G->Vertex_num;i++)
    {
        printf("%d ",dijkstra_result[0][i]);
    }
    printf("\n");
    for(int i=1;i<=G->Vertex_num;i++)
    {
        printf("%d ",dijkstra_result[1][i]);
    }
    printf("\n");
    
    floyd_result=Floyd(G);
    for(int i=0;i<=G->Vertex_num;i++)
    {
        for(int j=0;j<=G->Vertex_num;j++)
        {
            printf("%d --> %d :",i,j);
            if(floyd_result[0][i][j]==__INT16_MAX__)
            {
                printf("NULL \n");
            }
            else
            {
                int buf[MAX_VERTES]={0};
                int num=-1;
                int temp=floyd_result[1][i][j];
        
                while (temp!=i)
                {
                    buf[++num]=temp;
                    temp=floyd_result[1][i][temp];
                }
                
                for(num;num>=0;num--)
                {
                    printf("%d ",buf[num]);
                }

                printf(" %d\n",floyd_result[0][i][j]);
            }
            
        }
    }
    getchar();
    getchar();
    return 0;

}
/*
5 8
0 1 10
1 2 50
3 2 20
3 4 60
0 4 100
2 4 10
0 3 30
2 3 20
*/