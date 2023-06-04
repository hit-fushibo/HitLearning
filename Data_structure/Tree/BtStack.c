#include "BtStack.h"

//创建空栈
void Creat(BtStack *s)
{
    s->top = MAXLENGTH;
}

//将栈置空
void MakeNull(BtStack *s)
{
    s->top = MAXLENGTH;
}

//返回栈顶值
BTreeNode Top(BtStack *s)
{
    if (s->top != MAXLENGTH)
        return s->data[s->top];
    else
    {
        printf("stack top error");
        exit(8);
    }
}

//弹栈
void Pop(BtStack *s)
{
    if (s->top != MAXLENGTH)
        s->top++;
    else
    {
        printf("stack pop error\n");
        exit(8);
    }
}

//压栈
void Push(BtStack *s, BTreeNode element)
{
    if (s->top > 0)
    {
        s->top--;
        s->data[s->top] = element;
    }
    else
    {
        printf("stack push error\n");
        exit(8);
    }
}