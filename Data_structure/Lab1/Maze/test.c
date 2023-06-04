#include"Maze.h"

#include"Maze.c"
#include"Stack.c"

int main(void)
{
    int map[MAX_Y][MAX_X]={0};
    CreatMaze(map);
    ShowMaze(map);
    Find(map);
    return 0;
}