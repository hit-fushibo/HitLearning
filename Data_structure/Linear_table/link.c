#include"link_list.h"
#include"link_list.c"

int main (void)
{
    intlink *head1=(intlink *)malloc(sizeof(intlink)),*head2=(intlink*)malloc(sizeof(intlink));
	intlink *p=(intlink *)malloc(sizeof(intlink)),*q;
	head1->next=NULL;head2->next=NULL;
	int ctn=-1;int num;
	printf("1:delet element\n2:delete repeat element\n3:inverted\n4:move left\n5:move right\n6:merge\n");
	printf("please enter the function you want to test:");
	scanf("%d",&ctn);
	switch (ctn)
	{
	case 1:
		{
			printf("please enter node number:");
			scanf("%d",&num);
			printf("enter %d element:\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			printf("please enter element to delete:");
			int element;
			scanf("%d",&element);
			//OutPutLink(head1);
			DeletElement(head1,element);
			OutPutLink(head1);
		}
		break;
	case 2:
		{
			printf("please enter node number:");
			scanf("%d",&num);
			printf("enter %d element(must be orderly):\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			//OutPutLink(head1);
			DeletRepeatElement(head1);
			OutPutLink(head1);
		}
		break;
	case 3:
		{
			printf("please enter node number:");
			scanf("%d",&num);
			printf("enter %d element:\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			//OutPutLink(head1);
			InvertedLinkList(head1);
			OutPutLink(head1);
		}
		break;
	case 4:
		{
			printf("please enter node number:");
			scanf("%d",&num);
			printf("enter %d element:\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			//OutPutLink(head1);
			int k;
			printf("enter the number of digits to move:");
			scanf("%d",&k);
			MoveLeft(head1,k);
			OutPutLink(head1);
		}
		break;
	case 5:
		{
			printf("please enter node number:");
			scanf("%d",&num);
			printf("enter %d element:\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			//OutPutLink(head1);
			int k;
			printf("enter the number of digits to move:");
			scanf("%d",&k);
			MoveRight(head1,k);
			OutPutLink(head1);
		}
		break;
	case 6:
		{
			printf("please enter list1 node number:");
			scanf("%d",&num);
			printf("enter %d element(must be orderly):\n",num);
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head1->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			printf("please enter list2 node number:");
			scanf("%d",&num);
			printf("enter %d element(must be orderly):\n",num);
			p=(intlink*)malloc(sizeof(intlink));
			for(int i=0;i<num;i++)
			{
				if(i==0)
				{
					head2->next=p;
					scanf("%d",&p->data);
					p->next=NULL;
				}
				else
				{
					q=(intlink *)malloc(sizeof(intlink));
					q->next=NULL;
					scanf("%d",&q->data);
					p->next=q;
					p=q;
				}
			}
			//OutPutLink(head1);OutPutLink(head2);
			intlink*re=(intlink*)malloc(sizeof(intlink));
			re->next=MergeList(head1->next,head2->next);
			OutPutLink(re);
		}
		break;
	default:
		{
			printf("error wrong number\n");
		}
		break;
	}
	getchar();
    printf("press Enter to exit");
    getchar();
    return 0;
}