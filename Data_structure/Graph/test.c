#include"Undirected_graphs.h"
#include"Traversal_of_undirected_graphs.h"
#include"Stack.h"
#include"Que.h"
#include"Tree.h"

#include"Undirected_graphs.c"
#include"Traversal_of_undirected_graphs.c"
#include"Stack.c"
#include"Que.c"
#include"Tree.c"


int main(void)
{

    printf("Just for testing\nthe node number is 0, 1, 2, 3...\nWhen the node is deleted, the number will remain the sequence of 0, 1, 2, 3.\n");


    printf("Graph\n0.exit\n1.creat graph\n2.Modify graph\n3.DFS\n4.BFS\n5.Minimum spanning tree\n6.Get degree\n:");
    Am *umg=(Am*)malloc(sizeof(Am));
    Un_Init_Am(umg);
    At *utg=(At *)malloc(sizeof(At));
    Un_Init_At(utg);
    T *BFS_tree=(T*)malloc(sizeof(T)),*DFS_tree=(T*)malloc(sizeof(T));
    int *visit_DFS,*visit_BFS,*degree,*DFS_num,*BFS_num;
    int vertex_num=0,edge_num=0,i=0,v1=0,v2=0,len=0;
    int ctn=0;
    int init_flag=0;
    scanf("%d",&ctn);
    while (1)
    {
        switch (ctn)
        {
        case 0:
            {
                printf("thanks for using!\n");
            }
            break;
        case 1:
            {
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
                init_flag=1;
            }
            break;
        case 2:
            {
                if(init_flag==0)
                {
                    printf("graph is null!\n");
                    break;
                }
                int inctn=0;
                printf("Modify\n0.exit\n1.Add vertex\n2.delete vertex\n3.Add side\n4.delete side\n:");
                scanf("%d",&inctn);
                while (1)
                {
                    switch (inctn)
                    {
                    case 0:
                        {
                            break;
                        }
                        break;
                    case 1:
                        {
                            int addnum=0;
                            printf("Please enter the number of vertices to be added\n:");
                            scanf("%d",&addnum);
                            if(addnum<0)
                            {
                                printf("WARING:must a positive number!\n");
                                continue;
                            }
                            else
                            {
                                int i=0;
                                for(i=0;i<addnum;i++)
                                {
                                    Un_NewNode_Am(umg);
                                }
                            }
                        }
                        break;
                    case 2:
                        {
                            int deletenum=0;
                            printf("Please enter the number of vertices to be deleted\n:");
                            scanf("%d",&deletenum);
                            if(deletenum<0)
                            {
                                printf("WARING:must a positive number!\n");
                                continue;
                            }
                            else
                            {
                                Un_DelNode_Am(umg,deletenum);
                            }
                        }
                        break;
                    case 3:
                        {
                            int addnum=0;
                            printf("Please enter the number of sides to be added\n:");
                            scanf("%d",&addnum);
                            if(addnum<0)
                            {
                                printf("WARING:must a positive number!\n");
                                continue;
                            }
                            else
                            {
                                int i=0,v1,v2;
                                for(i=0;i<addnum;i++)
                                {
                                    printf("enter v1--v2\n");
                                    scanf("%d %d",&v1,&v2);
                                    Un_SetSucc_Am(umg,v1,v2);
                                }
                            }
                        }
                        break;
                    case 4:
                        {
                            int deletenum=0;
                            printf("Please enter the number of sides to be deleted\n:");
                            scanf("%d",&deletenum);
                            if(deletenum<0)
                            {
                                printf("WARING:must a positive number!\n");
                                continue;
                            }
                            else
                            {
                                int i=0,v1=0,v2=0;
                                for(i=0;i<deletenum;i++)
                                {
                                    printf("v1--v2\n");
                                    scanf("%d %d",&v1,&v2);
                                    Un_DelSucc_Am(umg,v1,v2);
                                }
                            }
                        }
                        break;
                    default:
                        {
                            printf("WARING:Invalid parameter!\n");
                        }
                        break;
                    }
                    if(inctn==0)break;
                    printf("Modify\n0.exit\n1.Add vertex\n2.delete vertex\n3.Add side\n4.delete side\n:");
                    scanf("%d",&inctn);
                }
                
            }
            break;
        case 3:
            {
                if(init_flag==0)
                {
                    printf("graph is null!\n");
                    break;
                }
                int inctn=0;
                printf("\n1.recursion DFS\n2.loop DFS\n:");
                scanf("%d",&inctn);
                if(inctn==1)
                {
                    visit_DFS=Un_DFS_Am_Rec(umg,&len,&DFS_tree);
                    DFS_num=Visit_To_Num(visit_DFS,len);
                    printf("rec dfs sequence:\n");
                    for(int i=0;i<len;i++)
                    {
                        printf("%d ",visit_DFS[i]);
                    }
                    printf("\n");
                    printf("rec dfs number:\n");
                    for(int i=0;i<len;i++)
                    {
                        printf("%d ",DFS_num[i]);
                    }
                    printf("\n");
                }
                else if(inctn==2)
                {
                    visit_DFS=Un_DFS_Am_Cir(umg,&len,&DFS_tree);
                    DFS_num=Visit_To_Num(visit_DFS,len);
                    printf("cir dfs sequence:\n");
                    for(int i=0;i<len;i++)
                    {
                        printf("%d ",visit_DFS[i]);
                    }
                    printf("\n");
                    printf("cir dfs number:\n");
                    for(int i=0;i<len;i++)
                    {
                        printf("%d ",DFS_num[i]);
                    }
                    printf("\n");
                }
                else
                {
                    printf("WARING:Invalid parameter!\n");
                }
            }
            break;
        case 4:
            {
                if(init_flag==0)
                {
                    printf("graph is null!\n");
                    break;
                }
                visit_BFS=Un_BFS_Am(umg,&len,&BFS_tree);
                BFS_num=Visit_To_Num(visit_BFS,len);
                printf("bfs sequence:\n");
                for(int i=0;i<len;i++)
                {
                    printf("%d ",visit_BFS[i]);
                }
                printf("\n");
                printf("bfs number:\n");
                for(int i=0;i<len;i++)
                {
                    printf("%d ",BFS_num[i]);
                }
                printf("\n");
            }
            break;
        case 5:
            {
                if(init_flag==0)
                {
                    printf("graph is null!\n");
                    break;
                }
                int inctn=0;
                printf("\n1.DFS\n2.BFS\n:");
                scanf("%d",&inctn);
                if(inctn==1)
                {
                    Un_DFS_Am_Rec(umg,&len,&DFS_tree);
                    ShowTree(DFS_tree);
                }
                else if(inctn==2)
                {
                    Un_BFS_Am(umg,&len,&BFS_tree);
                    ShowTree(BFS_tree);
                }
            }
            break;
        case 6:
            {
                if(init_flag==0)
                {
                    printf("graph is null!\n");
                    break;
                }
                Am_to_At(umg,utg);
                degree=Un_GetDegree_At(utg,&len);
                for(int i=0;i<len;i++)
                {
                    printf("%d ",degree[i]);
                }
                printf("\n");
            }
            break;
        default:
            printf("WARING:Invalid parameter!");
            break;
        }
        if(ctn==0)
        {
            break;
        }
        printf("Graph\n0.exit\n1.creat graph\n2.Modify graph\n3.DFS\n4.BFS\n5.Minimum spanning tree\n6.Get degree\n:");
        scanf("%d",&ctn);
    }
    printf("Press any key to exit");
    getchar();
    getchar();

    



//   test of Undirected graph with Adjacency_matrix   //
    

    //Am *umg=(Am*)malloc(sizeof(Am));
    //Un_Init_Am(umg);
    //At *utg=(At *)malloc(sizeof(At));
    //Un_Init_At(utg);
    //T *BFS_tree=(T*)malloc(sizeof(T)),*DFS_tree=(T*)malloc(sizeof(T));
    //int *visit_DFS,*visit_BFS,*degree;
    //int vertex_num=0,edge_num=0,i=0,v1=0,v2=0,len=0;
    //printf("vertex_num edge_num\n");
    //scanf("%d %d",&vertex_num,&edge_num);
    //for(i=0;i<vertex_num;i++)
    //{
    //    Un_NewNode_Am(umg);
    //}
    //for(i=0;i<edge_num;i++)
    //{
    //    printf("edge v1--v2\n");
    //    scanf("%d %d",&v1,&v2);
    //    Un_SetSucc_Am(umg,v1,v2);
    //}
    //visit_DFS=Un_DFS_Am_Rec(umg,&len,&DFS_tree);
    //printf("rec dfs umg:\n");
    //for(int i=0;i<len;i++)
    //{
    //    printf("%d ",visit_DFS[i]);
    //}
    //printf("\n");
    //visit_DFS=Un_DFS_Am_Cir(umg,&len,&DFS_tree);
    //printf("cir dfs umg:\n");
    //for(int i=0;i<len;i++)
    //{
    //    printf("%d ",visit_DFS[i]);
    //}
    //printf("\n");
    //visit_BFS=Un_BFS_Am(umg,&len,&BFS_tree);
    //printf("bfs umg:\n");
    //for(int i=0;i<len;i++)
    //{
    //    printf("%d ",visit_BFS[i]);
    //}
    //printf("\n");
    //Am_to_At(umg,utg);
    //degree=Un_GetDegree_At(utg,&len);
    //printf("degree:\n");
    //for(int i=0;i<len;i++)
    //{
    //    printf("%d ",degree[i]);
    //}
    //printf("\n");


//   test of Undirected graph with Adjacency_tables   //


    //At *utg=(At *)malloc(sizeof(At));
    //Un_Init_At(utg);
    //int *visit;
    //int vertex_num=0,edge_num=0,i=0,v1=0,v2=0,len=0;
    //printf("vertex_num edge_num\n");
    //scanf("%d %d",&vertex_num,&edge_num);
    //for(i=0;i<vertex_num;i++)
    //{
    //    Un_NewNode_At(utg);
    //}
    //for(i=0;i<edge_num;i++)
    //{
    //    printf("edge v1--v2\n");
    //    scanf("%d %d",&v1,&v2);
    //    Un_SetSucc_At(utg,v1,v2);
    //}
    //visit=Un_BFS_At(utg,&len);
    return 0;
}
/*
13 13

*/