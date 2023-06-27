#include"Que.h"


//创建队列
void CreatQueue(Q * q)
{
    q->l=-1;
}

//清空队列
void ClearQurur(Q * q)
{
    q->l=-1;
}

//判断队列是否为空
int QueueEmpty(Q * q)
{
    if(q->l>=0)
    return 1;
    else
    return 0;
}

//队列大小
int QueueLength(Q * q)
{
    return q->l+1;
}

//队头元素
int QueueHead(Q * q)
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
void EnQueue(Q * q,int element)
{
    if (q->l < MAX_VERTES - 1)
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
void DeQueue(Q * q)
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




//创建队列
void TCreatQueue(TQ * q)
{
    q->l=-1;
}

//清空队列
void TClearQurur(TQ * q)
{
    q->l=-1;
}

//判断队列是否为空
int TQueueEmpty(TQ * q)
{
    if(q->l>=0)
    return 1;
    else
    return 0;
}

//队列大小
int TQueueLength(TQ * q)
{
    return q->l;
}

//队头元素
T* TQueueHead(TQ * q)
{
    if (TQueueEmpty(q))
        return q->data[0];
    else
    {
        printf("queue get head error\n");
        exit(8);
    }
}

//入队
void TEnQueue(TQ * q,T* element)
{
    if (q->l < MAX_VERTES - 1)
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
void TDeQueue(TQ * q)
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