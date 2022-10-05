#include"BinTree.h"

//建立一颗空的二叉树
void Empty(BTreeNode * bt)
{
    bt->data=0;
    bt->lchild=NULL;
    bt->rchild=NULL;
}

//判断二叉树是否为空，空返回0，否则返回1
int IsEmpty(BTreeNode * bt)
{
    if(bt->lchild==NULL&&bt->rchild==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//建立一颗新的二叉树，数据为data，左子树和右子树分别为LT和RT
BTreeNode * CreatBT(int data,BTreeNode * LT,BTreeNode * RT)
{
    BTreeNode *temp=(BTreeNode *)malloc(sizeof(BTreeNode));
    temp->data=data;
    temp->lchild=LT;
    temp->rchild=RT;
    return temp;

}

//返回bt的左儿子，若无左儿子，返回空
BTreeNode * Lchild(BTreeNode * bt)
{
    return bt->lchild;
}

//返回bt的右儿子，若无右儿子，返回空
BTreeNode * Rchild(BTreeNode * bt)
{
    return bt->rchild;
}

//返回bt的根节点的数据域
int Data(BTreeNode * bt)
{
    return bt->data;
}

//生成测试用二叉树
BTreeNode *TestCreatBT(int depth)
{
    if(depth==0)
    {
        return NULL;
    }
    BTreeNode *root=(BTreeNode *)malloc(sizeof(BTreeNode));
    Empty(root);
    scanf("%d",&root->data);
    root->lchild=TestCreatBT(depth-1);
    root->rchild=TestCreatBT(depth-1);
}

//递归先序遍历
void RecPreOrder(BTreeNode * bt)
{
    if(bt==NULL)
    {
        return;
    }
    else
    {
        printf("%d ",Data(bt));
        RecPreOrder(bt->lchild);
        RecPreOrder(bt->rchild);
    }
}

//递归中序遍历
void RecInOredr(BTreeNode * bt)
{
    if(bt==NULL)
    {
        return;
    }
    else
    {
        RecPreOrder(bt->lchild);
        printf("%d ",Data(bt));
        RecPreOrder(bt->rchild);
    }
}

//递归后序遍历
void RecPostOrder(BTreeNode * bt)
{
    if(bt==NULL)
    {
        return;
    }
    else
    {
        RecPreOrder(bt->lchild);
        RecPreOrder(bt->rchild);
        printf("%d ",Data(bt));
    }
}

//循环先序遍历
void CirPreOrder(BTreeNode * bt)
{

}

//循环中序遍历
void CirInOrder(BTreeNode *bt)
{
    BtStack *s=(BtStack *)malloc(sizeof(BtStack));
    Creat(s);
    BTreeNode *temp=(BtStack *)malloc(sizeof(BtStack));
    temp=bt;
    while (s->top!=MAXLENGTH||!IsEmpty(temp))
    {
        if(!IsEmpty(temp))
        {
            Push(s,*temp);
            temp=temp->lchild;
        }
        else
        {
            *temp=Top(s);Pop(s);
            printf("%d ",Data(temp));
            temp=temp->rchild;
        }
    }
    
}

//循环后序遍历
void CirPostOrder(BTreeNode *bt)
{

}