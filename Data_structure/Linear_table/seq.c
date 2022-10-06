#include"seq_list.h"
#include"seq_list.c"

int main (void)
{
    SeqList *l1=(SeqList *)malloc(sizeof(SeqList));
    int ctn =-1;int num;int k;
    printf("1:delet element\n2:delete repeat element\n3:inverted\n4:move left\n5:move right\n6:merge\n");
	printf("please enter the function you want to test:");
	scanf("%d",&ctn);
    switch (ctn)
    {
    case 1:
        printf("please enter list number:");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        printf("please enter element to delete:");
        int element;
        scanf("%d",&element);
        //OutPut(l1);
        DeleteElement(l1,element);
        OutPut(l1);
        break;
    case 2:
        printf("please enter list number:");
        scanf("%d",&num);
        printf("enter %d element:(must be orderly)\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        //OutPut(l1);
        DeleteRepeatElement(l1);
        OutPut(l1);
        break;
    case 3:
        printf("please enter list number:");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        //OutPut(l1);
        Inverted(l1);
        OutPut(l1);
        break;
    case 4:
        printf("please enter list number:");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        printf("enter the number of digits to move:");
		scanf("%d",&k);
        //OutPut(l1);
        MoveLeft(l1,k);
        OutPut(l1);
        break;
    case 5:
        printf("please enter list number:");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        printf("enter the number of digits to move:");
		scanf("%d",&k);
        //OutPut(l1);
        MoveRight(l1,k);
        OutPut(l1);
        break;
    case 6:
        printf("please enter list1 number(must be orderly):");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l1);
        InitializeList(l1,num);
        SeqList *l2=(SeqList *)malloc(sizeof(SeqList));
        printf("please enter list2 number(must be orderly):");
        scanf("%d",&num);
        printf("enter %d element:\n",num);
        CreatList(l2);
        InitializeList(l2,num);
        //OutPut(l1);OutPut(l2);
        SeqList * r=(SeqList *)malloc(sizeof(SeqList));
        Merge(l1,l2,&r);
        OutPut(r);
        break;
    default:
        printf("error wrong number\n");
        break;
    }
    getchar();
    printf("press Enter to exit");
    getchar();
    return 0;
}