#include"flappy_bird.h"

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
	//��ʼ������
	item star;
	star.exist = 0;
	star.radius = 18;

	item stone;
	stone.exist = 0;
	stone.radius = 18;

	//����ͼƬ��Դ
	IMAGE bird, bird1, bird2, bird3, stick1, stick2, background;
	loadimage(&bird1, _T("bird1.png"));
	loadimage(&bird2, _T("bird2.png"));
	loadimage(&bird3, _T("bird3.png"));
	loadimage(&stick1, _T("���ϰ���.png"));
	loadimage(&stick2, _T("���ϰ���.png"));
	loadimage(&background, _T("����.png"));
	loadimage(&star.graph, _T("star.png"));
	loadimage(&stone.graph, _T("stone.png"));
	bird = bird3;
	
	
	BeginBatchDraw();
	//������
	putimage(0, 0, &background);
	//����
	transparentimage(x - radius, y - radius, bird);
	//������
	transparentimage(st[0].left, st[0].top - 400, stick1);
	transparentimage(st[0].left, st[0].bottom, stick2);

	putimage(st[1].left, st[1].top - 400, &stick1);
	putimage(st[1].left, st[1].bottom, &stick2);

	putimage(st[2].left, st[2].top - 400, &stick1);
	putimage(st[2].left, st[2].bottom, &stick2);

	//���ո����ʼ��Ϸ
	char input;
	settextstyle(40, 0, _T("����"));//�������ִ�С������
	setbkmode(TRANSPARENT);//��������͸��
	settextcolor(RGB(50, 255, 50));//�趨������ɫ
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