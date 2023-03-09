#include <stdio.h>
#include <math.h>

int fibadd(int a[], int b[], int c[]); 
void fibdiv(int a[], int b[]);         
int fibsub(int a[], int b[]);          
int fibleft(int a[]);                  
int cmp(int a[], int b[]);             

int main(void)
{
    int fib[101][30] = {0};
    fib[0][0] = 1;
    fib[1][0] = 1;
    int i = 0;
    for (i = 2; i < 101; i++)
    {
        fibadd(fib[i], fib[i - 1], fib[i - 2]);
    }
    fibdiv(fib[99], fib[100]);
    return 0;
}

int fibadd(int a[], int b[], int c[])
{
    int m = 0;
    for (m = 0; m < 30; m++)
    {
        a[m] = b[m] + c[m];
    }
    for (m = 0; m < 30; m++)
    {
        if (a[m] >= 10)
        {
            a[m] = a[m] - 10;
            a[m + 1]++;
        }
    }
}
void fibdiv(int a[], int b[])
{
    printf("0.");
    int i, j = 0;
    fibleft(b);
    for (i = 0; i < 8; i++)
    {
        j = 0;
        while (cmp(a, b) > 0)
        {
            fibsub(a, b);
            j++;
        }
        fibleft(b);
        printf("%d", j);
    }
    printf("\n");
}
int fibsub(int a[], int b[])
{
    int i, j, k;
    for (i = 0; i < 30; i++)
    {
        if (a[i] < b[i])
        {
            for (j = i + 1; a[j] == 0; j++)
                ;
            a[j]--;
            for (k = j - 1; k > i; k--)
            {
                a[k] = 9;
            }
            a[i] = a[i] + 10 - b[i];
        }
        else
        {
            a[i] = a[i] - b[i];
        }
    }
}
int fibleft(int a[])
{
    int i, j;
    for (i = 29; i >= 0 && a[i] == 0; i--)
        ;
    for (j = 0; j < i; j++)
    {
        a[j] = a[j + 1];
    }
    a[i] = 0;

    return 1;
}
int cmp(int a[], int b[])
{
    int i, j;
    for (i = 29; i >= 0 && a[i] == 0; i--)
        ;
    for (j = 29; j >= 0 && b[j] == 0; j--)
        ;
    if (i > j)
    {
        return 1;
    }
    else if (i == j)
    {
        if (a[i] > b[j])
        {
            return 1;
        }
        else if (a[i] == b[j])
        {
            for (; i >= 0 && j >= 0; i--, j--)
            {
                if (a[i] > b[j])
                {
                    return 1;
                }
                if (a[i] < b[j])
                {
                    return -1;
                }
            }
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}