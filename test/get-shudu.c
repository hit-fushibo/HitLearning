#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    FILE * fp=fopen("D:\\code\\test\\shudu.txt","r");
    if(fp==NULL)
        perror("error1");
    FILE * result=fopen("D:\\code\\test\\result.txt","w");
    if(result==NULL)
        perror("error2");
    char Buffer[11]={0};
    if(fp==NULL||result==NULL)
    {
        if(fp==NULL)
            printf("can not open file\n");
        if(result==NULL)
            printf("can not open file 1\n");
        exit(1);
    }
    int x=0,y=0;
    while (fgets(Buffer,100,fp))
    {
        printf("%d %s\n",x,Buffer);
        for(y=0;y<10;y++)
        {
            if(Buffer[y]>='1'&&Buffer[y]<='9')
            {
                fprintf(result,"%d %d %c\n",x,y,Buffer[y]);
                perror("");
                printf("%d %d %c\n",x,y,Buffer[y]);
            }
        }
        x++;
    }
    fprintf(result,"%d %d %d\n",-1,-1,-1);
    perror("");
    fclose(fp);
    fclose(result);
    return 0;

}