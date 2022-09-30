#include"Stack.h"

void Creat(stack * s)//创建空栈
{
    s->top=MAXLENGTH;
}
void MakNull(stack * s)//将栈置空
{
    s->top=MAXLENGTH-1;
}
int Top(stack * s)//返回栈顶值
{
    return s->data[s->top];
}
void Pop(stack * s)//弹栈
{
    s->data[s->top]=0;
    s->top++;
}
void Push(stack * s,int element)//压栈
{
    
    s->top--;
    s->data[s->top]=element;
    
}
