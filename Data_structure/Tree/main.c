#include "BinTree.h"

#include "BinTree.c"
#include "BtStack.c"
#include "BtQue.c"

int main(void)
{
    BTreeNode *root = (BTreeNode *)malloc(sizeof(BTreeNode));
    char input[100] = {0};
    gets(input);
    CreatBt(&root, input);
    printf("RecPreOrder:\n");
    RecPreOrder(root);
    printf("\nRecInOrder:\n");
    RecInOrder(root);
    printf("\nRecPostOrder:\n");
    RecPostOrder(root);
    printf("\nCirPreOrder:\n");
    CirPreOrder(root);
    printf("CirInOrder:\n");
    CirInOrder(root);
    printf("\nCirPostOrder:\n");
    CirPostOrder(root);
    printf("\nLatOrder:\n");
    LatOrder(root);
    if (JudgeCBT(root))
        printf("Is Complete binary tree \n");
    else
        printf("Not Complete binary tree \n");
    BinWide(root, 0);
    printf("width: %d\n", bin_width);
    return 0;
}