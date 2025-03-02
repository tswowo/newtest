#include"flappy_bird.h"

#ifndef __login_h__
#define __login_h__

extern int score;
void Vistor_Login();//初始化加载游客账户
user create(int x);//创建链表结点
user load();//读取用户列表文件
int find(wchar_t* in, user H);//查找用户名是否存在
void foutput(user head);//存档用户列表
void regis(wchar_t* in, user H);//注册新用户并存档
void login();//登录界面
void update_Score(int score);//更新分数
user finduser(user H, wchar_t* text);//查找用户结点
void printLink();//打印用户列表
void getName();//获取输入字符串
void remove();//删除用户
void exchange();//更改用户名
void getLogin();//登入用户

#endif