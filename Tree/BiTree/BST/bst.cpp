#include<stdio.h>
#include<malloc.h>

/*
    二叉排序树(BST)

    定义:
        二叉排序树，又称二叉查找树
        一棵二叉树或者是空二叉树，或者是具有如下性质的二叉树：
            1）左子树上的所有节点的关键字均小于根节点的关键字
            2）右子树上的所有节点的关键字均大于根节点的关键字
            3）左子树和右子树又各是一棵二叉排序树
        
        即 左子树节点值 < 根节点值 < 右子树节点值

        因此进行中序遍历，可以得到一个递增的有序序列（访问顺序为：左 根 右 ）



    时间复杂度、查找效率分析
        
        查找长度 —— 在查找运算中，需要对比关键字的次数称为查找长度，反映了操作时间复杂度

        查找成功
            平均查找长度ASL = （层次号 x 当前层的节点数）/ 总节点数
        查找失败
            平均查找长度ASL = （每层叶节点的左右孩子的个数 x 叶节点所在层数）/ 所有叶节点的个数

        最好的情况：
            满足完全二叉树
        最坏的情况：
            树的高度 = 节点数，平均查找长度为O(n)
*/

typedef int ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *Lchild;
    struct BSTNode *Rchild;
} BSTNode, *BSTree;


/*
    二叉排序树的查找

    若树非空，则目标值与根节点值比较：
    若相等，则查找成功；
    若小于根节点的值，则往左子树查找，否则往右子树上查找；

    查找成功，则返回节点指针，否则失败则返回NULL；

*/

//非递归实现
//最坏空间复杂度O（1），即原地操作
BSTNode* FindNode(BSTree T, ElemType target)
{
    BSTNode* cur = T;
    while (cur != NULL && cur->data != target)
    {
        if (cur->data > target)
        {
            cur = cur->Lchild;
        }
        else
        {
            cur = cur->Rchild;
        }
    }
    return cur;
}

//递归实现
//最坏空间复杂度为O（h），h为树的高度
BSTNode *FindNode_(BSTree T, ElemType target)
{
    if (T == NULL)
    {
        return NULL;
    }
    if (T->data == target)
    {
        return T;
    }
    else{
        if (T->data > target) 
        {
            FindNode_(T->Lchild, target); //大于当前节点的值，往他的左孩子节点找
        }
        else
        {
            FindNode_(T->Rchild, target); //小于当前节点的值，往他的右孩子节点找
        }
    }
}

/*
    二叉排序树的插入

        思路：
        若原二叉排序树为空，则直接插入节点，否则，若关键字小于根节点，则插入到左子树，若关键字大于根节点，则插入到右子树

        最坏空间复杂度：O（h）
*/
int BST_Insert(BSTree &T, int sdata)
{
    if (T == NULL)
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = sdata;
        T->Lchild = NULL;
        T->Rchild = NULL;
        return 1;
    }
    else if (T->data == sdata) //二叉排序树不允许有两个节点的关键字的值相同
    {
        return 0; //若排序树中已经存在相同关键字的节点，则插入失败
    }
    
    else
    {
        if (sdata < T->data)
        {
            BST_Insert(T->Lchild, sdata); //若关键字小于节点关键字，则往左孩子节点插入
        }
        else
        {
            BST_Insert(T->Rchild, sdata); //若关键字大于节点关键字，则往右孩子节点插入
        }
    }
}


/*
    二叉排序树的构造
    
        按照str[]中的关键字序列建立二叉排序树

        不同的关键字序列可能得到同款的二叉排序树
        也可能得到不同的二叉排序树

*/
void Create_BST(BSTree &T, int Str[], int n)
{
    T = NULL;
    int i = 0;
    while (i < n)
    {
        BST_Insert(T, Str[i]);
        i++;
    }
}

/*
    二叉排序树的删除

        分以下情况讨论：
        
        1. 删除对象为叶子节点，则直接删除即可
        2. 删除对象只有左子树或只有右子树, 则让他的左子树或者右子树代替他

        3. 若节点有左右子树，
            1）可以直接让他的直接后继（也就是右子树中序遍历序列的第一个节点，也就是右子树最左下的节点，方法参考搜索树的找后继方法）
               代替他，然后从二叉排序树中删去这个直接后继，这样就转换成了第一种或第二种情况

            2）也可以直接让他的直接前驱（也就是左子树中序遍历序列的第一个节点，也就是左子树最右下的节点，方法参考搜索树的找前驱方法）
               代替他，然后从二叉排序树中删去这个直接后继，这样就转换成了第一种或第二种情况
*/

int main(void)
{
    
}
