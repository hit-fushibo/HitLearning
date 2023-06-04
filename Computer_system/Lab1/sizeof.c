#include<stdio.h>

int main (void)
{
    printf("size of char: %u\n",sizeof(char));
    printf("size of short: %u\n",sizeof(short));
    printf("size of int: %u\n",sizeof(int));
    printf("size of long: %u\n",sizeof(long));
    printf("size of long long: %u\n",sizeof(long long));
    printf("size of float: %u\n",sizeof(float));
    printf("size of double: %u\n",sizeof(double));
    printf("size of long double: %u\n",sizeof(long double));
    printf("size of pointer: %u\n",sizeof(int *));
    return 0;
}