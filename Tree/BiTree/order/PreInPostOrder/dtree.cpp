#include<stdio.h>
#include<malloc.h>

/*
    二叉树的遍历

        二叉树的递归特性：
            1. 要么是个空树
            2. 要么就是由 “根节点 + 左子树 + 右子树” 组成的二叉树

        前序遍历
            根->左->右
        中序遍历
            左->根->右
        后序遍历
            左->右->根
*/

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *LeftNode;
    struct BiTNode *RightNode;
} BiTNode, *BiTree;

//前序遍历（递归）
void PerOrder(BiTree node)
{
    if (node == NULL) //判断是否为叶节点
    {
        return;
    }
    printf("%c",node->data); //输出当前节点的值
    PerOrder(node->LeftNode); //往左找
    PerOrder(node->RightNode); //往右找
}

//中序遍历（递归）
void InOrder(BiTree node)
{
    if (node == NULL) //判断是否为叶节点
    {
        return;
    }
    InOrder(node->LeftNode); //往左找
    printf("%c",node->data); //输出当前节点的值
    InOrder(node->RightNode); //往右找
}

//后序遍历（递归）
void PostOrder(BiTree node)
{
    if (node == NULL) //判断是否为叶节点
    {
        return;
    }
    PostOrder(node->LeftNode); //往左找
    PostOrder(node->RightNode); //往右找
    printf("%c",node->data); //输出当前节点的值
}

int main(void)
{
    BiTNode RootNode, BNode, CNode, DNode, ENode, FNode, GNode; //初始化树的各个节点
    RootNode.data = 'A';

    RootNode.LeftNode = &BNode;
    RootNode.RightNode = &CNode;

    BNode.data = 'B';
    BNode.LeftNode = &DNode;
    BNode.RightNode = &ENode;

    DNode.data = 'D';
    DNode.LeftNode = NULL;
    DNode.RightNode = &GNode;

    GNode.data = 'G';
    GNode.RightNode = GNode.LeftNode = NULL;

    ENode.data = 'E';
    ENode.LeftNode = ENode.RightNode = NULL;

    CNode.data = 'C';
    CNode.LeftNode = &FNode;
    CNode.RightNode = NULL;

    FNode.data = 'F';
    FNode.RightNode = FNode.LeftNode = NULL;

    printf("Per:\n");
    PerOrder(&RootNode);

    printf("\nIn:\n");
    InOrder(&RootNode);

    printf("\nPost:\n");
    PostOrder(&RootNode);

    return 0;
}