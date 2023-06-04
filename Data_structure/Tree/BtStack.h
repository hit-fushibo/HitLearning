#ifndef BTSTACK_H
#define BTSTACK_H

#include "Definition.h"

void Creat(BtStack *s);                   //创建空栈
void MakeNull(BtStack *s);                //将栈置空
BTreeNode Top(BtStack *s);                //返回栈顶值
void Pop(BtStack *s);                     //弹栈
void Push(BtStack *s, BTreeNode element); //压栈

#endif