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
                CPush(s,'+');
            }
            else if(Judge('+',CTop(s))==1)
            {
                suf[j]='+';
                j++;
            }
            else if(Judge('+',CTop(s))==0)
            {
                CPush(s,'+');
            }
            else
            {
                suf[j]=CTop(s);
                CPop(s);CPush(s,'+');
                j++;
            }
            break;
        case '-':
            if(s->top==MAXLENGTH)
            {
                CPush(s,'-');
            }
            else if(Judge('-',CTop(s))==1)
            {
                suf[j]='-';
                j++;
            }
            else if(Judge('-',CTop(s))==0)
            {
                CPush(s,'-');
            }
            else
            {
                suf[j]=CTop(s);
                CPop(s);CPush(s,'-');
                j++;
            }
            break;
        case '*':
            if(s->top==MAXLENGTH)
            {
                CPush(s,'*');
            }
            else if(Judge('*',CTop(s))==1)
            {
                suf[j]='*';
                j++;
            }
            else if(Judge('*',CTop(s))==0)
            {
                CPush(s,'*');
            }
            else
            {
                suf[j]=CTop(s);
                CPop(s);CPush(s,'*');
                j++;
            }
            break;
        case '/':
            if(s->top==MAXLENGTH)
            {
                CPush(s,'/');
            }
            else if(Judge('/',CTop(s))==1)
            {
                suf[j]='/';
                j++;
            }
            else if(Judge('/',CTop(s))==0)
            {
                CPush(s,'/');
            }
            else
            {
                suf[j]=CTop(s);
                CPop(s);CPush(s,'/');
                j++;
            }
            break;
        case '(':
            CPush(s,'(');
            break;
        case ')':
            for(;CTop(s)!='(';j++)
            {
                suf[j]=CTop(s);
                CPop(s);
            }
            CPop(s);
            break;
        default:
            suf[j]=In[i];j++;
            break;
        }
    }
    for(;s->top!=MAXLENGTH;j++)
    {
        suf[j]=CTop(s);
        CPop(s);
    }
    suf[++j]='\0';
}