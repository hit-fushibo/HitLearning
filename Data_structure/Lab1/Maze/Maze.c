#include"Maze.h"

int AutoCreatMaze(int  map[][MAX_X]);
int CreatMaze(int map[][MAX_X])
{
    //printf("please enter the maze size(length width)\n");
    //printf("length and width cannot exceed 50\n:");
    scanf("%d %d",&length,&width);
    int i,j,k,x,y;
    for(i=0;i<width+2;i++)
    {
        if(i==0||i==width+1)
        {
            for(j=0;j<length+2;j++)
            {
                map[i][j]=1;
            }
        }
        else
        {
            map[i][0]=1;
            map[i][length+1]=1;
        }
    }
    scanf("%d %d",&STARTX,&STARTY);
    scanf("%d %d",&ENDX,&ENDY);
    map[STARTX+1][STARTY+1]=2;
    map[ENDX+1][ENDY+1]=3;
    scanf("%d",&k);
    for(i=0;i<k;i++)
    {
        scanf("%d %d",&x,&y);
        map[x+1][y+1]=1;
    }
}
int ShowMaze(int map[][MAX_X])
{
    for(int i=1;i<width+1;i++)
    {
        for(int j=1;j<length+1;j++)
        {
            printf("%d  ",map[i][j]);
        }
        printf("\n");
    }
}
void ShowWay(stack *s)
{
    int x,y;
    while(JudgeEmpty(s))
    {
        x=Top(s,0);y=Top(s,1);
        printf("%d %d\n",x,y);
        Pop(s);
    }
}
int Find(int map[][MAX_X])
{
    int crex=STARTX+1,crey=STARTY+1;
    int dir=1;
    stack *s=(stack *)malloc(sizeof(stack));
    Creat(s);
    Push(s,crex,crey,dir);
    while(JudgeEmpty(s)||crex-1!=ENDX&&crey-1!=ENDY)
    {
        if(dir==1)
        {
            if(map[crex-1][crey]!=1)
            {
                Pop(s);
                Push(s,crex,crey,dir);
                dir=1;
                Push(s,crex-1,crey,1);
                crex--;
            }
            else
            dir++;
        }
        if(dir==2)
        {
            if(map[crex][crey+1]!=1)
            {
                Pop(s);
                Push(s,crex,crey,dir);
                dir=1;
                Push(s,crex,crey+1,1);
                crey++;
            }
            else
            dir++;
        }
        if(dir==3)
        {
            if(map[crex+1][crey]!=1)
            {
                Pop(s);
                Push(s,crex,crey,dir);
                dir=1;
                Push(s,crex+1,crey,1);
                crex++;
            }
            else
            dir++;
        }
        if(dir==4)
        {
            if(map[crex][crey-1]!=1)
            {
                Pop(s);
                Push(s,crex,crey,dir);
                dir=1;
                Push(s,crex,crey-1,1);
                crey--;
            }
            else
            dir++;
        }
        if(dir==5)
        {
            Pop(s);
            crex=Top(s,0);crey=Top(s,1);dir=Top(s,2)+1;
        }

        printf("%d %d\n",crex,crey);
    }
    if(!JudgeEmpty(s))
    {
        printf("There's no way out of this maze\n");
    }
    else
    {
        ShowWay(s);
    }
}
