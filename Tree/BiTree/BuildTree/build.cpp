#include<stdio.h>
#include<malloc.h>

/*
    由遍历序列构造二叉树

        若只给出一颗二叉树的 前/中/后/层 序遍历序列的一种，不能唯一确定一颗二叉树

    1. 前序 + 中序
    2. 后序 + 中序
    3. 层序 + 中序

    只有满足以上三种关系的两两组合才能确定唯一的二叉树
*/

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *LeftChild;
    struct BiTNode *RightChild;
} BiTNode, *BiTree;

int main(void)
{
    
} 