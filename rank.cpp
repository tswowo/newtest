#include"flappy_bird.h"

user rank_Sort(user list)
{
    if ((list->next == NULL) || (list->next->next == NULL))
        return list;
    //排序
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

// 绘制排行榜界面
void rank_Show() {
    printf("已打开排行榜\n");
    cleardevice();
    FlushBatchDraw();
    //加载背景
    IMAGE background;
    loadimage(&background, _T("pictures\\背景.png"));
    putimage(0, 0, &background);

    //设置字体样式
    settextstyle(40, 0, _T("宋体"));//设置文字大小，字体
    setbkmode(TRANSPARENT);//文字字体透明
    outtextxy(0, 0, _T("排行榜"));

    //读取排行榜数据
    user H = load();
    if (H == NULL) {
        printf("无法读取排行榜数据");
        return;
    }
    //调用排序函数
    H = rank_Sort(H);

    //绘制排行榜内容
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
    outtextxy(200, y, _T("按任意键返回主菜单"));
    FlushBatchDraw();
    _getch();
	free_rank(H);
}