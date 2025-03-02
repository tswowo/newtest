#include"flappy_bird.h"

//ȫ�ֱ�������
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

void start()//��Ϸ�˵�ͼƬ
{
	//����ͼƬ��Դ
	IMAGE bird, background;
	loadimage(&bird, _T("bird3.png"));
	loadimage(&background, _T("����.png"));
	//��ʼ�����λ��
	float x = width / 6, y = height / 4;
	//������
	putimage(0, 0, &background);
	//����
	transparentimage(x - radius, y - radius, bird);
	FlushBatchDraw();
}

void menu()//���˵�����
{
	//����������ʽ
	settextstyle(40, 0, _T("����"));//�������ִ�С������
	setbkmode(TRANSPARENT);//��������͸��
	settextcolor(RGB(50, 255, 50));//�趨������ɫ
	//��ʾ���˵���������
	outtextxy(0, 0, _T("��ң�"));
	outtextxy(0, 40, name);
	outtextxy(width / 4, height / 4 + 40, _T("Flappy Bird"));
	outtextxy(width / 4, height / 4 + 80, _T("1.��¼�˺�"));
	outtextxy(width / 4, height / 4 + 120, _T("2.��ʼ��Ϸ"));
	outtextxy(width / 4, height / 4 + 160, _T("3.���а�"));
	outtextxy(width / 4, height / 4 + 200, _T("4.��Ϸ����"));
	outtextxy(width / 4, height / 4 + 240, _T("5.�˳���Ϸ"));
	FlushBatchDraw();
}

void ShowRules()//��Ϸ������ʾ
{
	IMAGE star, stone;
	loadimage(&star, _T("star.png"));
	loadimage(&stone, _T("stone.png"));
	start();
	outtextxy(width / 4, height / 4, _T("Flappy Bird ��Ϸ����"));
	outtextxy(width / 4, height / 4 + 40, _T("�ո�� С������"));
	outtextxy(width / 4, height / 4 + 80, _T("����1  �۳�200����ֵ��ʹС������ٶȼ���"));
	outtextxy(width / 4, height / 4 + 120, _T("       ����25����ֵ"));
	transparentimage(width / 4, height / 4 + 120, star);
	outtextxy(width / 4, height / 4 + 160, _T("       ����20�÷�"));
	transparentimage(width / 4, height / 4 + 160, stone);
	FlushBatchDraw();
	_getch();
}

void main_Show()//���˵�ѡ��
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