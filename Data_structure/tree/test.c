#include"BinTree.h"

#include"BinTree.c"
#include"BtStack.c"
#include"BtQue.c"

int main (void)
{
    //BTreeNode * root=(BTreeNode * )malloc(sizeof(BTreeNode));
    //int depth=0;
    //scanf("%d",&depth);
    //root=TestCreatBT(depth);
    
    BTreeNode *root=(BTreeNode *)malloc(sizeof(BTreeNode));
    char test[100]={0};
    gets(test);
    CreatBt(&root,test);
    LatOrder(root);
    BinWide(root,0);
    printf("%d",bin_width);
    return 0;
}