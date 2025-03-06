#include"flappy_bird.h"

wchar_t inName[100];
wchar_t input;
char flag;

void getName()//���ռ������벢��ʾ
{
	static int flag0 = 0;
	int i = 0;
	input = '\0';
	inName[0] = '\0';
	while (input != 13)
	{
		//��ʾ����������
		input = _getch();
		cleardevice();
		start();
		if (flag == '2' && flag0 == 0)
			outtextxy(width / 4 - 80, height / 4, _T("�������û�����"));
		else if (flag == '2' && flag0 == 1)
			outtextxy(width / 4 - 80, height / 4, _T("�����������ƣ�"));
		else
			outtextxy(width / 4 - 80, height / 4, _T("�������û�����"));
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

void getLogin()//��¼���û�
{
	user H = load();
	if (find(inName, H) == 0)
	{
		printf("δ���ҵ��˻�\n");
		regis(inName, H);
		printf("�˻�ע��ɹ�\n");
	}
	else
		printf("��¼�ɹ�:\n");
	wcscpy(name, inName);
	wprintf(L"��½�˻���%ls\n", name);
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
		if (bytesRead != 0)//���ļ�δ����ʱ����ȫ��ȡ�ɹ�����������ӵ��Ѷ�ȡ���
		{
			q->next = p;
			q = q->next;
		}
		else if (bytesRead == 0)//�ļ�����
		{
			free(p);//�ͷ����һ�η��䵫δʹ�õ��ڴ�
			break;
		}
	}
	fclose(fp);
	printf("���ļ��ɹ���%p\n", head);
	return head;
}

int find(wchar_t* in, user H)//��ѯ���û��Ƿ����
{
	while (H)
	{
		if (wcscmp(H->name, in) == 0)
			return 1;
		H = H->next;
	}
	return 0;
}

void foutput(user head)//������д���ļ�
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

void regis(wchar_t* in, user H)//ע�����û�
{
	user p = H;
	while (p->next)
		p = p->next;
	p->next = create(0);
	p = p->next;
	wcscpy(p->name, in);
	foutput(H);
}

void printLink()//������
{
	user H = load()->next;
	while (H)
	{
		printf("�û�:-%ld\n", H->score);
		wprintf(L"-%ls\n", H->name);
		H = H->next;
	}
}

void login()//��¼����ѡ��
{
	flag = '0';
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4 - 50, _T("1 ɾ���û�"));
	outtextxy(width / 4 - 80, height / 4, _T("2 �����û���"));
	outtextxy(width / 4 - 80, height / 4 + 50, _T("3 ��¼"));
	outtextxy(width / 4 - 80, height / 4 + 100, _T("4 �������˵�"));
	FlushBatchDraw();
	flag = _getch();
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4')
		flag = _getch();
	if (flag == '4')
		return;
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4, _T("�������û�����"));
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

void Vistor_Login()//�ο͵�¼
{
	wchar_t Vister[] = _T("Vistor");
	wcscpy(name, Vister);
}

user finduser(user H, wchar_t* text)//�����û��ڵ�
{
	printf("��ʼ�����û���㣺\n");
	while (H)
	{
		printf("������...\n");
		if (wcscmp(H->name, text) == 0)
		{
			printf("���ҵ��û���㣡\n");
			wprintf(L"%ls\n", H->name);
			return H;
		}
		H = H->next;
	}
	printf("δ�ҵ�ƥ����û���\n");
	return NULL;
}

void update_Score(int score)//���¸��û�����
{
	user H = load();
	if (H == NULL)
	{
		printf("�޷������û���Ϣ\n");
		return;
	}
	user p = finduser(H, name);
	if (p == NULL)
	{
		printf("δ�ҵ���ǰ�û�\n");
		return;
	}
	if (score > p->score)
	{
		p->score = score;
		printf("��������: %d\n", p->score);
	}
	printLink();
	foutput(H);
}

void remove()//�Ƴ��û�
{
	user H = load(), p = H, q = H;
	while (p)
	{
		if (wcscmp(inName, p->name) == 0)
		{
			q->next = p->next;
			printf("�û�ɾ���ɹ�\n");
			foutput(H);
			Vistor_Login();
			return;
		}
		q = p;
		p = p->next;
	}
	printf("���û�������\n");
}

void exchange()//�޸��û���
{
	printf("exchange()---start:\n");
	user H = load(), p = finduser(H, inName);
	if (NULL == p)
		return;
	cleardevice();
	start();
	outtextxy(width / 4 - 80, height / 4, _T("�����������ƣ�"));
	FlushBatchDraw();
	getName();
	wcscpy(p->name, inName);
	wcscpy(name, inName);
	foutput(H);
}