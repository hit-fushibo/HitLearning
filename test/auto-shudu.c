//自动解数独程序

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void Creat(int **map);//初始化初始数独地图
void ShowMap(int ** map);//展示数独地图
void Handle(int **map);//开始解数独
int IsCompleted(int **map);//判断是否解完
int RowConflict(int **map,int x,int y,int num);//判断在(x,y)位置填入num是否会导致行冲突
int ColConflict(int **map,int x,int y,int num);//判断在(x,y)位置填入num是否会导致列冲突
int CellConflict(int **map,int x,int y,int num);//判断在(x,y)位置填入num是否会导致单元格冲突
void GetCell(int x,int y,int * top,int *left);//通过(x,y)位置返回所在单元格左上角坐标



int main (void)
{
    int **map=(int **)malloc(sizeof(int *)*9);
    for(int i=0;i<9;i++)
    {
        map[i]=(int *)malloc(sizeof(int)*9);
        for(int j=0;j<9;j++)
        {
            map[i][j]=0;
        }
    }
    Creat(map);
    Handle(map);
    printf("result\n\n");
    ShowMap(map);
    printf("\n\n");
    return 0;
}

void Creat(int **map)
{
    printf("Take the upper left corner as the origin\n");
    int x,y,num;
    printf("x y num(Terminate with the input of - 1 - 1 - 1)\n:");
    scanf("%d %d %d",&x,&y,&num);
    while (x!=-1&&y!=-1&&num!=-1)
    {
        map[x][y]=num;
        printf("x y num(Terminate with the input of - 1 - 1 - 1)\n:");
        scanf("%d %d %d",&x,&y,&num);
    }
    printf("this is original map\n\n");
    ShowMap(map);
    printf("\n\n");

}

void ShowMap(int ** map)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}

void Handle(int **map)//开始解数独
{
    do
    {
        int Flag=0;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(map[i][j])
                    continue;
                int flag=0,tmp=0;
                for(int num=1;num<10;num++)
                {
                    if(RowConflict(map,i,j,num)||ColConflict(map,i,j,num)||CellConflict(map,i,j,num))
                        continue;
                    else
                    {
                        flag++;
                        tmp=num;
                    }
                }
                if(flag==1)
                {
                    map[i][j]=tmp;
                    Flag++;
                }
            }
        }
        if(Flag==0)
        {
            printf("error no result\n");
            exit(1);
        }
    } while (!IsCompleted(map));
    
}


int IsCompleted(int **map)//判断是否解完
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(map[i][j]==0)
                return 0;
        }
    }
    return 1;
}


int RowConflict(int **map,int x,int y,int num)//判断在(x,y)位置填入num是否会导致行冲突
{
    for(int i=0;i<9;i++)
    {
        if(num==map[x][i])
            return 1;
    }
    return 0;
}


int ColConflict(int **map,int x,int y,int num)//判断在(x,y)位置填入num是否会导致列冲突
{
    for(int i=0;i<9;i++)
    {
        if(num==map[i][y])
            return 1;
    }
    return 0;
}


int CellConflict(int **map,int x,int y,int num)//判断在(x,y)位置填入num是否会导致单元格冲突
{
    int top=0,left=0;
    GetCell(x,y,&top,&left);
    for(int i=top;i<top+3;i++)
    {
        for(int j=left;j<left+3;j++)
        {
            if(num==map[i][j])
                return 1;
        }
    }
    return 0;
}


void GetCell(int x,int y,int * top,int *left)//通过(x,y)位置返回所在单元格左上角坐标
{
    if(y>=6)
    {
        *left=6;
    }
    else if (y>=3)
    {
        *left=3;
    }
    else
    {
        *left=0;
    }
    
    if(x>=6)
    {
        *top=6;
    }
    else if (x>=3)
    {
        *top=3;
    }
    else
    {
        *top=0;
    }
    
    
}