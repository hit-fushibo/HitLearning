#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(void)
{
	long int n,N,sum=0,i=1,r,j,k,l;
    long long error=0;
	long int * a;
	scanf("%ld %ld",&n,&N);
    r=N/(n+1);
	a=(long int *)malloc(sizeof(long int)*(n+1));
	a[0]=0;
	for(i=1;i<n+1;i++)
	{
		scanf("%ld",&a[i]);
	}
	long int f[N];long int g[N];
    for(i=0;i<n;i++)
    {
        j=a[i],k=a[i+1];
        for(l=j;l<k;l++)
        {
            f[l]=i;
        }
    }
    for(j=a[n];j<N;j++)
    {
        f[j]=n;
    }
    for(i=0;i<N;i++)
    {
        g[i]=i/r;
        error+=abs(g[i]-f[i]);
    }
    printf("%ld",error);
	return 0;
}