#include "BtQue.h"

//创建队列
void CreatQueue(BtQue *q)
{
    q->l = -1;
}

//清空队列
void ClearQueue(BtQue *q)
{
    q->l = -1;
}

//判断队列是否为空
int QueueEmpty(BtQue *q)
{
    if (q->l >= 0 && q->l < MAXLENGTH)
        return 1;
    else
        return 0;
}

//队列大小
int QueueLength(BtQue *q)
{
    return q->l + 1;
}

//队头元素
BTreeNode GetHead(BtQue *q)
{
    if (QueueEmpty(q))
        return q->data[0];
    else
    {
        printf("queue get head error\n");
        exit(8);
    }
}

//入队
void EnQueue(BtQue *q, BTreeNode element)
{
    if (q->l < MAXLENGTH - 1)
    {
        q->l++;
        q->data[q->l] = element;
    }
    else
    {
        printf("queue enqueue error\n");
        exit(8);
    }
}

//出队
void DeQueue(BtQue *q)
{
    if (q->l >= 0)
    {
        for (int i = 0; i < q->l; i++)
        {
            q->data[i] = q->data[i + 1];
        }
        q->l--;
    }
    else
    {
        printf("queue dequeue error\n");
        exit(8);
    }
}