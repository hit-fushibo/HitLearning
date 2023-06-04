#include "link_list.h"

//在head链表的第i个节点后插入一个节点
int InsertNode(intlink *head, int i)
{
    int cut = 0, flag = 1;
    intlink *p = head->next;
    for (cut = 1; cut != i; cut++)
    {
        if (p->next != NULL)
            p = p->next;
        else
        {
            if (cut == i)
            {
                break;
            }
            else
            {
                flag = 0;
                return flag;
            }
        }
    }
    intlink *q = (intlink *)malloc(sizeof(intlink));
    scanf("%d", &q->data);
    q->next = p->next;
    p->next = q;
    return flag;
}

//输出链表
void OutPutLink(intlink *l)
{
    intlink *p=l;
    for(;p->next!=NULL;p=p->next)
    {
        printf("%d ",p->next->data);
    }
    printf("\n");
}

//删除head链表的第i个节点
int DeleteNode(intlink *head, int i)
{
    int cut = 0;
    intlink *p = head, *q;
    for (cut = 1; cut != i; cut++)
    {
        if (p->next == NULL)
            return 0;
        else
            p = p->next;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

//修改head链表的第i个节点
int ModifyNode(intlink *head, int i)
{
    int cut = 0;
    intlink *p = head, *q;
    for (cut = 1; cut != i; cut++)
    {
        if (p->next == NULL)
            return 0;
        else
            p = p->next;
    }
    scanf("%d", &p->next->data);
    return 1;
}

//查询head链表的第i个节点数据
int SearchNode(intlink *head, int i)
{
    int cut = 0;
    intlink *p = head, *q;
    for (cut = 1; cut != i; cut++)
    {
        if (p->next == NULL)
            return 0;
        else
            p = p->next;
    }
    printf("the %d node data is %d\n", i, p->next->data);
    return 1;
}

//删除链表所有data为element的节点
int DeletElement(intlink *head, int element)
{
    intlink *p = head, *q;
    while (p->next != NULL)
    {
        if (p->next->data == element)
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
    if (p->data == element)
    {
        for (q = head; q->next != p; q++)
            ;
        q->next = NULL;
        free(p);
    }
    return 1;
}

//删除有序链表重复元素
int DeletRepeatElement(intlink *head)
{
    intlink *p = head->next, *q;
    while (p != NULL && p->next != NULL)
    {
        if (p->data == p->next->data)
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
            p = p->next;
    }
    return 0;
}

//获取链表最后一位的地址
intlink *GetLast(intlink *head)
{
    intlink *q = head;
    for (; q->next != NULL; q = q->next)
        ;
    return q;
}

//获取倒数第二位地址
intlink *GetSecondLast(intlink *head)
{
    intlink *q = head;
    if (q->next == NULL)
    {
        printf("get second last error\n");
        exit(0);
    }
    for (; q->next->next != NULL; q = q->next)
        ;
    return q;
}

//链表逆置
int InvertedLinkList(intlink *head)
{
    intlink *p, *q;
    p = head->next;
    if (p == NULL)
        return 0;
    if (p->next == NULL)
        return 1;
    head->next = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        q->next = head->next;
        head->next = q;
    }
    return 1;
}

//左移k位
int MoveLeft(intlink *head, int k)
{
    int i = 0;
    intlink *q=head;
    if (q->next == NULL)
        return 0;
    if (q->next->next == NULL)
        return 1;
    for (i = 0; i < k; i++)
    {
        q = GetLast(head);
        q->next = head->next;
        head->next = head->next->next;
        q->next->next = NULL;
    }
    return 1;
}

//右移k位
int MoveRight(intlink *head, int k)
{
    int i = 0;
    intlink *q=head;
    if (q->next == NULL)
        return 0;
    if (q->next->next == NULL)
        return 1;
    for (i = 0; i < k; i++)
    {
        q = GetSecondLast(head);
        q->next->next = head->next;
        head->next = q->next;
        q->next = NULL;
    }
    return 1;
}

//合并两个有序链表
intlink *MergeList(intlink *l1, intlink *l2)
{
    if (l1 == NULL)
    {
        return l2;
    }
    if (l2 == NULL)
    {
        return l1;
    }
    intlink *re;
    if (l1->data > l2->data)
    {
        re = l2;
        re->next = MergeList(l1, l2->next);
    }
    else
    {
        re = l1;
        re->next = MergeList(l1->next, l2);
    }
    return re;
}