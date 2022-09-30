#include"Suf.h"

#include"InToSuf.c"
#include"Stack.c"
#include"Suf.c"
#include"fileop.c"

int main(void)
{
    char In[MAXLENGTH]={0},Suf[MAXLENGTH]={0};
    FILE *fp=fopen("in.txt","r");
    if(fp==NULL)
    {
        perror("error ");
        exit(7);
    }
    ReadInfix(fp,In);
    puts(In);
    //printf("Please enter a legal infix expression:\n");
    //gets(In);
    InToSuf(In,Suf);
    printf("Its corresponding suffix expression is:\n");
    puts(Suf);
    int result=evaluation(Suf);
    printf("Its operation result is:");
    printf("%d\n",result);
    printf("press any key to exit");
    getchar();
    return 0;
}