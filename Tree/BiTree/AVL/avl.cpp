#include<stdio.h>
#include<malloc.h>

/*
    平衡二叉树

        平衡二叉树，又称平衡树，树上任一节点的左子树和右子树的
        高度之差不超过1

        注意：平衡二叉树是基于二叉排序树的！仍然具有左节点 < 根节点 < 右节点的特性！

        节点的平衡因子 = 左子树高 - 右子树高

    调整最小不平衡子树（每次调整的对象）

        LL 在A的左孩子的左子树中插入导致的不平衡
        RR 在A的右孩子的右子树中插入导致的不平衡
        LR 在A的左孩子的右子树中插入导致的不平衡
        RL 在A的右孩子的左子树中插入导致的不平衡

    在插入操作中，只要将最小不平衡子树调整平衡，则其他祖先节点都会回复平衡

    算法思路：
        1. 找到最小不平衡子树的根节点
        2. 根据上面四种情况进行左右旋的恢复平衡操作
        3. 检查恢复后是否仍然满足二叉排序树的特性
*/

typedef struct AVLNode
{
    int key;
    int balance; //平衡因子
    struct AVLNode *Lchild;
    struct AVLNode *Rchild;
} AVLNode, *AVLTree;


