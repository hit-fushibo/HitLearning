#include"Code.h"

#include"Code.c"

int main (void)
{
    CW *Weight;
    int kind=0;
    char input[100];
    gets(input);
    kind=GetWeights(input,&Weight);
    if(kind==1)
    {
        char a[4];
        a[0]=input[0];
        a[1]=' ';
        a[2]='1';
        a[3]='\0';
    }
    HuT *w=CreatNode(Weight,kind);
    HuT *root=CreatHuffman(w,kind);
    char **huffmacode=(char **)malloc(sizeof(char *)*kind);
    for(int i=0;i<kind;i++)
    {
        huffmacode[i]=(char*)malloc(sizeof(char)*(kind));
    }
    char buffer[100]={0};
    HuffmanCode(huffmacode,root,buffer,0);
    for(int i=0;i<kind;i++)
    {
        printf("%s\n",huffmacode[i]);
    }
    return 0;
}