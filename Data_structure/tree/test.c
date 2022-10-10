#include"BinTree.h"

#include"BinTree.c"
#include"BtStack.c"
#include"BtQue.c"

int main (void)
{
    int depth=0;
    scanf("%d",&depth);
    BTreeNode * root=(BTreeNode * )malloc(sizeof(BTreeNode));
    root=TestCreatBT(depth);
    LatOrder(root);
    return 0;
}