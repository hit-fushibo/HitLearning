#include"Stack.h"

//创建空栈
void Creat(S *s)
{
    s->top=-1;
}

//将栈置空
void MakNull(S *s)
{
    s->top=-1;
}

//返回栈顶值
int Top(S *s)
{
    if(s->top!=-1)
    {
        return s->data[s->top];
    }
    else
    {
        printf("ERROR Top:stack is empty!\n");
        exit(8);
    }
}

//弹栈
void Pop(S *s)
{
    if(s->top!=-1)
    {
        s->top--;
    }
    else
    {
        printf("ERROR Top:stack is empty!\n");
        exit(8);
    }
}

//压栈
void Push(S *s, int element)
{
    if(s->top<MAX_VERTES-1)
    {
        s->data[++s->top]=element;
    }
    else
    {
        printf("ERROR Push:no more space\n ");
        exit(8);
    }
}


void TCreat(TS *s)
{
    s->top=-1;
}


void TMakeNull(TS *s)
{
    s->top=-1;
}


T* TTop(TS *s)
{
    if(s->top!=-1)
    {
        return s->data[s->top];
    }
    else
    {
        printf("ERROR Top:stack is empty!\n");
        exit(8);
    }
}


void TPop(TS* s)
{
    if(s->top!=-1)
    {
        s->top--;
    }
    else
    {
        printf("ERROR Top:stack is empty!\n");
        exit(8);
    }
}


void TPush(TS* s,T* element)
{
    if(s->top<MAX_VERTES-1)
    {
        s->data[++s->top]=element;
    }
    else
    {
        printf("ERROR Push:no more space\n ");
        exit(8);
    }
}
