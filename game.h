#ifndef __game_h__
#define __game_h__

typedef struct stick//障碍物结构体
{
	int left;
	int right;
	int top;
	int bottom;
	int v;
	struct stick* next;
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

void free_st(stick* H);//释放障碍物结点内存
void Initst(stick* H);//初始化障碍物
void add_first_st(stick* H);//添加第一个障碍物
void add_st(stick* H);//添加障碍物
void put_st(stick* H, IMAGE &stick1,IMAGE &stick2);//绘制障碍物
void move_st(stick* H);//移动障碍物
void game();//游戏主体逻辑

#endif