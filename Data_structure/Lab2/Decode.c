#include"Decode.h"

//匹配当前未处理编码，返回匹配之后的编码指针位置和字符
char *FindCode(char *code,char **Hufcode,int *location)
{
    int i=0,j=0,k=0;
    while (1)
    {
        j=2;k=0;
        while (Hufcode[i][j]!='\0'&&code[k]==Hufcode[i][j])
        {
            j++;k++;
        }
        if(Hufcode[i][j]=='\0')break;
        i++;
    }
    *location=i;
    return code+k;
}

//根据hufcode解码code并存储在data里
void Decode(char *data,char **Hufcode,char *code)
{
    char *p=code;
    int i=0,j=0;
    while(*p!='\0')
    {
        p=FindCode(p,Hufcode,&i);
        data[j]=*Hufcode[i];
        j++;
    }
    data[j]='\0';
}