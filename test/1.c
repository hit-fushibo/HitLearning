#include<stdio.h>
#include<stdlib.h>

int aa(int x,int y);
int recod[5][5]={0};

int main (void)
{
    printf("%d",aa(4,3));
    
    return 0;
}

int aa(int x,int y)
{
    if(x==0&&y>=0)
    {
        recod[x][y]=1;
        return 1;
    }
    else if (x==1&&y==0)
    {
        recod[x][y]=2;
        return 2;
    }
    else if (x>=2&&y==0)
    {
        recod[x][y]=x+2;
        return x+2;
    }
    else
    {
        if(recod[x-1][y]==0)
        {
            recod[x-1][y]==aa(x-1,y);
            int tmp=recod[x-1][y];
            if(recod[tmp][y-1]==0)
            {
                recod[tmp][y-1]=aa(recod[x-1][y],y-1);
                return recod[tmp][y-1];
            }
            else
            {
                return recod[tmp][y-1];
            }
        }
        else
        {
            int tmp=recod[x-1][y];
            if(recod[tmp][y-1]==0)
            {
                recod[tmp][y-1]=aa(recod[x-1][y],y-1);
                return recod[tmp][y-1];
            }
            else
            {
                return recod[tmp][y-1];
            }

        }
    }
    
    
}