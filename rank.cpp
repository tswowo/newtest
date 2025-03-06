#include"flappy_bird.h"

user rank_Sort(user list)
{
    if ((list->next == NULL) || (list->next->next == NULL))
        return list;
    //����
    user next, head, pre, cur, end, temp;
    head = list;
    end = NULL;
    while (head->next != end)
    {
        for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
        {
            if (cur->score < next->score)
            {
                cur->next = next->next;
                pre->next = next;
                next->next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
    return head;
}

void free_rank(user H)
{
	user p = H, q;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

// �������а����
void rank_Show() {
    printf("�Ѵ����а�\n");
    cleardevice();
    FlushBatchDraw();
    //���ر���
    IMAGE background;
    loadimage(&background, _T("pictures\\����.png"));
    putimage(0, 0, &background);

    //����������ʽ
    settextstyle(40, 0, _T("����"));//�������ִ�С������
    setbkmode(TRANSPARENT);//��������͸��
    outtextxy(0, 0, _T("���а�"));

    //��ȡ���а�����
    user H = load();
    if (H == NULL) {
        printf("�޷���ȡ���а�����");
        return;
    }
    //����������
    H = rank_Sort(H);

    //�������а�����
    int y = 100, num = 1;
    user p = H->next;
    while (p) {
        wchar_t text[50];
        _itow_s(num, text, 50, 10);
        outtextxy(40, y, text);
        _itow_s(p->score, text, 50, 10);
        outtextxy(110, y, text);
        wcscpy(text, p->name);
        outtextxy(200, y, text);
        num++;
        y += 40;
        p = p->next;
    }
    outtextxy(200, y, _T("��������������˵�"));
    FlushBatchDraw();
    _getch();
	free_rank(H);
}