#include"BinTree.h"

#include"BinTree.c"
#include"BtStack.c"

int main (void)
{
    int depth=0;
    scanf("%d",&depth);
    BTreeNode * root=(BTreeNode * )malloc(sizeof(BTreeNode));
    root=TestCreatBT(depth);
    CirPostOrder(root);
    printf("\n");
    RecPostOrder(root);
    return 0;
}