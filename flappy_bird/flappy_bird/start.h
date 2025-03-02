#ifndef __start_h__
#define __start_h__

typedef struct users//用户结构体
{
	wchar_t name[20];
	int score;
	struct users* next;
}*user;

void transparentimage(int x, int y, IMAGE img);//显示透明背景图片
void start();//显示游戏主菜单背景
void menu();//显示主界面菜单
void ShowRules();//显示游戏规则
void main_Show();//游戏主菜单跳转

#endif