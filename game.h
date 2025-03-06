#ifndef __game_h__
#define __game_h__

typedef struct stick//�ϰ���ṹ��
{
	int left;
	int right;
	int top;
	int bottom;
	int v;
	struct stick* next;
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

void free_st(stick* H);//�ͷ��ϰ������ڴ�
void Initst(stick* H);//��ʼ���ϰ���
void add_first_st(stick* H);//��ӵ�һ���ϰ���
void add_st(stick* H);//����ϰ���
void put_st(stick* H, IMAGE &stick1,IMAGE &stick2);//�����ϰ���
void move_st(stick* H);//�ƶ��ϰ���
void game();//��Ϸ�����߼�

#endif