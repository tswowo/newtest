#ifndef __game_h__
#define __game_h__

typedef struct stick//�ϰ���ṹ��
{
	int left;
	int right;
	int top;
	int bottom;
	int v;
}stick;

typedef struct item//���߽ṹ��
{
	int exist;
	int x;
	int y;
	int radius;
	IMAGE graph;
}item;

extern int radius;

void game();//��Ϸ�����߼�

#endif