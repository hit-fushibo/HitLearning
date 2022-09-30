#ifndef STACK_H
#define STACK_H

#include "fileop.h"

#define MAXLENGTH 50

typedef struct intstack
{
    int top;
    int data[MAXLENGTH];
} Istack;

typedef struct charstack
{
    int top;
    char data[MAXLENGTH];
}Cstack;


void ICreat(Istack *s);             //创建空栈
void IMakNull(Istack *s);           //将栈置空
int ITop(Istack *s);                //返回栈顶值
void IPop(Istack *s);               //弹栈
void IPush(Istack *s, int element); //压栈

void CCreat(Cstack *s);
void CMakeNull(Cstack *s);
char CTop(Cstack *s);
void CPop(Cstack *s);
void CPush(Cstack *s,char element);

#endif