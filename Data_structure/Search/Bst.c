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
    if(temp->rchild==NULL)
    {
        i=temp->data;
        root->lchild=temp->lchild;
        free(temp);
        return i;
    }
    else if (temp->rchild->rchild==NULL)
    {
        i=temp->rchild->data;
        free(temp->rchild);
        return i;
    }
    else
    {
        while (temp->rchild->rchild)
        {
            temp=temp->rchild;
        }
        i=temp->rchild->data;
        temp->rchild=temp->rchild->lchild;
        free(temp->rchild);
        return i;
    }
}

//查找
int Search(T* root,int element)
{
    global_count++;
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
    int *result=(int *)malloc(sizeof(int)*(num+1));
    for(int i=1;i<=num;i++)
    {
        result[i]=i;
    }
    result[0]=num;
    return result;
}

//1-num的随机不重复数组
int* RandomInt(int num)
{
    int *result=(int *)malloc(sizeof(int)*(num+1));
    int *temp=(int *)malloc(sizeof(int)*(num+1));
    int *B=(int *)malloc(sizeof(int)*(num+1));
    for(int i=1;i<=num;i++)
    {
        temp[i]=i;
        B[i]=0;
    }
    for(int i=1;i<=num;i++)
    {
        int temp1=rand()%num+1;
        while(B[temp1])
        {
            
            temp1=rand()%num+1;
        }
        result[i]=temp[temp1];
        B[temp1]=1;
    }
    result[0]=num;
    free(temp);free(B);
    return result;
}

//二分查找
int BinSearch(int *num,int element)
{
    int i=1,j=num[0];
    int temp=(i+j)/2;
    int flag=0;
    while (i<=j)
    {
        if(element==num[temp])
        {
            flag++;
            break;
        }
        else if(element<num[temp])
        {
            j=temp-1;
        }
        else
        {
            i=temp+1;
        }
        flag++;
        temp=(i+j)/2;
    }
    return flag;
}


int TestSorted()
{
    int *sorted,*random;
    int length=1024;
    sorted=SortedInt(length);
    random=RandomInt(length);
    T* root=(T*)malloc(sizeof(T));
    root->lchild=NULL;
    root->rchild=NULL;
    int success=0,unsuccess=0;
    for(int i=0;i<1000;i++)
    {
        int element=rand()%1024+1;
        success+=BinSearch(sorted,element);
        while (element>=1&&element<=1024)
        {
            element=rand();
        }
        unsuccess+=BinSearch(sorted,element);
    }
    printf("bin search:success :%f,unsuccess :%f\n",(float)success/1000,(float)unsuccess/1000);
    for(int j=1;j<=1024;j++)
    {
        if(j==1)
        {
            root->data=sorted[j];
        }
        else
        {
            CreatBst(root,sorted[j]);
        }
    }
    success=0;unsuccess=0;
    for(int i=0;i<1000;i++)
    {
        int element=rand()%1024+1;
        global_count=0;
        Search(root,element);
        success+=global_count;
        global_count=0;
        while (element>=1&&element<=1024)
        {
            element=rand();
        }
        Search(root,element);
        unsuccess+=global_count;
    }
    printf("bst sorted success :%f,unsuccess :%f\n",(float)success/1000,(float)unsuccess/1000);
    for(int j=1;j<=1024;j++)
    {
        if(j==1)
        {
            root->data=random[j];
        }
        else
        {
            CreatBst(root,random[j]);
        }
    }
    success=0;unsuccess=0;
    for(int i=0;i<1000;i++)
    {
        root->lchild=NULL;
        root->rchild=NULL;
        random=RandomInt(length);
        for(int j=1;j<=1024;j++)
        {
            if(j==1)
            {
                root->data=random[j];
            }
            else
            {
                CreatBst(root,random[j]);
            }
        }
        
        int element=rand()%1024+1;
        global_count=0;
        Search(root,element);
        success+=global_count;
        global_count=0;
        while (element>=1&&element<=1024)
        {
            element=rand();
        }
        Search(root,element);
        unsuccess+=global_count;
    }
    printf("bst random success :%f,unsuccess :%f\n",(float)success/1000,(float)unsuccess/1000);

}