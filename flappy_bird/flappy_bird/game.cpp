#include"flappy_bird.h"

void game()
{
	//初始化游戏界面:

	//初始化鸟
	float x = width / 6, y = height / 4;
	float vy = 0, g = 0.2;
	int life = 100;
	wchar_t lifeShow[4] = _T("100");
	//初始化得分
	int score = 0;
	wchar_t scoreShow[5] = _T("0000");
	//获取随机高度种子
	srand((unsigned int)time(NULL));
	//设置游戏速度与加速度
	float vx = 3, a = 0.001;
	//初始化柱子位置
	stick st[3];
	st[0].top = rand() % (height / 4) + height / 4;
	st[0].bottom = st[0].top + height / 3;
	st[0].left = width / 4 * 3;
	st[0].right = st[0].left + 200;

	st[1].top = rand() % (height / 4) + height / 4;
	st[1].bottom = st[1].top + height / 3;
	st[1].left = st[0].left + width / 3;
	st[1].right = st[1].left + 200;

	st[2].top = rand() % (height / 4) + height / 4;
	st[2].bottom = st[2].top + height / 3;
	st[2].left = st[1].left + width / 3;
	st[2].right = st[2].left + 200;
	//初始化道具
	item star;
	star.exist = 0;
	star.radius = 18;

	item stone;
	stone.exist = 0;
	stone.radius = 18;

	//加载图片资源
	IMAGE bird, bird1, bird2, bird3, stick1, stick2, background;
	loadimage(&bird1, _T("bird1.png"));
	loadimage(&bird2, _T("bird2.png"));
	loadimage(&bird3, _T("bird3.png"));
	loadimage(&stick1, _T("上障碍物.png"));
	loadimage(&stick2, _T("下障碍物.png"));
	loadimage(&background, _T("背景.png"));
	loadimage(&star.graph, _T("star.png"));
	loadimage(&stone.graph, _T("stone.png"));
	bird = bird3;
	
	
	BeginBatchDraw();
	//画背景
	putimage(0, 0, &background);
	//画鸟
	transparentimage(x - radius, y - radius, bird);
	//画柱子
	transparentimage(st[0].left, st[0].top - 400, stick1);
	transparentimage(st[0].left, st[0].bottom, stick2);

	putimage(st[1].left, st[1].top - 400, &stick1);
	putimage(st[1].left, st[1].bottom, &stick2);

	putimage(st[2].left, st[2].top - 400, &stick1);
	putimage(st[2].left, st[2].bottom, &stick2);

	//按空格键开始游戏
	char input;
	settextstyle(40, 0, _T("宋体"));//设置文字大小，字体
	setbkmode(TRANSPARENT);//文字字体透明
	settextcolor(RGB(50, 255, 50));//设定文字颜色
	outtextxy(40, 40, _T("按空格键开始游戏"));
	FlushBatchDraw();
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			if (input == ' ')
				break;
		}
	}
	cleardevice();

	//游戏本体
	while (1)
	{
		cleardevice();
		if (_kbhit())
		{
			input = _getch();
			if (input == ' ')
				vy = -6;
			if (input == '1' && life > 200)
			{
				vx /= 2;
				life -= 200;
			}
		}
		//计算小鸟速度
		vy = vy + g;
		vx = vx + a;
		bird = vy >= 0 ? bird1 : bird2;
		putimage(0, 0, &background);
		//计算小鸟位置，放置小鸟图像
		y += vy;
		transparentimage(x - radius, y - radius, bird);

		//判定柱子是否到达左侧
		if (st[0].right <= 0)
		{

			st[0].left = st[1].left;
			st[0].right = st[1].right;
			st[0].top = st[1].top;
			st[0].bottom = st[1].bottom;

			st[1].left = st[2].left;
			st[1].right = st[2].right;
			st[1].top = st[2].top;
			st[1].bottom = st[2].bottom;

			st[2].left = width;
			st[2].top = rand() % (height / 4) + height / 4;
			st[2].bottom = st[2].top + height / 3;
			score++;
		}
		//计算是否生成星星道具
		if (0 == star.exist && 0 == rand() % 100)//100分之一概率生成道具
		{
			star.y = rand() % (height / 4) + height / 4;
			star.x = width + 200;
			star.exist = 1;
		}
		//判断星星是否到达画面左侧
		if (star.x <= 0)
			star.exist = 0;
		//计算是否生成钻石道具
		if (0 == stone.exist && 0 == rand() % 1000)//1000分之一概率生成道具
		{
			stone.y = rand() % (height / 4) + height / 4;
			stone.x = width + 200;
			stone.exist = 1;
		}
		//判断钻石是否到达画面左侧
		if (stone.x <= 0)
			stone.exist = 0;
		//移动柱子
		st[0].right = st[0].left;
		st[0].left -= vx;
		putimage(st[0].left, st[0].top - 400, &stick1);
		putimage(st[0].left, st[0].bottom, &stick2);

		st[1].right = st[1].left;
		st[1].left -= vx;
		putimage(st[1].left, st[1].top - 400, &stick1);
		putimage(st[1].left, st[1].bottom, &stick2);

		st[2].right = st[2].left;
		st[2].left -= vx;
		putimage(st[2].left, st[2].top - 400, &stick1);
		putimage(st[2].left, st[2].bottom, &stick2);
		//移动星星
		if (star.exist == 1)
		{
			star.x -= vx;
			transparentimage(star.x - star.radius, star.y - star.radius, star.graph);
		}
		//移动钻石
		if (stone.exist == 1)
		{
			stone.x -= vx;
			transparentimage(stone.x - stone.radius, stone.y - stone.radius, stone.graph);
		}
		//小鸟触顶反弹
		if ( y - radius <= 0)
		{
			y = radius;
			vy = -vy;
		}
		//判断小鸟是否碰到道具
		//星星回血
		if (star.exist == 1 && pow((x - star.x), 2) + pow((y - star.y), 2) <= pow(radius + star.radius,2))
		{
			star.exist = 0;
			life += 25;
		}
		//钻石加分
		if (stone.exist == 1 && pow((x - stone.x), 2) + pow((y - stone.y), 2) <= pow(radius + stone.radius,2))
		{
			stone.exist = 0;
			score += 10;
		}
		//判定小鸟是否碰到柱子或触底,以结束游戏
		if (x + radius > st[0].left && x - radius < st[0].right && (y<st[0].top || y>st[0].bottom))
		{
			life-=3;
			Sleep(10);
			if (life <= 0)
				break;
		}
		if (y + radius > height)
		{
			x = width / 6, y = height / 4;
			vy = 0;
			break;
		}
		//计算并打印分数
		scoreShow[3] = score % 10 + '0';
		scoreShow[2] = score / 10 % 10 + '0';
		scoreShow[1] = score / 100 % 10 + '0';
		scoreShow[0] = score / 1000 + '0';
		outtextxy(10, 40, _T("得分："));
		outtextxy(100, 40, scoreShow);
		//计算并打印生命值
		lifeShow[2] = life % 10 + '0';
		lifeShow[1] = life / 10 % 10 + '0';
		lifeShow[0] = life / 100 % 10 + '0';
		outtextxy(10, 80, _T("生命："));
		outtextxy(100, 80, lifeShow);
		
		FlushBatchDraw();
		Sleep(2);
	}
	update_Score(score);
	outtextxy(width / 4 + 100, height / 2, _T("Game Over"));
	outtextxy(width / 4 + 100, height / 2 + 40, _T("最终得分为："));
	outtextxy(width / 4 + 330, height / 2 + 40, scoreShow);
	outtextxy(width / 4 + 100, height / 2 + 80, _T("按任意键返回主菜单"));
	FlushBatchDraw();
	_getch();
	cleardevice();
}