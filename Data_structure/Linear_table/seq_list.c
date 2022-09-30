#include"seq_list.h"

//创建数组线性表
void CreatList(SeqList * l)
{
    l->last=0;
}

//初始化线性表
void InitializeList(SeqList*a,int num)
{
    if(num>MAXLENGTH-1)
    {
        printf("error too big\n");
        exit(8);
    }
    for(int i=1;i<=num;i++)
    {
        scanf("%d",&a->data[i]);
    }
    a->last=num;
    return ;
}

//输出线性表
void OutPut(SeqList *l)
{
    int i=0;
    for(i=1;i<=l->last;i++)
    {
        printf("%d ",l->data[i]);
    }
    printf("\n");
}

//判断非空 空->0 非空->1
int IsZero(SeqList * l)
{
    if(l->last==0)
    return 0;
    else
    return 1;
}

//在线性表的第a项后插入一项
void Insert(SeqList * l,int a)
{
    if(l->last==MAXLENGTH-1)
    {
        printf("no more memory\n");
        exit(9);
    }
    else if(a<1||a>l->last)
    {
        printf("error no this postion\n");
        exit(7);
    }
    else
    {
        int i=++l->last;
        for(i;i>a+1;i--)
        {
            l->data[i]=l->data[i-1];
        }
        scanf("%d",&l->data[a+1]);
    }
}

//删除第a项
void Delete(SeqList * l,int a)
{
    if(a<1||a>l->last)
    {
        printf("error no this postion\n");
        exit(7);
    }
    else
    {
        int i=a;
        for(i;i<l->last;i++)
        {
            l->data[i]=l->data[i+1];
        }
        l->last--;
    }
}

//编辑第a项
void Modify(SeqList * l,int a)
{
    if(a<1||a>l->last)
    {
        printf("error no this postion\n");
        exit(7);
    }
    scanf("%d",&l->data[a]);
}

//查询第a项
int  Search(SeqList * l,int a)
{
    if(a<1||a>l->last)
    {
        printf("error no this postion\n");
        exit(7);
    }
    else
    {
        return l->data[a];
    }
}

//删除有序表的重复项
void DeleteRepeatElement(SeqList * l)
{
    int i=1,j;
    for(j=2;j<=l->last;j++)
    {
        if(l->data[j]!=l->data[i])
        {
            i++;
            l->data[i]=l->data[j];
        }
    }
    l->last=i;
}

//删除表中值为element的项
void DeleteElement(SeqList * l,int element)
{
    int i=0,j=1;
    for(;j<=l->last;j++)
    {
        if(l->data[j]!=element)
        {
            i++;
            l->data[i]=l->data[j];
        }
    }
    l->last=i;
}

//逆置表
void Inverted(SeqList * l)
{
    if(IsZero(l)==0||l->last==1)return;
    int i=1,j=l->last,temp=0;
    while (i<j)
    {
        temp=l->data[i];
        l->data[i]=l->data[j];
        l->data[j]=temp;
        i++;j--;
    }
}

//左移k项
void MoveLeft(SeqList * l,int k)
{
    int i=0,temp,j;
    for(i=0;i<k;i++)
    {
        temp=l->data[1];
        for(j=1;j<l->last;j++)
        {
            l->data[j]=l->data[j+1];
        }
        l->data[l->last]=temp;
    }
}

//右移k项
void MoveRight(SeqList * l,int k)
{
    int i=0,temp,j;
    for(i=0;i<k;i++)
    {
        temp=l->data[l->last];
        for(j=l->last;j>1;j--)
        {
            l->data[j]=l->data[j-1];
        }
        l->data[1]=temp;
    }
}

//合并有序表
void Merge(SeqList * l1,SeqList *l2,SeqList ** re)
{
    SeqList *r=*re;
    if(l1->last+l2->last>MAXLENGTH-1)
    {
        printf("error too big\n");
        exit(8);
    }
    else if(l1->last==0&&l2->last==0)
    {
        r->last=0;
    }
    else if(l1->last==0)
    {
        r=l2;
    }
    else if(l1->last==0)
    {
        r=l1;
    }
    else
    {

        r->last=l1->last+l2->last;
        int p1=1,p2=1,i=1;
        while(p1<l1->last&&p2<=l2->last)
        {
            if(l1->data[p1]<l2->data[p2])
            {
                r->data[i]=l1->data[p1];
                if(p1<=l1->last)p1++;
            }
            else
            {
                r->data[i]=l2->data[p2];
                if(p2<l2->last)p2++;
            }
            i++;
        }
        if(p1<l1->last&&p2<l2->last)return ;
        else if (p1<l1->last)
        {
            r->data[i]=l2->data[p2];i++;
            while(p1<=l1->last)
            {
                r->data[i]=l1->data[p1];
                p1++;
                i++;
            }
        }
        else
        {
            r->data[i]=l1->data[p1];i++;
            while(p2<=l2->last)
            {
                r->data[i]=l2->data[p2];
                i++;
                p2++;
            }
        }
        
    }
    return ;
}