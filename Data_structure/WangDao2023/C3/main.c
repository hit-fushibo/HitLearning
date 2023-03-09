#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<math.h>


#define MAXSIZE 100

typedef struct Stack
{
    int top;
    int data[MAXSIZE];
}S;
