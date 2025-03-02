#include"flappy_bird.h"

wchar_t inName[100];
wchar_t input;
char flag;

void getName()//接收键盘输入并显示
{
	static int flag0 = 0;
	int i = 0;
	input = '\0';
	inName[0] = '\0';
	while (input != 13)
	{
		//显示已输入文字
		input = _getch();
		cleardevice();
		start();
		if (flag == '2' && flag0 == 0)
			outtextxy(width / 4 - 80, height / 4, _T("请输入用户名："));
		else if (flag == '2' && flag0 == 1)
			outtextxy(width / 4 - 80, height / 4, _T("请输入新名称："));
		else
			outtextxy(width / 4 - 80, height / 4, _T("请输入用户名："));
		if (input == 8 && i > 0)
		{
			i--;
			inName[i] = '\0';
		}
		else if (i >= 0)
		{
			inName[i++] = input;
			inName[i] = '\0';
		}
		outtextxy(width / 4, height / 4 + 40, inName);
		FlushBatchDraw();
	}
	if (flag == '2' && flag0 == 0)
	{
		flag0 = 1;
	}
	else if (flag == '2' && flag0 == 1)
	{
		flag0 = 0;
	}
}

void getLogin()//登录该用户
{
	user H = load();
	if (find(inName, H) == 0)
	{
		printf("未查找到账户\n");
		regis(inName, H);
		printf("账户注册成功\n");
	}
	else
		printf("登录成功:\n");
	wcscpy(name, inName);
	wprintf(L"登陆账户：%ls\n", name);
}

user create(int x)
{
	user p = (user)malloc(sizeof(users));
	while (p == NULL)
		p = (user)malloc(sizeof(users));
	p->score = x;
	p->next = NULL;
	return p;
}

user load()
{
	FILE* fp;
	fp = fopen("rank.txt", "r");
	user head = create(0);
	head->name[0] = '\0';
	head->next = NULL;
	user q = head;
	user p;

	while (true)
	{
		p = create(0);
		size_t bytesRead = fread(p, sizeof(struct users), 1, fp);
		if (bytesRead != 0)//当文件未结束时，完全读取成功，则继续连接到已读取结点
		{
			q->next = p;
			q = q->next;
		}
		else if (bytesRead == 0)//文件结束
		{
			free(p);//释放最后一次分配但未使用的内存
			break;
		}
	}
	fclose(fp);
	printf("打开文件成功：%p\n", head);
	return head;
}

int find(wchar_t* in, user H)//查询该用户是否存在
{
	while (H)
	{
		if (wcscmp(H->name, in) == 0)
			return 1;
		H = H->next;
	}
	return 0;
}

void foutput(user head)//将链表写入文件
{
	FILE* fp;
	fp = fopen("rank.txt", "w");
	user p = head->next;
	while (p)
	{
		fwrite(p, sizeof(users), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void regis(wchar_t* in, user H)//注册新用户
{
	user p = H;
	while (p->next)
		p = p->next;
	p->next = create(0);
	p = p->next;
	wcscpy(p->name, in);
	foutput(H);
}

void printLink()//测试用
{
	user H = load()->next;
	while (H)
	{
		printf("用户:-%ld\n", H->score);
		wprintf(L"-%ls\n", H->name);
		H = H->next;
	}
}

void login()//登录界面选项
{
	flag = '0';
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4 - 50, _T("1 删除用户"));
	outtextxy(width / 4 - 80, height / 4, _T("2 更改用户名"));
	outtextxy(width / 4 - 80, height / 4 + 50, _T("3 登录"));
	outtextxy(width / 4 - 80, height / 4 + 100, _T("4 返回主菜单"));
	FlushBatchDraw();
	flag = _getch();
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4')
		flag = _getch();
	if (flag == '4')
		return;
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4, _T("请输入用户名："));
	FlushBatchDraw();
	getName();

	switch (flag)
	{
	case'1':
		remove();
		break;
	case'2':
		exchange();
		break;
	case'3':
		getLogin();
		break;
	}
}

void Vistor_Login()//游客登录
{
	wchar_t Vister[] = _T("Vistor");
	wcscpy(name, Vister);
}

user finduser(user H, wchar_t* text)//返回用户节点
{
	printf("开始查找用户结点：\n");
	while (H)
	{
		printf("查找中...\n");
		if (wcscmp(H->name, text) == 0)
		{
			printf("查找到用户结点！\n");
			wprintf(L"%ls\n", H->name);
			return H;
		}
		H = H->next;
	}
	printf("未找到匹配的用户。\n");
	return NULL;
}

void update_Score(int score)//更新该用户分数
{
	user H = load();
	if (H == NULL)
	{
		printf("无法加载用户信息\n");
		return;
	}
	user p = finduser(H, name);
	if (p == NULL)
	{
		printf("未找到当前用户\n");
		return;
	}
	if (score > p->score)
	{
		p->score = score;
		printf("分数更新: %d\n", p->score);
	}
	printLink();
	foutput(H);
}

void remove()//移除用户
{
	user H = load(), p = H, q = H;
	while (p)
	{
		if (wcscmp(inName, p->name) == 0)
		{
			q->next = p->next;
			printf("用户删除成功\n");
			foutput(H);
			Vistor_Login();
			return;
		}
		q = p;
		p = p->next;
	}
	printf("该用户不存在\n");
}

void exchange()//修改用户名
{
	printf("exchange()---start:\n");
	user H = load(), p = finduser(H, inName);
	if (NULL == p)
		return;
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4, _T("请输入新名称："));
	FlushBatchDraw();
	getName();
	wcscpy(p->name, inName);
	wcscpy(name, inName);
	foutput(H);
}