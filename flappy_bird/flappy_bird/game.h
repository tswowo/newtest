#ifndef __game_h__
#define __game_h__

typedef struct stick//障碍物结构体
{
	int left;
	int right;
	int top;
	int bottom;
	int v;
}stick;

typedef struct item//道具结构体
{
	int exist;
	int x;
	int y;
	int radius;
	IMAGE graph;
}item;

extern int radius;

void game();//游戏主体逻辑

#endif