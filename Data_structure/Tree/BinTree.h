#ifndef BINTREE_H
#define BINTREE_H

#include "BtQue.h"

void Empty(BTreeNode *bt);                                  //建立一颗空的二叉树
int IsEmpty(BTreeNode *bt);                                 //判断二叉树是否为空，空返回0，否则返回1
BTreeNode *CreatBT(int data, BTreeNode *LT, BTreeNode *RT); //建立一颗新的二叉树，数据为data，左子树和右子树分别为LT和RT
BTreeNode *Lchild(BTreeNode *bt);                           //返回bt的左儿子，若无左儿子，返回空
BTreeNode *Rchild(BTreeNode *bt);                           //返回bt的右儿子，若无右儿子，返回空
int Data(BTreeNode *bt);                                    //返回bt的根节点的数据域
char *CreatBt(BTreeNode **bt, char *p);                     //根据字符串p生成二叉树，p先序序列，data之间用空格区分，data为空格代表为空节点
BTreeNode *TestCreatBT(int depth);                          //生成测试用二叉树，顺序为先序顺序，深度为depth的满二叉树，手动输入数据
void RecPreOrder(BTreeNode *bt);                            //递归先序遍历
void RecInOrder(BTreeNode *bt);                             //递归中序遍历
void RecPostOrder(BTreeNode *bt);                           //递归后序遍历
void CirPreOrder(BTreeNode *bt);                            //循环先序遍历
void CirInOrder(BTreeNode *bt);                             //循环中序遍历
void CirPostOrder(BTreeNode *bt);                           //循环后序遍历
int JudgeEqul(BTreeNode *a, BTreeNode *b);                  //判断两个根节点是否相同
void LatOrder(BTreeNode *bt);                               //层序遍历二叉树
int JudgeCBT(BTreeNode *bt);                                //判断是否完全二叉树
void JudgeFunc(BTreeNode *bt, int i, char *lat);            //将二叉树以层序顺序输出到lat中T代表有数据，F代表无数据
int bin_wide[100] = {0};
int bin_width = -1;
void BinWide(BTreeNode *bt, int k); //求二叉树的宽度

#endif