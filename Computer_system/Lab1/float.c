#include<stdio.h>

int main (void)
{
    float f;
    for(;;)
    {
        printf("enter a float:");
        scanf("%f",&f);
        printf("%f\n",f);
        if(f==0)
        break;
    }
    return 0;
}