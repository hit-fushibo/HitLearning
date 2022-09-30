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
            break;
        case '-':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y-x);
            break;
        case '*':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y*x);
            break;
        case '/':
            x=ITop(s);
            IPop(s);
            y=ITop(s);
            IPop(s);
            IPush(s,y/x);
            break;
        default:
            IPush(s,*p-'0');
            break;
        }
    }
    x=ITop(s);
    IPop(s);
    return x;
}