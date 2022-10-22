#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void Initimg(int img[1920][1080]);
void Origin(int img[1920][1080]);
void Cpu_8(int img[1920][1080]);
void Cpu_4(int img [1920][1080]);
void Dusty(int img[1920][1080]);
void Cache_row(int img[1920][1080]);

int img[1920][1080];

int main (void)
{
    
    Initimg(img);
    int t1,t2;
    //t1=clock();
    //Origin(img);
    //t2=clock();
    //printf("Unoptimized time:%f s\n",(t2-t1)/((double)CLOCKS_PER_SEC));
    //t1=clock();
    //Cpu_4(img);
    //t2=clock();
    //printf("4 Loop unfolds time:%f s\n",(t2-t1)/((double)CLOCKS_PER_SEC));
    //t1=clock();
    //Cpu_8(img);
    //t2=clock();
    //printf("8 Loop unfolds time:%f s\n",(t2-t1)/((double)CLOCKS_PER_SEC));
    t1=clock();
    Cache_row(img);
    t2=clock();
    printf("Chunk by row time:%f s\n",(t2-t1)/((double)CLOCKS_PER_SEC));
    return 0;
}

void Initimg(int img[1920][1080])
{
    for(int i=0;i<1920;i++)
    {
        for(int j=0;j<1080;j++)
        {
            img[i][j]=rand()%64;
        }
    }
}


void Dusty(int img[1920][1080])
{
    int i,j;
    int buffer[1080]={0};
    for(i=0;i<1080;i++)
    {
        buffer[i]= img[i][0];
    }
    for(j=0;j<1079;j++)
    {
        
    }
}

void Origin(int img[1920][1080])
{
    int i,j;
    int buffer[1080]={0};
    for(i=0;i<1080;i++)
    {
        buffer[i]= img[0][i];
    }
    for(i=1;i<1919;i++)
    {
        buffer[0]=img[i][0];
        buffer[1079]=img[i][1079];
        for(j=1;j<1079;j++)
        {
            int temp=img[i][j];
            img[i][j]=(buffer[j-1]+img[i][j+1]+buffer[j]+img[i+1][j])/4;
            buffer[j]=temp;
        }
    }
}


void Cpu_8(int img[1920][1080])
{
    int i,j;
    int buffer[1080]={0};
    for(i=0;i<1080;i++)
    {
        buffer[i]= img[0][i];
    }
    int temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7;
    for(i=1;i<1919;i++)
    {
        buffer[0]=img[i][0];
        buffer[1079]=img[i][1079];
        for(j=1;j<1072;j+=8)
        {
            temp0=img[i][j+0];temp1=img[i][j+1];
            temp2=img[i][j+2];temp3=img[i][j+3];
            temp4=img[i][j+4];temp5=img[i][j+5];
            temp6=img[i][j+6];temp7=img[i][j+7];
            img[i][j+0]=(buffer[j-1]+buffer[j]+img[i+1][j]+temp1)/4;
            img[i][j+1]=(temp0+buffer[j+1]+img[i+1][j+1]+temp2)/4;
            img[i][j+2]=(temp1+buffer[j+2]+img[i+1][j+2]+temp3)/4;
            img[i][j+3]=(temp2+buffer[j+3]+img[i+1][j+3]+temp4)/4;
            img[i][j+4]=(temp3+buffer[j+4]+img[i+1][j+4]+temp5)/4;
            img[i][j+5]=(temp4+buffer[j+5]+img[i+1][j+5]+temp6)/4;
            img[i][j+6]=(temp4+buffer[j+6]+img[i+1][j+6]+temp7)/4;
            img[i][j+7]=(temp6+buffer[j+7]+img[i+1][j+7]+img[i][j+8])/4;
            buffer[j+0]=temp0;
            buffer[j+1]=temp1;
            buffer[j+2]=temp2;
            buffer[j+3]=temp3;
            buffer[j+4]=temp4;
            buffer[j+5]=temp5;
            buffer[j+6]=temp6;
            buffer[j+7]=temp7;
        }
        temp0=img[i][j+0];temp1=img[i][j+1];
        temp2=img[i][j+2];temp3=img[i][j+3];
        temp4=img[i][j+4];temp5=img[i][j+5];
        temp6=img[i][j+6];
        img[i][j+0]=(buffer[j-1]+buffer[j]+img[i+1][j]+temp1)/4;
        img[i][j+1]=(temp0+buffer[j+1]+img[i+1][j+1]+temp2)/4;
        img[i][j+2]=(temp1+buffer[j+2]+img[i+1][j+2]+temp3)/4;
        img[i][j+3]=(temp2+buffer[j+3]+img[i+1][j+3]+temp4)/4;
        img[i][j+4]=(temp3+buffer[j+4]+img[i+1][j+4]+temp5)/4;
        img[i][j+5]=(temp4+buffer[j+5]+img[i+1][j+5]+temp6)/4;
        img[i][j+6]=(temp4+buffer[j+6]+img[i+1][j+6]+temp7)/4;
        buffer[j+0]=temp0;
        buffer[j+1]=temp1;
        buffer[j+2]=temp2;
        buffer[j+3]=temp3;
        buffer[j+4]=temp4;
        buffer[j+5]=temp5;
        buffer[j+6]=temp6;
    }
}

void Cpu_4(int img [1920][1080])
{
    int i,j;
    int buffer[1080]={0};
    for(i=0;i<1080;i++)
    {
        buffer[i]= img[0][i];
    }
    int temp0,temp1,temp2,temp3;
    for(i=1;i<1919;i++)
    {
        buffer[0]=img[i][0];
        buffer[1079]=img[i][1079];
        for(j=1;j<1076;j+=4)
        {
            temp0=img[i][j+0];temp1=img[i][j+1];
            temp2=img[i][j+2];temp3=img[i][j+3];
            img[i][j+0]=(buffer[j-1]+buffer[j]+img[i+1][j]+temp1)/4;
            img[i][j+1]=(temp0+buffer[j+1]+img[i+1][j+1]+temp2)/4;
            img[i][j+2]=(temp1+buffer[j+2]+img[i+1][j+2]+temp3)/4;
            img[i][j+3]=(temp2+buffer[j+3]+img[i+1][j+3]+img[i][j+4])/4;
            buffer[j+0]=temp0;
            buffer[j+1]=temp1;
            buffer[j+2]=temp2;
            buffer[j+3]=temp3;
        }
        temp0=img[i][j+0];temp1=img[i][j+1];
        img[i][j+0]=(buffer[j-1]+buffer[j]+img[i+1][j]+temp1)/4;
        img[i][j+1]=(temp0+buffer[j+1]+img[i+1][j+1]+temp2)/4;
        buffer[j+0]=temp0;
        buffer[j+1]=temp1;
    }
}

void Cache_row(int img[1920][1080])
{
    int i,j,ctn;
    int bsize=4;
    int buffer[1080]={0};
    for(i=0;i<1080;i++)
    {
        buffer[i]= img[0][i];
    }
    for(ctn=0;ctn<1919;ctn+=bsize)
    {
        for(i=ctn;i<ctn+bsize;i++)
        {
            if(i>=1919)break;
            buffer[0]=img[i][0];
            buffer[1079]=img[i][1079];
            for(j=1;j<1079;j++)
            {
                int temp=img[i][j];
                img[i][j]=(buffer[j-1]+img[i][j+1]+buffer[j]+img[i+1][j])/4;
                buffer[j]=temp;
            }
        }
    }
}