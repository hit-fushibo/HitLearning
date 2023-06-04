#include "Suf.h"

#include "InToSuf.c"
#include "Stack.c"
#include "Suf.c"
#include "fileop.c"

int main(int argc, char *argv[])
{
    char In[MAXLENGTH] = {0}, Suf[MAXLENGTH] = {0};
    int ctn = argc;//判断输入方式
    if (ctn == 2)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("error ");
            exit(7);
        }
        ReadInfix(fp, In);
        puts(In);
    }
    else if (ctn == 1)
    {
        printf("Please enter a legal infix expression:\n");
        gets(In);
    }
    else
    {
        printf("error too much parameter\n");
        exit(6);
    }

    //中缀转后缀
    InToSuf(In, Suf);
    printf("Its corresponding suffix expression is:\n");
    puts(Suf);
    //后缀求值
    float result = evaluation(Suf);
    if (strlen(In) == 0)
        result = 0;
    printf("Its operation result is:");
    printf("%f\n", result);
    
    printf("press any key to exit");
    getchar();
    return 0;
}