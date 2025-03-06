#include"flappy_bird.h"

void Initst(stick* H)
{
	add_first_st(H);
	add_st(H);
	add_st(H);
	H->next->left = H->left + width / 3;
	H->next->right = H->next->left + 200;
	H->next->next->left = H->next->left + width / 3;
	H->next->next->right = H->next->next->left + 200;
}

void add_first_st(stick* H)
{
	stick* q = H;
	q->top = rand() % (height / 5) + height / 5;
	q->bottom = q->top + height / 5;
	q->left = width;
	q->right = q->left + 200;
	q->next = NULL;
}

void add_st(stick* H)
{
	stick* p = H, * pre = H;
	while (p != NULL)
	{
		pre = p;
		p = p->next;
	}
	stick* q = (stick*)malloc(sizeof(stick));
	q->top = rand() % (height / 5 * 3) + height / 5;
	q->bottom = q->top + height / 5;
	q->left = width;
	q->right = q->left + 200;
	q->next = NULL;
	pre->next = q;
}

void put_st(stick* H,IMAGE &stick1,IMAGE &stick2)
{
	stick* p = H;
	while (p != NULL)
	{
		transparentimage(p->left, p->top - 800, stick1);
		transparentimage(p->left, p->bottom, stick2);
		p = p->next;
	}
}

void move_st(stick* H,float vx)
{
	stick* p = H;
	while (p != NULL)
	{
		p->right = p->left;
		p->left -= vx;
		p = p->next;
	}
}

void free_st(stick* H)
{
	stick* p = H, * q;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

void game()
{
	//��ʼ����Ϸ����:

	//��ʼ����
	float x = width / 6, y = height / 4;
	float vy = 0, g = 0.2;
	int life = 100;
	wchar_t lifeShow[4] = _T("100");
	//��ʼ���÷�
	int score = 0;
	wchar_t scoreShow[5] = _T("0000");
	//��ȡ����߶�����
	srand((unsigned int)time(NULL));
	//������Ϸ�ٶ�����ٶ�
	float vx = 3, a = 0.001;
	//��ʼ������λ��
	stick* st_First = (stick*)malloc(sizeof(stick));
	Initst(st_First);
	//��ʼ������
	item star;
	star.exist = 0;
	star.radius = 18;

	item stone;
	stone.exist = 0;
	stone.radius = 18;

	//����ͼƬ��Դ
	IMAGE bird, bird1, bird2, bird3, stick1, stick2, background;
	loadimage(&bird1, _T("pictures\\bird1.png"));
	loadimage(&bird2, _T("pictures\\bird2.png"));
	loadimage(&bird3, _T("pictures\\bird3.png"));
	loadimage(&stick1, _T("pictures\\���ϰ���.png"));
	loadimage(&stick2, _T("pictures\\���ϰ���.png"));
	loadimage(&background, _T("pictures\\����.png"));
	loadimage(&star.graph, _T("pictures\\star.png"));
	loadimage(&stone.graph, _T("pictures\\stone.png"));
	bird = bird3;
	
	
	BeginBatchDraw();
	//������
	putimage(0, 0, &background);
	//����
	transparentimage(x - radius, y - radius, bird);
	//������
	put_st(st_First, stick1, stick2);

	//���ո����ʼ��Ϸ
	char input;
	settextstyle(40, 0, _T("����"));//�������ִ�С������
	setbkmode(TRANSPARENT);//��������͸��
	outtextxy(40, 40, _T("���ո����ʼ��Ϸ"));
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

	//��Ϸ����
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
		//����С���ٶ�
		vy = vy + g;
		vx = vx + a;
		bird = vy >= 0 ? bird1 : bird2;
		putimage(0, 0, &background);
		//����С��λ�ã�����С��ͼ��
		y += vy;
		transparentimage(x - radius, y - radius, bird);

		//�ж������Ƿ񵽴����
		if (st_First->right <= 0)
		{
			stick* tmp = st_First;
			st_First = st_First->next;
			free(tmp);
			add_st(st_First);
			score++;
		}
		//�����Ƿ��������ǵ���
		if (0 == star.exist && 0 == rand() % 100)//100��֮һ�������ɵ���
		{
			star.y = rand() % (height / 4) + height / 4;
			star.x = width + 200;
			star.exist = 1;
		}
		//�ж������Ƿ񵽴ﻭ�����
		if (star.x <= 0)
			star.exist = 0;
		//�����Ƿ�������ʯ����
		if (0 == stone.exist && 0 == rand() % 1000)//1000��֮һ�������ɵ���
		{
			stone.y = rand() % (height / 4) + height / 4;
			stone.x = width + 200;
			stone.exist = 1;
		}
		//�ж���ʯ�Ƿ񵽴ﻭ�����
		if (stone.x <= 0)
			stone.exist = 0;
		//�ƶ�����
		move_st(st_First,vx);
		put_st(st_First, stick1, stick2);
		//�ƶ�����
		if (star.exist == 1)
		{
			star.x -= vx;
			transparentimage(star.x - star.radius, star.y - star.radius, star.graph);
		}
		//�ƶ���ʯ
		if (stone.exist == 1)
		{
			stone.x -= vx;
			transparentimage(stone.x - stone.radius, stone.y - stone.radius, stone.graph);
		}
		//С�񴥶�����
		if ( y - radius <= 0)
		{
			y = radius;
			vy = -vy;
		}
		//�ж�С���Ƿ���������
		//���ǻ�Ѫ
		if (star.exist == 1 && pow((x - star.x), 2) + pow((y - star.y), 2) <= pow(radius + star.radius,2))
		{
			star.exist = 0;
			life += 25;
		}
		//��ʯ�ӷ�
		if (stone.exist == 1 && pow((x - stone.x), 2) + pow((y - stone.y), 2) <= pow(radius + stone.radius,2))
		{
			stone.exist = 0;
			score += 10;
		}
		//�ж�С���Ƿ��������ӻ򴥵�,�Խ�����Ϸ
		if (x + radius > st_First->left && x - radius < st_First->right && (y<st_First->top || y>st_First->bottom))
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
		//���㲢��ӡ����
		scoreShow[3] = score % 10 + '0';
		scoreShow[2] = score / 10 % 10 + '0';
		scoreShow[1] = score / 100 % 10 + '0';
		scoreShow[0] = score / 1000 + '0';
		outtextxy(10, 40, _T("�÷֣�"));
		outtextxy(100, 40, scoreShow);
		//���㲢��ӡ����ֵ
		lifeShow[2] = life % 10 + '0';
		lifeShow[1] = life / 10 % 10 + '0';
		lifeShow[0] = life / 100 % 10 + '0';
		outtextxy(10, 80, _T("������"));
		outtextxy(100, 80, lifeShow);
		
		FlushBatchDraw();
		Sleep(2);
	}
	update_Score(score);
	outtextxy(width / 4 + 100, height / 2, _T("Game Over"));
	outtextxy(width / 4 + 100, height / 2 + 40, _T("���յ÷�Ϊ��"));
	outtextxy(width / 4 + 330, height / 2 + 40, scoreShow);
	outtextxy(width / 4 + 100, height / 2 + 80, _T("��������������˵�"));
	FlushBatchDraw();
	_getch();
	cleardevice();
}