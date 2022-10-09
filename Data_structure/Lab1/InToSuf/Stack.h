#ifndef STACK_H
#define STACK_H

#include "fileop.h"

#define MAXLENGTH 50

typedef struct intstack
{
    int top;
    float data[MAXLENGTH];
} Istack;

typedef struct charstack
{
    int top;
    char data[MAXLENGTH];
} Cstack;

void ICreat(Istack *s);               //创建空栈
void IMakNull(Istack *s);             //将栈置空
float ITop(Istack *s);                //返回栈顶值
void IPop(Istack *s);                 //弹栈
void IPush(Istack *s, float element); //压栈
void IShowStack(Istack *s);           //显示栈内容，从栈底开始

void CCreat(Cstack *s);              //创建空栈
void CMakeNull(Cstack *s);           //将栈置空
char CTop(Cstack *s);                //返回栈顶值
void CPop(Cstack *s);                //弹栈
void CPush(Cstack *s, char element); //压栈
void CShowStack(Cstack *s);          //显示栈内容，从栈底开始

#endif