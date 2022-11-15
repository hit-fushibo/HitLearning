#include"Bst.h"

#include"Bst.c"

int main (void)
{
    int ctn=0;
    int check=0;
    T* root=(T*)malloc(sizeof(T));
    root->lchild=NULL;
    root->rchild=NULL;
    printf("Search\n0.exit\n1.creat bst\n2.delete\n3.sreach\n4.compare\n");
    check=scanf("%d",&ctn);
    while(check!=1)
    {
        printf("please enter a nember\n");
        check=scanf("%d",&ctn);
    }
    while (1)
    {
        switch (ctn)
        {
        case 0:
            
            break;
        case 1:
            {
                int num=0;
                printf("please enter the node num\n:");
                scanf("%d",&num);
                printf("please enter %d number\n",num);
                int temp=0;
                for(int i=0;i<num;i++)
                {
                    scanf("%d",&temp);
                    if(i==0)
                    root->data=temp;
                    else
                    CreatBst(root,temp);
                }
            }
            break;
        case 2:
            {
                printf("please enter the number you want to delete\n:");
                int del=0;
                scanf("%d",&del);
                Delete(root,del);
            }
            break;
        case 3:
            {
                printf("please enter the number to search\n:");
                int temp=0;
                scanf("%d",&temp);
                if(Search(root,temp))
                {
                    printf("success!\n");
                
                }
                else
                {
                    printf("failed\n");
                }
            }
            break;
        case 4:
            {
                printf("test 1-1024 sorted and random\n");
                TestSorted();
            }
            break;
        default:
        {
            printf("please enter a number between 0 to 4\n");
        }
            break;
        }
        if(ctn==0)break;
        printf("Search\n0.exit\n1.creat bst\n2.delete\n3.sreach\n4.compare\n");
        check=scanf("%d",&ctn);
        while(check!=1)
        {
            printf("please enter a nember\n");
            check=scanf("%d",&ctn);
        }
    }
    printf("thinks for using");
    getchar();
    getchar();
    return 0;
}