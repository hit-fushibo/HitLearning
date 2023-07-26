#include<stdio.h>
#include<stdlib.h>

int main (void)
{
    char a[10];
    
    gets(a);
    for(int i =0;i<10;i++)
    {
        if(a[i]=='\0')
        break;
        a[i]='a'+(a[i]-'a')%8;
    }
    printf("%s",a);
    return 0;
}