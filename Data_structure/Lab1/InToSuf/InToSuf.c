#include "InToSuf.h"

//判断优先级 直接进栈返回0，弹栈再进栈返回-1
int Judge(char a, char b)
{
    switch (a)
    {
    case '+':
        if (b == '(')
            return 0;
        else
            return -1;
        break;
    case '-':
        if (b == '(')
            return 0;
        else
            return -1;
        break;
    case '*':
        if (b == '+' || b == '-' || b == '(')
            return 0;
        else
            return -1;
        break;
    case '/':
        if (b == '+' || b == '-' || b == '(')
            return 0;
        else
            return -1;
        break;
    default:
        printf("error:illegal operator\n");
        exit(8);
        break;
    }
}

//中缀表达式转后缀表达式
void InToSuf(char In[], char suf[])
{
    Cstack *s = (Cstack *)malloc(sizeof(Cstack));
    CCreat(s);
    int i, j;
    for (i = 0, j = 0; In[i] != '\0'; i++)
    {
        switch (In[i])
        {
        case '+':
            if (s->top == MAXLENGTH) //栈空
            {
                printf("meet +,stack is empty,push +\n");
                CPush(s, '+');
                CShowStack(s);
            }
            else if (Judge('+', CTop(s)) == -1) //弹出栈顶再压栈
            {
                while (Judge('+', CTop(s)) == -1)
                {
                    printf("meet +,The top element of the stack is%c,output top element %c,push +\n", CTop(s), CTop(s));
                    suf[j] = CTop(s);
                    CPop(s);
                    CShowStack(s);
                    j++;
                    suf[j] = ' ';
                    j++;
                    if (s->top == MAXLENGTH)
                        break;
                }
                CPush(s, '+');
            }
            else if (Judge('+', CTop(s)) == 0) //直接入栈
            {
                printf("meet +,The top element of the stack is%c,push +\n", CTop(s));
                CPush(s, '+');
                CShowStack(s);
            }
            break;
        case '-':
            printf("meet -,");
            if (s->top == MAXLENGTH) //栈空
            {
                printf("stack is empty,push -\n");
                CPush(s, '-');
                CShowStack(s);
            }
            else if (Judge('-', CTop(s)) == -1) //弹出栈顶再压栈
            {
                while (Judge('-', CTop(s)) == -1)
                {
                    printf("The top element of the stack is%c,output top element%c,push -\n", CTop(s), CTop(s));
                    suf[j] = CTop(s);
                    CPop(s);
                    CShowStack(s);
                    j++;
                    suf[j] = ' ';
                    j++;
                    if (s->top == MAXLENGTH)
                        break;
                }
                CPush(s, '-');
            }
            else if (Judge('-', CTop(s)) == 0) //直接入栈
            {
                printf("The top element of the stack is%c,push -\n", CTop(s));
                CPush(s, '-');
                CShowStack(s);
            }
            break;
        case '*':
            printf("meet *,");
            if (s->top == MAXLENGTH) //栈空
            {
                printf("stack is empty,push *\n");
                CPush(s, '*');
                CShowStack(s);
            }
            else if (Judge('*', CTop(s)) == -1) //弹出栈顶再压栈
            {
                while (Judge('*', CTop(s)) == -1)
                {
                    printf("The top element of the stack is%c,output top element%c,push *\n", CTop(s), CTop(s));
                    suf[j] = CTop(s);
                    CPop(s);
                    CShowStack(s);
                    j++;
                    suf[j] = ' ';
                    j++;
                    if (s->top == MAXLENGTH)
                        break;
                }
                CPush(s, '*');
            }
            else if (Judge('*', CTop(s)) == 0) //直接入栈
            {
                printf("The top element of the stack is%c,push *\n", CTop(s));
                CPush(s, '*');
                CShowStack(s);
            }
            break;
        case '/':
            printf("meet /,");
            if (s->top == MAXLENGTH) //栈空
            {
                printf("stack is empty,push /\n");
                CPush(s, '/');
                CShowStack(s);
            }
            else if (Judge('/', CTop(s)) == -1) //弹出栈顶再压栈
            {
                while (Judge('/', CTop(s)) == -1)
                {
                    printf("The top element of the stack is%c,output top element%c,push /\n", CTop(s), CTop(s));
                    suf[j] = CTop(s);
                    CPop(s);
                    CShowStack(s);
                    j++;
                    suf[j] = ' ';
                    j++;
                    if (s->top == MAXLENGTH)
                        break;
                }
                CPush(s, '/');
            }
            else if (Judge('/', CTop(s)) == 0) //直接入栈
            {
                printf("The top element of the stack is%c,push /\n", CTop(s));
                CPush(s, '/');
                CShowStack(s);
            }
            break;
        case '(':
            printf("meet (,push (\n");
            CPush(s, '(');
            CShowStack(s);
            break;
        case ')':
            printf("meet ),output stack element until meet (\n");
            for (; CTop(s) != '('; j++) //依次弹栈直到遇到(
            {
                suf[j] = CTop(s);
                j++;
                suf[j] = ' ';
                CPop(s);
            }
            CPop(s);
            CShowStack(s);
            break;
        default: //遇见数字
            printf("meet number,output\n");
            for (In[i]; In[i] >= '0' && In[i] <= '9'; i++)
                suf[j++] = In[i];
            suf[j] = ' ';
            j++;
            i--;
            break;
        }
    }
    printf("Output the remaining elements in the stack\n"); //输出剩余元素
    for (; s->top != MAXLENGTH; j++)
    {
        suf[j] = CTop(s);
        j++;
        suf[j] = ' ';
        CPop(s);
    }
    suf[++j] = '\0';
}