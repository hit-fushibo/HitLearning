//以矩阵的形式显示迷宫，1表示墙，2起点，3终点，假定只有四个方向可走

#ifndef MAZE_H
#define MAZE_H

#include "Stack.h"


#define MAX_X 50
#define MAX_Y 50
int STARTX=0,STARTY=0,ENDX=0,ENDY=0,length=0,width=0;

int AutoCreatMaze(int  map[][MAX_X]);
int CreatMaze(int map[][MAX_X]);
int Find(int map[][MAX_X]);
int ShowMaze(int map[][MAX_X]);
void ShowWay(stack *s);

#endif