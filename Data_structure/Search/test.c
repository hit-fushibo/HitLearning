#include"Bst.h"

#include"Bst.c"

int main (void)
{
    int node_num=0;
    scanf("%d",&node_num);
    T* root=(T*)malloc(sizeof(T));
    root->lchild=NULL;
    root->rchild=NULL;
    /*for(int i=0;i<node_num;i++)
    {
        int element=0;
        printf("num\n");
        scanf("%d",&element);
        if(i==0)
        {
            root->data=element;
        }
        else
        CreatBst(root,element);
    }*/
    /*if(Delete(root,4))
    {
        T* temp=root;
        root=root->rchild;
        free(temp);
    }*/
    //int *sort=Sort(root,node_num);
    /*for(int i=1;i<=sort[0];i++)
    {
        printf("%d ",sort[i]);
    }*/
    int *randmu=RandomInt(node_num);
    for(int i=0;i<node_num;i++)
    {
        printf("%d ",randmu[i]);
    }

    return 0;
}