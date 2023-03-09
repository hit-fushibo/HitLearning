#ifndef STACK_H
#define STACK_H

#include"Define.h"

void Creat(S *s);               //创建空栈
void MakNull(S *s);             //将栈置空
int Top(S *s);                //返回栈顶值
void Pop(S *s);                 //弹栈
void Push(S *s, int element); //压栈

void TCreat(TS *s);
void TMakeNull(TS *s);
T* TTop(TS *s);
void TPop(TS* s);
void TPush(TS* s, T* element);

#endif