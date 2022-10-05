#ifndef BINTREE_H
#define BINTREE_H

#include"BtStack.h"

void Empty(BTreeNode *bt);                                  //建立一颗空的二叉树
int IsEmpty(BTreeNode *bt);                                 //判断二叉树是否为空，空返回0，否则返回1
BTreeNode *CreatBT(int data, BTreeNode *LT, BTreeNode *RT); //建立一颗新的二叉树，数据为data，左子树和右子树分别为LT和RT
BTreeNode *Lchild(BTreeNode *bt);                           //返回bt的左儿子，若无左儿子，返回空
BTreeNode *Rchild(BTreeNode *bt);                           //返回bt的右儿子，若无右儿子，返回空
int Data(BTreeNode *bt);                                    //返回bt的根节点的数据域
BTreeNode *TestCreatBT(int depth);                          //生成测试用二叉树，顺序为先序顺序，深度为depth的满二叉树，手动输入数据
void RecPreOrder(BTreeNode *bt);                            //递归先序遍历
void RecInOredr(BTreeNode *bt);                             //递归中序遍历
void RecPostOrder(BTreeNode *bt);                           //递归后序遍历
void CirPreOrder(BTreeNode *bt);                            //循环先序遍历
void CirInOrder(BTreeNode *bt);                             //循环中序遍历
void CirPostOrder(BTreeNode *bt);                           //循环后序遍历

#endif