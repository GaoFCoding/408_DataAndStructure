#include<stdio.h>
#include<malloc.h>

/*
    将二叉树线索化，变为线索二叉树
    作用：
        方便从一个指定节点出发，找到其前驱，后继节点；方便遍历

    存储结构：
        在普通二叉树结点的基础上，增加两个标志位ltag和rtag

    三种线索二叉树
        1. 中序线索二叉树
        2. 先序线索二叉树
        3. 后序线索二叉树

    不依靠线索化来找前驱的算法思路：
        1. 再次遍历一遍线索二叉树
        2. 让一个指针pre指向当前遍历到的节点的上一个节点，即前驱节点
        3. 当移动指针p指向目标节点时，即p == q时，此时的指针pre即为当前节点p的前驱
        同样的，当pre == q时，p则为当前节点的后继节点

    易错点：
        1. 注意最后一个节点的rchild，rtag的处理，当递归完后，全局的pre指向树序列最后一个节点，若
           他的rchild == NULL，则需要将他的rtag设置为1
        2. 先序线索化会出现指针死循环问题，原因是先序线索化是在访问节点时会将左孩子为NULL设置为指向他的前驱，
           在下一次递归调用时无法判定原先左孩子为NULL，会重新指回到原来的位置，造成死循环。而中序和后续线索化
           在访问节点时已经访问了左子节点，因此不可能出现上面的问题
*/

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *LeftNode;
    struct BiTNode *RightNode;
} BiTNode, *BiTree;


typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *Lchild; //左子
    struct ThreadNode *Rchild; //右子
    int ltag, rtag; //左、右线索标志，当tag == 0 时表示指针指向孩子，tag == 1时表示指针指向“线索”
} ThreadNode, *ThreadTree;

/************************传统方式寻找中序遍历树序列的前驱*****************************/

BiTNode *pre;

void Vist_pre(BiTNode *node, BiTNode *targetNode)
{
    if (node == targetNode)
    {
        if (pre == NULL)
        {
            printf("front node is itself ! is %c",node->data);
            return;
        }
        
        printf("front node is :%c\n",pre->data); //移动到了当前目标节点，可读出前驱节点
    }
    else
    {
        pre = node; //前驱节点移动
    }
}

void Visit_post(BiTNode *node, BiTNode *targetNode)
{
    if (pre == targetNode)
    {   
        printf("post node is :%c\n",node->data); //移动到了当前目标节点，可读出后继节点
    }
    pre = node; //前驱节点移动
}


void FindPreNode(BiTree Node, BiTNode* targetNode)
{
    if (Node != NULL)
    {
        FindPreNode(Node->LeftNode, targetNode);
        Vist_pre(Node, targetNode);
        FindPreNode(Node->RightNode, targetNode);
    }
}

void FindPostNode(BiTree Node, BiTNode* targetNode)
{
    if (Node != NULL)
    {
        FindPostNode(Node->LeftNode, targetNode);
        Visit_post(Node, targetNode);
        FindPostNode(Node->RightNode, targetNode);
    }
}

/****************通过中序遍历线索化的方式，一边遍历一边线索化******************/
ThreadNode *pre_th; //指向当前访问节点的前序

void ThreadVisit(ThreadNode *node)
{
    if (node->Lchild == NULL)   //左指针线索化
    {
        node->Lchild = pre_th;
        node->ltag = 1;
    }
    if (pre_th != NULL&& pre_th->Rchild == NULL)
    {
        pre_th->Rchild = node;
        pre_th->rtag = 1;
    }
    
    pre_th = node; //前驱节点跟随移动
}

void InThread(ThreadTree t)
{
    if (t != NULL)
    {
        InThread(t->Lchild);
        ThreadVisit(t);
        InThread(t->Rchild);
    }
}

//中序线索化二叉树T
void CreateInThread(ThreadTree t)
{
    pre_th = NULL;
    if (t != NULL)
    {
        InThread(t);
        if (pre_th->Rchild == NULL) //其实中序遍历中，访问最后一个节点时肯定没有右孩子（左->中->右）
        {
            pre_th->rtag = 1; //处理遍历的最后一个结点，此时的pre_th指向与node相同的最后一个节点
        }
        
    }
    
}

/****************先序遍历线索化*********************/

ThreadNode *pre_th; //指向当前访问节点的前序

void ThreadVisit(ThreadNode *node)
{
    if (node->Lchild == NULL)   //左指针线索化
    {
        node->Lchild = pre_th;
        node->ltag = 1;
    }
    if (pre_th != NULL&& pre_th->Rchild == NULL)
    {
        pre_th->Rchild = node;
        pre_th->rtag = 1;
    }
    
    pre_th = node; //前驱节点跟随移动
}

void InThread(ThreadTree t)
{
    if (t != NULL)
    {
        ThreadVisit(t);
        if (t->ltag == 0) //防止先序遍历线索化时进入指针死循环（中序遍历与后续遍历均不会出现这个问题，因为不会再回头去处理左孩子）
        {
            InThread(t->Lchild);
        }
        InThread(t->Rchild);
    }
}

//先序线索化二叉树T
void CreateInThread(ThreadTree t)
{
    pre_th = NULL;
    if (t != NULL)
    {
        InThread(t);
        if (pre_th->Rchild == NULL)
        {
            pre_th->rtag = 1; //处理遍历的最后一个结点，此时的pre_th指向与node相同的最后一个节点
        }
        
    }
}

/*********************线索中序二叉树找前驱和后继（遍历）****************************/

/*
    1. 找后继
*/

//找到以P为根的子树中，第一个被中序遍历的节点
ThreadNode *FirstNode(ThreadNode *p)
{
    while (p->ltag == 0) //ltag == 1时说明已经到头了
    {
        p = p->Lchild; //循环找到最左下的节点（不一定是叶节点）
    }
    return p;
}

//找到节点p的后继节点
//目标：找到p的右子树中的最左下的节点，即为p的后继节点
ThreadNode* NextNode(ThreadNode *p)
{
    if (p->rtag == 1) //如果被线索化，则直接返回
    {
        return p->Rchild;
    }
    //右子树中的最左下节点
    return FirstNode(p->Rchild);
}

//对中序线索二叉树进行中序遍历
void PrintNodeByInOrder(ThreadTree t)
{
    for (ThreadNode* p = FirstNode(t); p != NULL; p = NextNode(p))
    {
        printf("%c",p->data);
    }
}

/*
    2. 找前驱
*/
//找到以p为根节点的右子树中，最后一个被访问的节点
ThreadNode* FindLastNode(ThreadNode *p)
{
    while (p->rtag != 1)
    {
        p = p->Rchild;
    }
    return p;
}

//找到中序搜索树中p的前驱节点
//目标：找到p的左子树中最右下的节点
ThreadNode* PreNode(ThreadNode *p)
{
    if (p->ltag == 1) //如果被线索化，则直接返回
    {
        return p->Lchild;
    }
    return FindLastNode(p->Lchild);
}

//对中序线索二叉树进行逆向的中序遍历
void PrintNodeByInOrder_DESC(ThreadTree t)
{
    for (ThreadNode* p = FindLastNode(t); p != NULL; p = PreNode(p))
    {
        printf("%c",p->data);
    }
    
}

/*********************线索先序二叉树找前驱和后继（遍历）****************************/

/*
    1. 找后继

    若 p-> rtag == 1，next = p->rchild
    若 p-> rtag == 0
        若p有左孩子，则先序后继为左孩子
        若p只有右孩子，则先序后继为右孩子
*/



/*
    2. 找前驱

        先序遍历中，左右子树的节点只可能是根的后继，不可能是前驱
        除非用经典方法从头开始遍历

        基于三叉链表：
            1. 如果能找到p的父节点，且p是左孩子
            2. 如果能找到p的父节点，且p是右孩子，左兄弟为空
            3. 如果能找到p的父节点，且p是右孩子，其左兄弟非空
                p的前驱为左兄弟子树中最后一个被先序遍历的节点
            4. 如果p是根节点，则p没有先序前驱
*/

/*********************线索后序二叉树找前驱和后继（遍历）****************************/

/*
    1. 前驱
    若 p-> ltag == 1，next = p->lchild
    若 p-> ltag == 0
        若p为根节点，则前驱为右节点
        若p为根节点，且只有左孩子，则前驱为左孩子子树的最后一个后序遍历的节点
*/

/*
    2. 后继
    后续遍历中，左右子树中节点只可能是根的前驱，不可能是后继
    除非用经典方法从头开始遍历

    基于三叉链表：
        如果能找到p的父节点，且p是右孩子
        如果能找到p的父节点，且p是左孩子，其右兄弟为空
        如果能找到p的父节点，且p是左孩子，其右兄弟非空，则为其右兄弟子树中第一个被后续遍历的节点
        如果p是根节点，则无后继
*/



/*********************************************************************/

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

    BiTNode* targetNode = &RootNode; //目标节点
    pre = NULL; //记录当前的前驱节点, 开始时指向空

    FindPreNode(&RootNode,targetNode); //寻找前继节点
    FindPostNode(&RootNode,targetNode); //寻找后继节点
}