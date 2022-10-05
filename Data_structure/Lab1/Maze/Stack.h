#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 50

//用于储存节点，data保存3个数据，坐标x，y和方向dir
//dir 1 上方节点 2 右方节点 3 下方节点 4 左方节点
typedef struct intstack
{
    int top;
    int data[MAXLENGTH][3];
} stack;

void Creat(stack *s);//创建空栈
void MakNull(stack *s);//将栈置空
int Top(stack *s,int i);//返回栈顶值
void Pop(stack *s);//弹栈
void Push(stack *s, int element1,int element2,int element3);//压栈
int JudgeEmpty(stack *s);//判断栈是否空空返回0,否则返回1

#endif