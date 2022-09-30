#ifndef STACK_H
#define STACK_H

#include "fileop.h"

#define MAXLENGTH 50

typedef struct intstack
{
    int top;
    int data[MAXLENGTH];
} stack;

void Creat(stack *s);             //创建空栈
void MakNull(stack *s);           //将栈置空
int Top(stack *s);                //返回栈顶值
void Pop(stack *s);               //弹栈
void Push(stack *s, int element); //压栈

#endif