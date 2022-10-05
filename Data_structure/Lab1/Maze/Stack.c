#include"Stack.h"

void Creat(stack * s)//创建空栈
{
    s->top=MAXLENGTH;
}
void MakNull(stack * s)//将栈置空
{
    s->top=MAXLENGTH-1;
}
int Top(stack * s,int i)//返回栈顶值
{
    return s->data[s->top][i];
}
void Pop(stack * s)//弹栈
{
    s->top++;
}
void Push(stack *s, int element1,int element2,int element3)//压栈
{
    
    s->top--;
    s->data[s->top][0]=element1;
    s->data[s->top][1]=element2;
    s->data[s->top][2]=element3;
    
}

//判断栈是否空空返回0,否则返回1
int JudgeEmpty(stack *s)
{
    if(s->top==MAXLENGTH)
    return 0;
    else
    return 1;
}         
