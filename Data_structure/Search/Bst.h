#ifndef BST_H
#define BST_H

#include"Defination.h"


int IsEmpty(T* root);
void CreatBst(T* root,int element);//创建BST
int Delete(T* root,int element);//删除bst中值为element的节点
int GetNext(T* root);
int Search(T* root,int element);//查找
int* Sort(T* root,int num);//排序
void Inorder(T* root,int *order);

int BinSearch(int *num,int element);//二分查找


int* SortedInt(int num);//1-num的有序数组
int* RandomInt(int num);//1-num的随机不重复数组

int TestSorted();


#endif