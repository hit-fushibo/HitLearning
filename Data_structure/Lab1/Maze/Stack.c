#include"Stack.h"

void ICreat(Istack * s)//创建空栈
{
    s->top=MAXLENGTH;
}
void IMakNull(Istack * s)//将栈置空
{
    s->top=MAXLENGTH-1;
}
int ITop(Istack * s)//返回栈顶值
{
    return s->data[s->top];
}
void IPop(Istack * s)//弹栈
{
    s->data[s->top]=0;
    s->top++;
}
void IPush(Istack * s,int element)//压栈
{
    
    s->top--;
    s->data[s->top]=element;
    
}

void CCreat(Cstack *s)
{
    s->top=MAXLENGTH;
}
void CMakeNull(Cstack *s)
{
    s->top=MAXLENGTH-1;
}
char CTop(Cstack *s)
{
    return s->data[s->top];
}
void CPop(Cstack *s)
{
    s->data[s->top]=0;
    s->top++;
}
void CPush(Cstack *s,char element)
{
    s->top--;
    s->data[s->top]=element;
}