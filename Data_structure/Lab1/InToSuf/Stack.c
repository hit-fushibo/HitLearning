#include "Stack.h"

//创建空栈
void ICreat(Istack *s)
{
    s->top = MAXLENGTH;
}

//将栈置空
void IMakNull(Istack *s)
{
    s->top = MAXLENGTH - 1;
}

//返回栈顶值
float ITop(Istack *s)
{
    return s->data[s->top];
}

//弹栈
void IPop(Istack *s)
{
    s->data[s->top] = 0;
    s->top++;
}

//压栈
void IPush(Istack *s, float element)
{

    s->top--;
    s->data[s->top] = element;
}

//显示栈内容，从栈底开始
void IShowStack(Istack *s)
{
    int i = MAXLENGTH - 1;
    for (i; i >= s->top; i--)
    {
        printf("%f ", s->data[i]);
    }
    printf("\n");
}

//创建空栈
void CCreat(Cstack *s)
{
    s->top = MAXLENGTH;
}

//将栈置空
void CMakeNull(Cstack *s)
{
    s->top = MAXLENGTH - 1;
}

//返回栈顶值
char CTop(Cstack *s)
{
    return s->data[s->top];
}

//弹栈
void CPop(Cstack *s)
{
    s->data[s->top] = 0;
    s->top++;
}

//压栈
void CPush(Cstack *s, char element)
{
    s->top--;
    s->data[s->top] = element;
}

//显示栈内容，从栈底开始
void CShowStack(Cstack *s)
{
    int i = MAXLENGTH - 1;
    for (; i >= s->top; i--)
    {
        printf("%c ", s->data[i]);
    }
    printf("\n");
}