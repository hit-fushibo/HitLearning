#include<stdio.h>
#include<stdlib.h>

int main (void)
{
    int a=0;
    scanf("%d",&a);
    int c=1,b=1;
    if(a==0 || a==1){
        printf("%d\n",c);
    }
    else{
        int temp=b;
        while (a>1)
        {
            temp+=c;
            c=b;
            b=temp;
            a--;
        }
        printf("%d\n",b);
        
    }
    return 0;
}