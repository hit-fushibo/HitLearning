#ifndef SEQ_LIST_H
#define SEQ_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLENGTH 100

typedef struct SeqList
{
    int data[MAXLENGTH];
    int last;
}SeqList;


void CreatList(SeqList * l);//创建数组线性表
void InitializeList(SeqList*a,int num);//初始化线性表前num项
void OutPut(SeqList *l);//输出线性表
int IsZero(SeqList * l);//判断非空 空->0 非空->1
void Insert(SeqList * l,int a);//在线性表的第a项后插入一项
void Delete(SeqList * l,int a);//删除第a项
void Modify(SeqList * l,int a);//编辑第a项
int  Search(SeqList * l,int a);//查询第a项
void DeleteRepeatElement(SeqList * l);//删除有序表的重复项
void DeleteElement(SeqList * l,int element);//删除表中值为element的项
void Inverted(SeqList * l);//逆置表
void MoveLeft(SeqList * l,int k);//左移k项
void MoveRight(SeqList * l,int k);//右移k项
void Merge(SeqList * l1,SeqList *l2,SeqList ** re);//合并有序表

#endif