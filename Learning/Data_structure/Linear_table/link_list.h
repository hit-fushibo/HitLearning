#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct intlink
{
	int data;
	struct intlink *next;
} intlink;

intlink *GetLast(intlink *head);			  //获取链表最后一位的地址
intlink *GetSecondLast(intlink *head);		  //获取倒数第二位地址
int InsertNode(intlink *head, int i);		  //在head链表的第i个节点后插入一个节点
int DeleteNode(intlink *head, int i);		  //删除head链表的第i个节点
int ModifyNode(intlink *head, int i);		  //修改head链表的第i个节点
int SearchNode(intlink *head, int i);		  //查询head链表的第i个节点数据
int DeletElement(intlink *head, int element); //删除链表所有data为element的节点
int DeletRepeatElement(intlink *head);		  //删除有序链表重复元素
int InvertedLinkList(intlink *head);		  //链表逆置
int MoveLeft(intlink *head, int k);			  //左移k位
int MoveRight(intlink *head, int k);		  //右移k位
intlink *MergeList(intlink *l1, intlink *l2); //合并两个有序链表
void OutPutLink(intlink *l);				  //输出链表

#endif