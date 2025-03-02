#include"flappy_bird.h"

//全局变量声明
wchar_t name[100] = _T("ceshi");
int width = 1200;
int height = 700;
int radius = 22;

void transparentimage(int x, int y, IMAGE img) {
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0;i < img1.getheight() * img1.getwidth();i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03) {
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE)) {
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
}

void start()//游戏菜单图片
{
	//加载图片资源
	IMAGE bird, background;
	loadimage(&bird, _T("bird3.png"));
	loadimage(&background, _T("背景.png"));
	//初始化鸟的位置
	float x = width / 6, y = height / 4;
	//画背景
	putimage(0, 0, &background);
	//画鸟
	transparentimage(x - radius, y - radius, bird);
	FlushBatchDraw();
}

void menu()//主菜单文字
{
	//设置字体样式
	settextstyle(40, 0, _T("宋体"));//设置文字大小，字体
	setbkmode(TRANSPARENT);//文字字体透明
	settextcolor(RGB(50, 255, 50));//设定文字颜色
	//显示主菜单文字内容
	outtextxy(0, 0, _T("玩家："));
	outtextxy(0, 40, name);
	outtextxy(width / 4, height / 4 + 40, _T("Flappy Bird"));
	outtextxy(width / 4, height / 4 + 80, _T("1.登录账号"));
	outtextxy(width / 4, height / 4 + 120, _T("2.开始游戏"));
	outtextxy(width / 4, height / 4 + 160, _T("3.排行榜"));
	outtextxy(width / 4, height / 4 + 200, _T("4.游戏规则"));
	outtextxy(width / 4, height / 4 + 240, _T("5.退出游戏"));
	FlushBatchDraw();
}

void ShowRules()//游戏规则显示
{
	IMAGE star, stone;
	loadimage(&star, _T("star.png"));
	loadimage(&stone, _T("stone.png"));
	start();
	outtextxy(width / 4, height / 4, _T("Flappy Bird 游戏规则："));
	outtextxy(width / 4, height / 4 + 40, _T("空格键 小鸟跳起"));
	outtextxy(width / 4, height / 4 + 80, _T("数字1  扣除200生命值，使小鸟飞行速度减半"));
	outtextxy(width / 4, height / 4 + 120, _T("       增加25生命值"));
	transparentimage(width / 4, height / 4 + 120, star);
	outtextxy(width / 4, height / 4 + 160, _T("       增加20得分"));
	transparentimage(width / 4, height / 4 + 160, stone);
	FlushBatchDraw();
	_getch();
}

void main_Show()//主菜单选项
{
	wchar_t input;
	while (1)
	{
		start();
		menu();
		input = _getch();
		switch (input)
		{
		case '1':
			login();
			break;
		case '2':
			game();
			break;
		case '3':
			rank_Show();
			break;
		case '4':
			ShowRules();
			break;
		case '5':
			closegraph();
			return;
		}
	}
}