#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int MerrgInverted(int *A,int p,int q);
int Merrge(int *A,int p,int q,int r);

int main(void)
{
    int a[10];
    int i=0;
    for(i=0;i<10;i++)
    {
        scanf("%d",&a[i]);
    }
    int inverted=MerrgInverted(a,0,9);
    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n%d\n",inverted);
}

int Merrge(int *A,int p,int q,int r)
{
    int n=q-p+1,m=r-q,inver=0;
    int i,j,k;
    int *L=(int *)malloc(sizeof(int)*n);
    int *R=(int *)malloc(sizeof(int)*m);
    for(i=0;i<n;i++)
    {
        L[i]=A[p+i];
    }
    for(j=0;j<m;j++)
    {
        R[j]=A[q+j+1];
    }
    i=0;j=0;k=p;
    while(i<n&&j<m)
    {
        if(L[i]>R[j])
        {
            inver+=n-i;
            A[k]=R[j];
            j++;k++;
        }
        else
        {
            A[k]=L[i];
            i++;k++;
        }
    }
    if(i<n)
    {
        k++;
        for(i;i<n;i++)
        {
            A[k]=L[i];
            k++;
        }
    }
    if(j<m)
    {
        k++;
        for(j;j<m;j++)
        {
            A[k]=R[j];
            k++;
        }
    }
    return inver;
}

int MerrgInverted(int *A,int p,int q)
{
    int inver=0;
    if(p<q)
    {
        int r=(p+q)/2;
        
        inver+=MerrgInverted(A,p,r);
        inver+=MerrgInverted(A,r+1,q);
        inver+=Merrge(A,p,r,q);
    }
    return inver;
}