#include"InToSuf.h"

//判断优先级 直接输出返回1，直接进栈返回0，弹栈再进栈返回-1
int Judge(char a,char b)
{
    switch (a)
    {
    case '+':
        if(b=='('||b=='+'||b=='-')
        return 0;
        else
        return -1;
        break;
    case '-':
        if(b=='('||b=='+'||b=='-')
        return 0;
        else
        return -1;
        break;
    case '*':
        if(b=='+'||b=='-')
        return 0;
        else if(b=='(')
        return 0;
        else
        return 1;
        break;
    case '/':
        if(b=='+'||b=='-')
        return 0;
        else if(b=='(')
        return 0;
        else
        return 1;
        break;
    default:
        printf("error:illegal operator\n");
        exit(8);
        break;
    }
}
void InToSuf(char In[],char suf[])
{
    Cstack *s=(Cstack*)malloc(sizeof(Cstack));
    CCreat(s);
    int i,j;
    for(i=0,j=0;In[i]!='\0';i++)
    {
        switch (In[i])
        {
        case '+':
            if(s->top==MAXLENGTH)
            {
                printf("meet +,stack is empty,push +\n");
                CPush(s,'+');
                CShowStack(s);
            }
            else if(Judge('+',CTop(s))==1)
            {
                printf("meet +,The top element of the stack is%c,output +\n",CTop(s));
                suf[j]='+';
                j++;
            }
            else if(Judge('+',CTop(s))==0)
            {
                printf("meet +,The top element of the stack is%c,push +\n",CTop(s));
                CPush(s,'+');
                CShowStack(s);
            }
            else
            {
                printf("meet +,The top element of the stack is%c,output top element %c,push +\n",CTop(s),CTop(s));
                suf[j]=CTop(s);
                CPop(s);CPush(s,'+');
                CShowStack(s);
                j++;
            }
            break;
        case '-':
            printf("meet -,");
            if(s->top==MAXLENGTH)
            {
                printf("stack is empty,push -\n");
                CPush(s,'-');
                CShowStack(s);
            }
            else if(Judge('-',CTop(s))==1)
            {
                printf("The top element of the stack is%c,output -\n",CTop(s));
                suf[j]='-';
                j++;
            }
            else if(Judge('-',CTop(s))==0)
            {
                printf("The top element of the stack is%c,push -\n",CTop(s));
                CPush(s,'-');
                CShowStack(s);
            }
            else
            {
                printf("The top element of the stack is%c,output top element%c,push -\n",CTop(s),CTop(s));
                suf[j]=CTop(s);
                CPop(s);CPush(s,'-');
                CShowStack(s);
                j++;
            }
            break;
        case '*':
            printf("meet *,");
            if(s->top==MAXLENGTH)
            {
                printf("stack is empty,push *\n");
                CPush(s,'*');
                CShowStack(s);
            }
            else if(Judge('*',CTop(s))==1)
            {
                printf("The top element of the stack is%c,output *\n",CTop(s));
                suf[j]='*';
                j++;
            }
            else if(Judge('*',CTop(s))==0)
            {
                printf("The top element of the stack is%c,push *\n",CTop(s));
                CPush(s,'*');
                CShowStack(s);
            }
            else
            {
                printf("The top element of the stack is%c,output top element%c,push *\n",CTop(s),CTop(s));
                suf[j]=CTop(s);
                CPop(s);CPush(s,'*');
                CShowStack(s);
                j++;
            }
            break;
        case '/':
            printf("meet /,");
            if(s->top==MAXLENGTH)
            {
                printf("stack is empty,push /\n");
                CPush(s,'/');
                CShowStack(s);
            }
            else if(Judge('/',CTop(s))==1)
            {
                printf("The top element of the stack is%c,output /\n",CTop(s));
                suf[j]='/';
                j++;
            }
            else if(Judge('/',CTop(s))==0)
            {
                printf("The top element of the stack is%c,push /\n",CTop(s));
                CPush(s,'/');
                CShowStack(s);
            }
            else
            {
                printf("The top element of the stack is%c,output top element%c,push /\n",CTop(s),CTop(s));
                suf[j]=CTop(s);
                CPop(s);CPush(s,'/');
                CShowStack(s);
                j++;
            }
            break;
        case '(':
            printf("meet (,push (\n");
            CPush(s,'(');
            CShowStack(s);
            break;
        case ')':
            printf("meet ),output stack element until meet (\n");
            for(;CTop(s)!='(';j++)
            {
                suf[j]=CTop(s);
                CPop(s);
            }
            CPop(s);
            CShowStack(s);
            break;
        default:
            printf("meet number,output\n");
            suf[j]=In[i];j++;
            break;
        }
    }
    printf("Output the remaining elements in the stack\n");
    for(;s->top!=MAXLENGTH;j++)
    {
        suf[j]=CTop(s);
        CPop(s);
    }
    suf[++j]='\0';
}