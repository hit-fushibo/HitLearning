#include "Suf.h"

//后缀表达式求值
float evaluation(char *suf)
{
    Istack *s = (Istack *)malloc(sizeof(Istack));
    char *p = suf;
    float x = 0, y = 0;
    ICreat(s);
    for (; *p != '\0'; p++)
    {
        if (*p == '\0')
            break;
        switch (*p)
        {
        case '+':
            x = ITop(s);
            IPop(s);
            y = ITop(s);
            IPop(s);
            IPush(s, y + x); //注意运算顺序
            printf("meet +,pop two number %f %f,then push %f+%f\n", x, y, y, x);
            IShowStack(s);
            p++;
            break;
        case '-':
            x = ITop(s);
            IPop(s);
            y = ITop(s);
            IPop(s);
            IPush(s, y - x); //注意运算顺序
            printf("meet -,pop two number %f %f,then push %f-%f\n", x, y, y, x);
            IShowStack(s);
            p++;
            break;
        case '*':
            x = ITop(s);
            IPop(s);
            y = ITop(s);
            IPop(s);
            IPush(s, y * x); //注意运算顺序
            printf("meet *,pop two number %f %f,then push %f*%f\n", x, y, y, x);
            IShowStack(s);
            p++;
            break;
        case '/':
            x = ITop(s);
            IPop(s);
            y = ITop(s);
            IPop(s);
            IPush(s, y / x); //注意运算顺序
            printf("meet /,pop two number %f %f,then push %f/%f\n", x, y, y, x);
            IShowStack(s);
            p++;
            break;
        default:
            printf("meet number,push\n");
            x = strtof(p, &p); //获取数字函数
            printf("%f \n", x);
            IPush(s, x);
            IShowStack(s);
            break;
        }
    }
    x = ITop(s);
    IPop(s);
    return x;
}