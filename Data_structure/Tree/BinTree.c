#include "BinTree.h"

//建立一颗空的二叉树
void Empty(BTreeNode *bt)
{
    bt->data = 0;
    bt->lchild = NULL;
    bt->rchild = NULL;
}

//判断二叉树是否为空，空返回0，否则返回1
int IsEmpty(BTreeNode *bt)
{
    if (bt->lchild == NULL && bt->rchild == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//建立一颗新的二叉树，数据为data，左子树和右子树分别为LT和RT
BTreeNode *CreatBT(int data, BTreeNode *LT, BTreeNode *RT)
{
    BTreeNode *temp = (BTreeNode *)malloc(sizeof(BTreeNode));
    temp->data = data;
    temp->lchild = LT;
    temp->rchild = RT;
    return temp;
}

//返回bt的左儿子，若无左儿子，返回空
BTreeNode *Lchild(BTreeNode *bt)
{
    return bt->lchild;
}

//返回bt的右儿子，若无右儿子，返回空
BTreeNode *Rchild(BTreeNode *bt)
{
    return bt->rchild;
}

//返回bt的根节点的数据域
int Data(BTreeNode *bt)
{
    return bt->data;
}

//根据字符串p生成二叉树，p先序序列，data之间用空格区分，data为空格代表为空节点
char *CreatBt(BTreeNode **bt, char *p)
{
    if (*p >= '0' && *p <= '9')
    {
        (*bt)->lchild = (BTreeNode *)malloc(sizeof(BTreeNode));
        (*bt)->rchild = (BTreeNode *)malloc(sizeof(BTreeNode));
        int data = (int)strtof(p, &p);
        (*bt)->data = data;
        p++;
        p = CreatBt(&((*bt)->lchild), p);
        p = CreatBt(&((*bt)->rchild), p);
    }
    else
    {
        *bt = NULL;
        if (*p != '\0')
        {
            p++;
            p++;
        }
    }
    return p;
}

//生成测试用二叉树
BTreeNode *TestCreatBT(int depth)
{
    if (depth == 0)
    {
        return NULL;
    }
    BTreeNode *root = (BTreeNode *)malloc(sizeof(BTreeNode));
    Empty(root);
    scanf("%d", &root->data);
    root->lchild = TestCreatBT(depth - 1);
    root->rchild = TestCreatBT(depth - 1);
}

//判断两个根节点是否相同
int JudgeEqul(BTreeNode *a, BTreeNode *b)
{
    if (a->data == b->data && a->lchild == b->lchild && a->rchild == b->rchild)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//递归先序遍历
void RecPreOrder(BTreeNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    else
    {
        printf("%d ", Data(bt));
        RecPreOrder(bt->lchild);
        RecPreOrder(bt->rchild);
    }
}

//递归中序遍历
void RecInOrder(BTreeNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    else
    {
        RecInOrder(bt->lchild);
        printf("%d ", Data(bt));
        RecInOrder(bt->rchild);
    }
}

//递归后序遍历
void RecPostOrder(BTreeNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    else
    {
        RecPostOrder(bt->lchild);
        RecPostOrder(bt->rchild);
        printf("%d ", Data(bt));
    }
}

//循环先序遍历
void CirPreOrder(BTreeNode *bt)
{
    BtStack *s = (BtStack *)malloc(sizeof(BtStack));
    Creat(s);
    BTreeNode *temp = (BTreeNode *)malloc(sizeof(BTreeNode));
    temp = bt;
    while (s->top != MAXLENGTH || temp)
    {
        if (temp)
        {
            printf("%d ", temp->data);
            Push(s, *temp);
            temp = temp->lchild;
        }
        else
        {
            temp = (BTreeNode *)malloc(sizeof(BTreeNode));
            *temp = Top(s);
            Pop(s);
            temp = temp->rchild;
        }
    }
    printf("\n");
}

//循环中序遍历
void CirInOrder(BTreeNode *bt)
{
    BtStack *s = (BtStack *)malloc(sizeof(BtStack));
    Creat(s);
    BTreeNode *temp = (BTreeNode *)malloc(sizeof(BTreeNode));
    temp = bt;
    while (s->top != MAXLENGTH || temp)
    {
        if (temp)
        {
            Push(s, *temp);
            temp = temp->lchild;
        }
        else
        {
            temp = (BTreeNode *)malloc(sizeof(BTreeNode));
            *temp = Top(s);
            Pop(s);
            printf("%d ", Data(temp));
            temp = temp->rchild;
        }
    }
}

//循环后序遍历
void CirPostOrder(BTreeNode *bt)
{
    int flag[MAXLENGTH] = {0}, i = MAXLENGTH - 1;
    BtStack *s = (BtStack *)malloc(sizeof(BtStack));
    Creat(s);
    BTreeNode *temp = (BTreeNode *)malloc(sizeof(BTreeNode));
    temp = bt;
    while (s->top != MAXLENGTH || temp)
    {
        if (temp)
        {
            if (s->top == MAXLENGTH)
            {
                Push(s, *temp);
                flag[i] = 1;
                i--;
                temp = temp->lchild;
            }
            else
            {
                if (flag[i] == 0)
                {
                    Push(s, *temp);
                    flag[i] = 1;
                    i--;
                    temp = temp->lchild;
                }
                else if (flag[i] == 1)
                {
                    temp = temp->rchild;
                    flag[i] = 2;
                    i--;
                }
                else
                {
                    flag[i] = 0;
                    printf("%d ", temp->data);
                    if (JudgeEqul(temp, bt))
                        break;
                    Pop(s);
                    i++;
                    *temp = Top(s);
                }
            }
        }
        else
        {
            temp = (BTreeNode *)malloc(sizeof(BTreeNode));
            *temp = Top(s);
            i++;
        }
    }
}

//层序遍历二叉树
void LatOrder(BTreeNode *bt)
{
    if (IsEmpty(bt))
    {
        BtQue *q = (BtQue *)malloc(sizeof(BtQue));
        CreatQueue(q);
        EnQueue(q, *bt);
        while (QueueEmpty(q))
        {
            BTreeNode temp = GetHead(q);
            printf("%d ", temp.data);
            if (temp.lchild)
                EnQueue(q, *temp.lchild);
            if (temp.rchild)
                EnQueue(q, *temp.rchild);
            DeQueue(q);
        }
        printf("\n");
    }
}

//判断是否完全二叉树
int JudgeCBT(BTreeNode *bt)
{
    char lat[128] = {0};
    JudgeFunc(bt, 1, lat);
    lat[0] = 'T';
    int i = 0;
    int flag1 = 0, flag2 = 1;
    for (i; i < strlen(lat); i++)
    {
        if (flag1 == 0)
        {
            if (lat[i] == 'F')
                flag1 = 1;
        }
        else
        {
            if (lat[i] == 'T')
            {
                flag2 = 0;
                break;
            }
        }
    }
    return flag2;
}

//将二叉树以层序顺序输出到lat中
void JudgeFunc(BTreeNode *bt, int i, char *lat)
{
    if (bt)
    {
        lat[i] = 'T';
        JudgeFunc(bt->lchild, 2 * i, lat);
        JudgeFunc(bt->rchild, 2 * i + 1, lat);
    }
    else
    {
        lat[i] = 'F';
    }
    return;
}

//求二叉树的宽度
void BinWide(BTreeNode *bt, int k)
{
    if (bt)
    {
        bin_wide[k]++;
        if (bin_wide[k] > bin_width)
            bin_width = bin_wide[k];
        BinWide(bt->lchild, k + 1);
        BinWide(bt->rchild, k + 1);
    }
    else
    {
        return;
    }
}