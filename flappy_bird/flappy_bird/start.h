#ifndef __start_h__
#define __start_h__

typedef struct users//�û��ṹ��
{
	wchar_t name[20];
	int score;
	struct users* next;
}*user;

void transparentimage(int x, int y, IMAGE img);//��ʾ͸������ͼƬ
void start();//��ʾ��Ϸ���˵�����
void menu();//��ʾ������˵�
void ShowRules();//��ʾ��Ϸ����
void main_Show();//��Ϸ���˵���ת

#endif