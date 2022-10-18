#ifndef BTQUE_H
#define BTQUE_H

#include "BtStack.h"

void CreatQueue(BtQue *q);                 //创建队列
void ClearQueue(BtQue *q);                 //清空队列
int QueueEmpty(BtQue *q);                  //判断队列是否为空
int QueueLength(BtQue *q);                 //队列大小
BTreeNode GetHead(BtQue *q);               //队头元素
void EnQueue(BtQue *q, BTreeNode element); //入队
void DeQueue(BtQue *q);                    //出队

#endif