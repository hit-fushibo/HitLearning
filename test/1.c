#include<stdio.h>
#include<stdlib.h>

int main (int argc,char *argv[])
{
    long long int a,b,c;
    //for(a=0;a<3218;a++)
    //{
    //    for(b=0;b<3128;b++)
    //    {
    //        for(c=0;c<3218;c++)
    //        {
    //            if(a*b*c==3218)
    //            {
    //                printf("%d %d %d\n",a,b,c);
    //            }
    //        }
    //    }
    //}
    for(a=0;a<1609;a++)
    {
        if(1609%a==0)
        {
            printf("%d\n",a);
        }
    }
    
    return 0;
}