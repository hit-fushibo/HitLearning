#include"fileop.h"

#include"search.c"
#include"graph.c"
#include"fileop.c"

int main(void)
{
    Am* G=(Am*)malloc(sizeof(Am));
    InitGraph(G);
    int **dijkstra_result,***floyd_result;
    int source=0;
    char filename[100]={0};
    int ctn=0,init=0,getin=0;
    printf("Graph\n0.exit\n1.creat graph\n2.dijkstra\n3.floyd\n4.v-->c\n5.v-->u&&u-->v\n:");
    getin=scanf("%d",&ctn);
    while (getin!=1)
    {
        printf("please enter a number!\n");
        fflush(stdin);
        getin=scanf("%d",&ctn);
    }
    while (1)
    {
        if(ctn==0)
        {
            
            break;
        }
        printf("\n");
        switch (ctn)
        {
        case 1:
            {
                printf("please enter open file: ");
                getchar();
                gets(filename);
                G=Read(filename);
                while (G->Vertex_num==-1)
                {
                    printf("please chack your file,intput must not be 0\n");
                    printf("please enter open file: ");
                    gets(filename);
                    G=Read(filename);
                }
                init=1;
            }
            break;
        case 2:
            {
                if(init==0)
                {
                    printf("please creat a graph!\n");
                    break;
                }
                else
                {
                    int source=0;
                    printf("source node\n");
                    getin=scanf("%d",&source);
                    if(source<0||source>G->Vertex_num)
                    getin=-1;
                    while (getin!=1)
                    {
                        fflush(stdin);
                        printf("please enter a legal number!\n");
                        getin=scanf("%d",&source);
                        if(source<0||source>G->Vertex_num)
                        getin=-1;
                    }
                    dijkstra_result=Dijkstra(G,source);
                    for(int i=0;i<=G->Vertex_num;i++)
                    {
                        printf("%d --> %d :",source,i);
                        if(dijkstra_result[0][i]==__INT16_MAX__)
                        {
                            printf("NULL\n");
                        }
                        else
                        {
                            int buf[MAX_VERTES]={0};
                            int num=-1;
                            int temp=dijkstra_result[1][i];
                            while (temp!=source)
                            {
                                buf[++num]=temp;
                                temp=dijkstra_result[1][temp];
                            }
                            
                            for(num;num>=0;num--)
                            {
                                printf("%d ",buf[num]);
                            }
                            printf("  length:%d\n",dijkstra_result[0][i]);
                        }
                    }
                }
            }
            break;
        case 3:
            {
                if(init==0)
                {
                    printf("please creat a graph!\n");
                    break;
                }
                else
                {
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

                                printf(" length:%d\n",floyd_result[0][i][j]);
                            }

                        }
                    }
                }
            }
            
            break;
        case 4:
            if(init==0)
                {
                    printf("please creat a graph!\n");
                    break;
                }
                else
                {
                    int c=0;
                    printf("please enter c\n:");
                    getin=scanf("%d",&c);
                    if(c<0||c>G->Vertex_num)
                    getin=-1;
                    while (getin!=1)
                    {
                        fflush(stdin);
                        printf("please enter a legal number!\n");
                        getin=scanf("%d",&c);
                        if(c<0||c>G->Vertex_num)
                        getin=-1;
                    }
                    floyd_result=Floyd(G);
                    for(int i=0;i<=G->Vertex_num;i++)
                    {
                        for(int j=0;j<=G->Vertex_num;j++)
                        {
                            if(j!=c)continue;
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

                                printf(" length:%d\n",floyd_result[0][i][j]);
                            }

                        }
                    }
                }
            break;
        case 5:
            if(init==0)
                {
                    printf("please creat a graph!\n");
                    break;
                }
                else
                {
                    int u=0,v=0;
                    printf("please enter u v\n:");
                    getin=scanf("%d %d",&u,&v);
                    if((u<0||u>G->Vertex_num)||v<0||v>G->Vertex_num)
                    getin=-1;
                    while (getin!=2)
                    {
                        fflush(stdin);
                        printf("please enter legal number!\n");
                        getin=scanf("%d %d",&u,&v);
                        if((u<0||u>G->Vertex_num)||v<0||v>G->Vertex_num)
                        getin=-1;
                    }
                    
                    floyd_result=Floyd(G);
                    for(int i=0;i<=G->Vertex_num;i++)
                    {
                        for(int j=0;j<=G->Vertex_num;j++)
                        {
                            if(!(i==u&&j==v||i==v&&j==u))continue;
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
                }
            break;
        default:
            {
                printf("Invalid parameter!");
                fflush(stdin);
            }
            break;
        }
        printf("\nGraph\n0.exit\n1.creat graph\n2.dijkstra\n3.floyd\n4.v-->c\n5.v-->u&&u-->v\n:");
        getin=scanf("%d",&ctn);
        while (getin!=1)
        {
            printf("please enter a number!\n");
            fflush(stdin);
            getin=scanf("%d",&ctn);
        }
    }
    printf("thanks for using\n");
    getchar();
    getchar();
    return 0;
}