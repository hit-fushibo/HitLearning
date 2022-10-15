#include"Code.h"
#include"Decode.h"
#include"Fileop.h"

#include"Code.c"
#include"Decode.c"
#include"Fileop.c"

int main (void)
{
    CW *Weight;
    int kind=0;
    //char input[100];
    //gets(input);
    char *input;
    GetData(&input);
    kind=GetWeights(input,&Weight);
    if(kind==1)
    {
        char **a=(char **)malloc(sizeof(char *));
        for(int i=0;i<kind;i++)
        {
            a[i]=(char*)malloc(sizeof(char)*4);
        }
        a[0][0]=input[0];
        a[0][1]=' ';
        a[0][2]='1';
        a[0][3]='\0';
        OutputHufcode(a,kind);
        int len=strlen(input);
        char *code=(char *)malloc(sizeof(char)*len);
        CodeString(input,a,code);
        OutputCode(code);
        char *Dedata=(char*)malloc(sizeof(char)*100);
        Decode(Dedata,a,code);
        OutputData(Dedata);
    }
    else
    {
        HuT *w=CreatNode(Weight,kind);
        HuT *root=CreatHuffman(w,kind);
        char **huffmacode=(char **)malloc(sizeof(char *)*kind);
        for(int i=0;i<kind;i++)
        {
            huffmacode[i]=(char*)malloc(sizeof(char)*(kind));
        }
        char buffer[100]={0};
        HuffmanCode(huffmacode,root,buffer,0);
        OutputHufcode(huffmacode,kind);
        int len=strlen(input);
        char *code=(char *)malloc(sizeof(char)*len*strlen(huffmacode[kind-1]));
        CodeString(input,huffmacode,code);
        OutputCode(code);
        char *Dedata=(char*)malloc(sizeof(char)*10000);
        Decode(Dedata,huffmacode,code);
        OutputData(Dedata);
        //printf("%s\n",code);
    }

    
    return 0;
}