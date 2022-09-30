#ifndef INTOSUF_H
#define INTOSUF_H

#include"stack.h"

void InToSuf(char In[],char suf[]);
int Judge(char a,char b);//判断优先级 直接输出返回1，直接进栈返回0，弹栈再进栈返回-1


#endif