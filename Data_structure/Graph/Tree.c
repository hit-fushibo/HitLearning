#include"Tree.h"


//将element插入到root的儿子中
void InsertChild(T* root,int element)
{
    T* temp=root->child;
    if(temp)
    {
        while (temp->brother)
        {
            temp=temp->brother;
        }
        temp->brother=(T*)malloc(sizeof(T));
        temp->brother->data=element;
        temp->brother->brother=NULL;
        temp->brother->child=NULL;
    }
    else
    {
        root->child=(T*)malloc(sizeof(T));
        root->child->data=element;
        root->child->brother=NULL;
        root->child->child=NULL;
    }
}

//返回root的最后一个孩子,如果没有孩子，返回NULL
T* LastChild(T *root)
{
    T *temp=root->child;
    if(temp)
    {
        while (temp->brother)
        {
            temp=temp->brother;
        }
    }
    return temp;
    
}