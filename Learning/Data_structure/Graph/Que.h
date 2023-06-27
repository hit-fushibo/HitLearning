#ifndef QUE_H
#define QUE_H

#include"Define.h"

void CreatQueue(Q * q);//创建队列
void ClearQurur(Q * q);//清空队列
int QueueEmpty(Q * q);//判断队列是否为空
int QueueLength(Q * q);//队列大小
int QueueHead(Q * q);//队头元素
void EnQueue(Q * q,int element);//入队
void DeQueue(Q * q);//出队

void TCreatQueue(TQ * q);//创建队列
void TClearQurur(TQ * q);//清空队列
int TQueueEmpty(TQ * q);//判断队列是否为空
int TQueueLength(TQ * q);//队列大小
T* TQueueHead(TQ * q);//队头元素
void TEnQueue(TQ * q,T* element);//入队
void TDeQueue(TQ * q);//出队

#endif