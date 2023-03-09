#include "Code.h"

//计算每个字符权值
int GetWeights(char *s, CW **Weight)
{
    float AllWeight[127] = {0}; //存储字符权值
    int i = 0, len = strlen(s), kind = 0, j = 0;
    for (i = 0; i < len; i++)
    {
        AllWeight[s[i]]++;
    }
    for (i = 0; i < 127; i++)
    {
        if (AllWeight[i] != 0)
        {
            kind++;
            AllWeight[i] /= len;
        }
    }
    *Weight = (CW *)malloc(sizeof(CW) * kind);
    for (i = 0; i < 127; i++)
    {
        if (AllWeight[i] != 0)
        {
            (*Weight)[j].data = i;
            (*Weight)[j].weight = AllWeight[i];
            j++;
        }
    }
    return kind;
}

//根据权值数组创建哈夫曼树节点数组
HuT *CreatNode(CW *a, int nums)
{
    int i = 0;
    HuT *h = (HuT *)malloc(sizeof(HuT) * nums);
    for (i = 0; i < nums; i++)
    {
        h[i].element = a[i].data;
        h[i].weight = a[i].weight;
        h[i].Lchild = NULL;
        h[i].Rchild = NULL;
    }
    return h;
}

//根据权值数组构建哈夫曼树
HuT *CreatHuffman(HuT *weight, int len)
{
    int i = 1, n = len;
    HuT *temp;
    for (i = 1; i < n; i++)
    {
        temp = (HuT *)malloc(sizeof(HuT));
        temp->Lchild = (HuT *)malloc(sizeof(HuT));
        temp->Rchild = (HuT *)malloc(sizeof(HuT));
        HuT x, y;
        x = GetMin(weight, len);
        len--;
        y = GetMin(weight, len);
        len--;
        *temp->Lchild = x;
        *temp->Rchild = y;
        temp->element = '\0';
        temp->weight = x.weight + y.weight;
        Insert(weight, *temp, len);
        len++;
    }
    temp = (HuT *)malloc(sizeof(HuT));
    *temp = GetMin(weight, len);
    len--;
    return temp;
}

//获取权值最小的节点并删除
HuT GetMin(HuT *weight, int len)
{
    int i = 0, j = 0;
    HuT temp;
    temp.weight = 2;
    for (i = 0; i < len; i++)
    {
        if (weight[i].weight < temp.weight)
        {
            j = i;
            temp.weight = weight[i].weight;
        }
    }
    temp = weight[j];
    for (j = j + 1; j < len; j++)
    {
        weight[j - 1] = weight[j];
    }
    weight[len - 1].weight = 0;
    return temp;
}

//将新节点插入节点数组
void Insert(HuT *weight, HuT element, int len)
{
    weight[len] = element;
}

//编码
void Code(char **s, HuT *root, char *buffer, int depth)
{
    if (!root)
        return;

    buffer[depth] = '0';
    Code(s, root->Lchild, buffer, depth + 1);
    buffer[depth] = '1';
    Code(s, root->Rchild, buffer, depth + 1);
    buffer[depth] = '\0';
    if (root->Lchild == NULL && root->Rchild == NULL)
    {
        s[codectn][0] = root->element;
        s[codectn][1] = ' ';
        int i;
        for (i = 0; buffer[i] != '\0'; i++)
        {
            s[codectn][i + 2] = buffer[i];
        }
        s[codectn][i + 2] = '\0';
        codectn++;
    }
}

//哈夫曼编码
void HuffmanCode(char **s, HuT *root, char *buffer, int depth)
{
    codectn = 0;
    Code(s, root, buffer, 0);
    codectn = 0;
}

//将data的内容根据hufcode编码到code
void CodeString(char *data, char **Hufcode, char *code)
{
    int data_i = 0, huf_i = 0, code_i = 0, len = strlen(data), j = 0;
    for (data_i = 0; data_i < len; data_i++)
    {
        for (huf_i = 0; data[data_i] != *Hufcode[huf_i]; huf_i++)
            ;
        for (j = 2; Hufcode[huf_i][j] != '\0'; j++)
        {
            code[code_i] = Hufcode[huf_i][j];
            code_i++;
        }
    }
    code[code_i] = '\0';
}