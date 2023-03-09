#include <cstdio>

using namespace std;

typedef long long LL;
typedef struct Node *Position;
typedef Position RingList;
struct Node
{
    int data;
    Position prevXORnext;
};

void ClockWise(RingList rL, Position prev2);             //顺时针
void AntiClockWise(RingList rL, Position next);          //逆时针
RingList CreateRingList(Position *prev, Position *next); //创建环形链表

int main()
{
    Position prev, next;
    RingList rL = CreateRingList(&prev, &next);

    printf("顺时针：");
    ClockWise(rL, prev);
    printf("逆时针：");
    AntiClockWise(rL, next);

    return 0;
}

RingList CreateRingList(Position *prevNode, Position *nextNode)
{
    RingList rL = new Node; //头结点
    int x;
    Position p = rL;
    Position prev = 0;   //初始头节点的异或就相当于next，而0异或某个数等于它本身
    Position next;
    Position firstP = NULL, secondP = NULL;
    int n = 0;
    while (scanf("%d", &x) != EOF)
    {
        n++;
        Position newP = new Node;
        if (n == 1)
            firstP = newP;
        if (n == 2)
            secondP = newP;     //保存第二个节点的指针便于之后更新第一个节点
        newP->data = x;
        next = newP;
        p->prevXORnext = (Position)((LL)prev ^ (LL)next);
        prev = p;
        p = newP;
    }
    //将尾指针的链域与第一个节点相关联
    p->prevXORnext = (Position)((LL)prev ^ (LL)firstP);
    //形成环后，更新第一个节点的链域
    firstP->prevXORnext = (Position)((LL)p ^ (LL)secondP);
    *prevNode = p;
    *nextNode = secondP;
    return rL;
}
void ClockWise(RingList rL, Position prev2)
{
    Position firstP = rL->prevXORnext;
    Position prev1 = firstP;
    printf("%d", firstP->data);
    Position cur = (Position)((LL)prev1->prevXORnext ^ (LL)(prev2));
    while (cur != firstP)
    {
        printf(" %d", cur->data);
        prev2 = prev1;
        prev1 = cur;
        cur = (Position)((LL)prev1->prevXORnext ^ (LL)(prev2));
    }
    printf("\n");
}

void AntiClockWise(RingList rL, Position next2)
{
    Position firstP = rL->prevXORnext;
    Position next1 = firstP;
    printf("%d", firstP->data);
    Position cur = (Position)((LL)next1->prevXORnext ^ (LL)(next2));
    while (cur != firstP)
    {
        printf(" %d", cur->data);
        next2 = next1;
        next1 = cur;
        cur = (Position)((LL)next1->prevXORnext ^ (LL)(next2));
    }
    printf("\n");
}