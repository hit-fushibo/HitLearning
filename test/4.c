#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
typedef struct mirror
{
    long int i;
    int fangxiang;
    long int x1;
    long int y1;
    long int x2;
    long int y2;
    float a;
    struct mirror * next;
}mirror;

int Reflection(long int d,long int x,long int y,mirror * a,float * l);
int ReflectionJudgement(long int x,long int y,long int x1,long int y1,long int x2,long int y2);

int main (void)
{
    mirror * head=(mirror * )malloc(sizeof(mirror));
    mirror * q;
    mirror * p=(mirror * )malloc(sizeof(mirror));
    head->next=p;
    p->next=NULL;
    int ctn,num,mirrornum=0;
    long int i,k;
    scanf("%d",&num);
    //scanf("%f",&p->a);
    for(i=0;i<num;i++)
    {
        scanf("%d ",&ctn);
        switch (ctn)
        {
        case 1:
        {
            if(mirrornum==0)
            {
                scanf("%ld %ld %ld %ld %f",&p->x1,&p->y1,&p->x2,&p->y2,&p->a);
                p->i=i+1;
                if((p->x1-p->x2)*(p->y1-p->y2)>0)
                {
                    p->fangxiang=1;
                }
                else
                {
                    p->fangxiang=-1;
                }
                mirrornum++;
            }
            else
            {
                q=(mirror * )malloc(sizeof(mirror));
                p->next=q;
                scanf("%ld %ld %ld %ld %f",&q->x1,&q->y1,&q->x2,&q->y2,&q->a);
                q->i=i+1;
                q->next=NULL;
                p=q;
                q=NULL;
                if((p->x1-p->x2)*(p->y1-p->y2)>0)
                {
                    p->fangxiang=1;
                }
                else
                {
                    p->fangxiang=-1;
                }
                mirrornum++;
            }
        }
            break;
        case 2:
        {
            scanf("%ld",&k);
            for(q=head;q->next!=NULL;q=q->next)
            {
                if(k==q->next->i)
                {
                    mirror *temp=q->next;
                    q->next=q->next->next;
                    free(temp);
                    mirrornum--;
                    break;
                }
            }
        }
            break;
        
        default:
        {
            long int x,y,t,flag;
            int d;
            float l;
            scanf("%ld %ld %d %f %ld",&x,&y,&d,&l,&t);
            for(flag=0;flag<t;flag++)
            {
                switch (d)
                {
                case 0:
                {
                    x++;
                    d=Reflection(d,x,y,head,&l);
                }
                    break;
                case 1:
                {
                    y++;
                    d=Reflection(d,x,y,head,&l);
                }
                    break;
                case 2:
                {
                    x--;
                    d=Reflection(d,x,y,head,&l);
                }
                    break;
                default:
                {
                    y--;
                    d=Reflection(d,x,y,head,&l);
                }
                    break;
                }
                if(l<1)
                {
                    printf("0 0 0\n");
                    break;
                }
            }
            if(l>=1)
            printf("%ld %ld %ld\n",x,y,(long int)l);
        }
            break;
        }
    }
    return 0;
}

int Reflection(long int d,long int x,long int y,mirror * a,float * l)
{
    for(;a->next!=NULL;a=a->next)
    {
        if(ReflectionJudgement(x,y,a->next->x1,a->next->y1,a->next->x2,a->next->y2)==1)
        {
            *l=((*l)*a->next->a);
            if(a->next->fangxiang==1)
            {
                switch (d)
                {
                case 0:
                    return 1;
                    break;
                case 1:
                    return 0;
                    break;
                case 2:
                    return 3;
                    break;

                default:
                    return 2;
                    break;
                }
            }
            else
            {
                return 3-d;
            }
        }
    }
    return d;
}
int ReflectionJudgement(long int x,long int y,long int x1,long int y1,long int x2,long int y2)
{
    int maxx,maxy,minx,miny;
    if(x1>x2)
    {
        maxx=x1;
        minx=x2;
    }
    else
    {
        maxx=x2;
        minx=x1;
    }
    if(y1>y2)
    {
        maxy=y1;
        miny=y2;
    }
    else
    {
        maxy=y2;
        miny=y1;
    }
    
    if(x>minx&&x<maxx&&y>miny&&y<maxy)
    {
        
        float a,b;
        a=(float)(x-x1)/(float)(y-y1);
        b=(float)(x2-x1)/(float)(y2-y1);
        if(a==b)
        return 1;
        else
        return 0;
    }
    else
    return 0;

}