#include"Fileop.h"

//将译码结果写入文件
void OutputData(char *data)
{
    FILE *fp=fopen("decode.txt","w");
    if(fp==NULL)
    {
        printf("data input error:can't opne file\n");
        exit(8);
    }
    for(int i=0;data[i]!='\0';i++)
    {
        putc(data[i],fp);
    }
    fclose(fp);
}

//将编码结果写入文件
void OutputCode(char *code)
{
    FILE *fp=fopen("code.txt","w");
    if(fp==NULL)
    {
        printf("code input error:can't opne file\n");
        exit(8);
    }
    for(int i=0;code[i]!='\0';i++)
    {
        putc(code[i],fp);
    }
    fclose(fp);
}

//从文件读入输入
void GetData(char **data)
{
    FILE *fp=fopen("data.txt","r");
    if(fp==NULL)
    {
        printf("data get error:can't opne file\n");
        exit(8);
    }
    int len,i=0;
    fseek(fp,0,2);
    len=ftell(fp);
    rewind(fp);
    *data=(char *)malloc(sizeof(char)*(len+1));
    char temp=getc(fp);
    while (temp!=EOF)
    {
        (*data)[i]=temp;
        temp=getc(fp);
        i++;
        
    }
    (*data)[i]='\0';
    fclose(fp);
}

//将哈夫曼码对照表输出到文件
void OutputHufcode(char **hufcode,int kind)
{
    FILE *fp=fopen("hufcode.txt","w");
    if(fp==NULL)
    {
        printf("code output error:can't opne file\n");
        exit(8);
    }
    for(int i=0;i<kind;i++)
    {
        int temp=hufcode[i][0];
        int buf[3]={0};
        buf[2]=temp%10;
        temp/=10;
        buf[1]=temp%10;
        temp/=10;
        buf[0]=temp%10;
        putc(buf[0]+'0',fp);
        putc(buf[1]+'0',fp);
        putc(buf[2]+'0',fp);
        for(int j=1;hufcode[i][j]!='\0';j++)
        {
            putc(hufcode[i][j],fp);
        }
        if(i!=kind-1)
        putc('\n',fp);
    }
    fclose(fp);
}

//从文件读入哈夫曼码对照表
void GetHufcode(char **hufcode)
{
    char buffer[10000]={0};
    FILE *fp=fopen("hufcode.txt","r");
    if(fp==NULL)
    {
        printf("code get error:can't opne file\n");
        exit(8);
    }
    int i=0,j=0;
    while (fgets(buffer,100,fp))
    {
        int temp=atoi(buffer);
        hufcode[i][0]=temp;
        for(j=3;buffer[j]!='\n';j++)
        {
            hufcode[i][j-2]=buffer[j];
        }
        hufcode[i][j-2]='\0';
        i++;
    }
    fclose(fp);
}