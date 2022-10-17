#ifndef CODE_H
#define CODE_H

#include "Define.h"

int GetWeights(char *s, CW **weight);                           //计算每个字符权值
HuT *CreatNode(CW *a, int nums);                                //根据权值数组创建哈夫曼树节点数组
HuT *CreatHuffman(HuT *weight, int len);                        //根据哈夫曼树节点数组构建哈夫曼树
HuT GetMin(HuT *weight, int len);                               //获取权值最小的节点并删除
void Insert(HuT *weight, HuT element, int len);                 //将新节点插入节点数组
void Code(char **s, HuT *root, char *buffer, int depth);        //编码
void HuffmanCode(char **s, HuT *root, char *buffer, int depth); //哈夫曼编码
void CodeString(char *data, char **Hufcode, char *code);        //将data的内容根据hufcode编码到code

#endif