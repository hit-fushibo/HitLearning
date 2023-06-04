#include<stdio.h>
#include<math.h>
int sum(int a,int b,int c,int d)
{
    return a*c-b*d;
}

float P(int a,int b,int c,int d)
{
    float t=a+b+c+d;
    float x=pow(0.4,t);
    float y=pow(0.6,(4-t));
    float r=x*y;
    return r;
}

int main(void)
{
    int a,b,c,d;
    float x[3]={0};
    for(a=0;a<2;a++)
    {
        for(b=0;b<2;b++)
        {
            for(c=0;c<2;c++)
            {
                for(d=0;d<2;d++)
                {
                    x[sum(a,b,c,d)+1]+=P(a,b,c,d);
                }
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        printf("%d %f\n",i-1,x[i]);
    }
}