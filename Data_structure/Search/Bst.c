#include"Bst.h"

//创建BST
void CreatBst(T* root,int element)
{
    
    
    if(element>root->data)
    {
        if(root->rchild==NULL)
        {
            root->rchild=(T*)malloc(sizeof(T));
            root->rchild->data=element;
            root->rchild->rchild=NULL;
            root->rchild->lchild=NULL;
            
        }
        else
        CreatBst(root->rchild,element);
    }
    else
    {
        if(root->lchild==NULL)
        {
            root->lchild=(T*)malloc(sizeof(T));
            root->lchild->data=element;
            root->lchild->rchild=NULL;
            root->lchild->lchild=NULL;
        }
        else
        CreatBst(root->lchild,element);
    }
    
    return ;
}


int IsEmpty(T* root)
{
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//删除bst中值为element的节点
int Delete(T* root,int element)
{
    int temp=0;
    if(element>root->data)
    {
        temp=Delete(root->rchild,element);
        if(temp==1)
        {
            root->rchild=root->rchild->rchild;
        }
        return 0;
    }
    else if(element<root->data)
    {
        temp=Delete(root->lchild,element);
        if(temp==1)
        {
            root->lchild=root->lchild->rchild;
        }
        return 0;
    }
    else
    {
        if(root->lchild==NULL)
        {
            return 1;
        }
        else
        {
            root->data=GetNext(root);
            return 0;
        }
    }
}

//获取后继
int GetNext(T* root)
{
    T* temp=root->lchild;
    int i;
    if (temp->rchild->rchild==NULL)
    {
        i=temp->rchild->data;
    }
    else
    {
        while (temp->rchild->rchild)
        {
            temp=temp->rchild;
        }
    }
    i=temp->rchild->data;
    free(temp->rchild);
    temp->rchild=NULL;
    return i;
}

//查找
int Search(T* root,int element)
{
    int flag=0;
    if(root==NULL)
    {
        flag=0;
    }
    else if(element>root->data)
    {
        flag=Search(root->rchild,element);
    }
    else if(element<root->data)
    {
        flag=Search(root->lchild,element);
    }
    else
    {
        flag=1;
    }
    return flag;
}

//排序
int* Sort(T* root,int num)
{
    int *result=(int *)malloc(sizeof(int)*(num+1));
    result[0]=0;
    Inorder(root,result);
    return result;
}

void Inorder(T* root,int *order)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        Inorder(root->lchild,order);
        order[++order[0]]=root->data;
        Inorder(root->rchild,order);
    }
}

//1-num的有序数组
int* SortedInt(int num)
{
    int *result=(int *)malloc(sizeof(int)*num);
    for(int i=1;i<=num;i++)
    {
        result[i-1]=i;
    }
    return result;
}

//1-num的随机不重复数组
int* RandomInt(int num)
{
    int *result=(int *)malloc(sizeof(int)*num);
    int *temp=(int *)malloc(sizeof(int)*num);
    int *B=(int *)malloc(sizeof(int)*num);
    for(int i=1;i<=num;i++)
    {
        temp[i-1]=i;
        B[i-1]=0;
    }
    for(int i=0;i<num;i++)
    {
        int temp1=rand()%num;
        while(B[temp1])
        {
            temp1=rand()%num;
        }
        result[i]=temp[temp1];
        B[temp1]=1;
    }
    free(temp);free(B);
    return result;
}