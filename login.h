#include"flappy_bird.h"

#ifndef __login_h__
#define __login_h__

extern int score;
void Vistor_Login();//��ʼ�������ο��˻�
user create(int x);//����������
user load();//��ȡ�û��б��ļ�
int find(wchar_t* in, user H);//�����û����Ƿ����
void foutput(user head);//�浵�û��б�
void regis(wchar_t* in, user H);//ע�����û����浵
void login();//��¼����
void update_Score(int score);//���·���
user finduser(user H, wchar_t* text);//�����û����
void printLink();//��ӡ�û��б�
void getName();//��ȡ�����ַ���
void remove();//ɾ���û�
void exchange();//�����û���
void getLogin();//�����û�

#endif