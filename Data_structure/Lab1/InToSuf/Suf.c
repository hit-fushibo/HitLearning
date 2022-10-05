#include"Suf.h"

int evaluation(char * suf)
{
    Istack *s=(Istack*)malloc(sizeof(Istack));
    char *p=suf;
    int x,y;
    ICreat(s);
    for(;*p!='\0';p++)
    {
        if(*p=='\0')break;
        switch (*p)
        {
        case '+':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y+x);
            printf("meet +,pop two number %d %d,then push %d+%d\n",x,y,y,x);
            IShowStack(s);
            break;
        case '-':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y-x);
            printf("meet -,pop two number %d %d,then push %d-%d\n",x,y,y,x);
            IShowStack(s);
            break;
        case '*':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y*x);
            printf("meet *,pop two number %d %d,then push %d*%d\n",x,y,y,x);
            IShowStack(s);
            break;
        case '/':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y/x);
            printf("meet /,pop two number %d %d,then push %d/%d\n",x,y,y,x);
            IShowStack(s);
            break;
        default:
            printf("meet number,push\n");
            IPush(s,*p-'0');
            IShowStack(s);
            break;
        }
    }
    x=ITop(s);
    IPop(s);
    return x;
}