#include<stdio.h>
#include<malloc.h>

/*
    二叉树的非递归遍历

    思路：利用栈实现二叉树的递归效果转换

        前序遍历
            根->左->右
        中序遍历
            左->根->右
        后序遍历
            左->右->根

    步骤:
        1. 沿着根的左孩子，依次入栈，直到左孩子为空
        2. 栈顶元素出栈并访问：若其右孩子为空，则继续执行这一步；若不为空，则将其右子树跳转到第一步
        3. 直到栈空并且当前指针指向空（最后一次循环肯定会使cur指向最后一个节点的下一个，也就是NULL）
*/

typedef char ElemType;

typedef struct BiTNode //二叉树
{
    ElemType data;
    struct BiTNode *LeftNode;
    struct BiTNode *RightNode;
} BiTNode, *BiTree;

typedef struct LNode
{
    BiTNode *data;
    struct LNode *next;
} *Stack;


//初始化栈
bool InitStack(Stack &s)
{
    s = (LNode *)malloc(sizeof(LNode)); //初始化头节点
    if (s == NULL)
    {
        return false;
    }
    s->next = NULL;
    return true;
}
 
//判断是否为空
bool IsEmpty(Stack s)
{
    if (s->next == NULL)
    {
        return true;
    }
    return false;
}

//入栈
bool Push(Stack &s, BiTNode* data)
{
    LNode* newdata = (LNode *)malloc(sizeof(LNode));
    newdata->data = data;
    
    newdata->next = s->next;
    s->next = newdata;
    return true;
}

//出栈
bool Pop(Stack &s, BiTNode* &res)
{
    if (s->next == NULL)
    {
        return false;
    }
    
    LNode* out;
    out = s->next;
    res = out->data;

    s->next = out->next;
    free(out);

    return true;
}

//获取栈顶元素
void GetTop(Stack S, BiTNode* &res)
{
    res = S->next->data;
}

//先序遍历
void PreOrder(Stack &S, BiTree T)
{
    InitStack(S); //初始化栈
    BiTNode *cur = T; //记录当前节点

    //循环时间步
    while (cur != NULL || !IsEmpty(S)) //当栈和当前节点同时为空时，退出循环
    {
        if (cur != NULL)
        {
            printf(" %c ",cur->data); //访问节点
            Push(S, cur); //左节点依次入栈，直到最左下的节点
            cur = cur->LeftNode;
        }
        else
        {
            Pop(S, cur); //出栈
            cur = cur->RightNode; //访问每一个出栈的右节点
        }
    }
    

}

//中序遍历
void InOrder(Stack &S, BiTree T)
{
    InitStack(S); //初始化栈
    BiTNode *cur = T; //记录当前节点

    //循环时间步
    while (cur != NULL || !IsEmpty(S)) //当栈和当前节点同时为空时，退出循环
    {
        if (cur != NULL)
        {
            Push(S, cur); //左节点依次入栈，直到最左下的节点
            cur = cur->LeftNode;
        }
        else
        {
            Pop(S, cur); //出栈
            printf(" %c ",cur->data); //访问节点
            cur = cur->RightNode; //访问每一个出栈的右节点
        }
    }
}

//后序遍历
/*
    后序遍历不同于前序和中序，他要保证根节点在出栈前，他的左右子树都已经访问过了

    后序非递归算法思路分析：
        1. 从根节点开始，将其入栈，然后沿左子树一直往下搜索，直到没有左孩子的节点
        2. 此时不能出栈访问，而是先判断栈顶节点是否有右子树，并且右子树是否已经访问
            1）若无右子树，则可以直接出栈，对下一个栈顶元素进行重复的判断
            2) 若有右子树，则对右子树重复从1开始的操作

        注意:
            每次出栈访问完一个节点就相当于遍历完以该节点为根的子树，需要将遍历指针cur置为NULL，
            以便让下一个栈顶元素出栈，否则会进入死循环，即重复走入栈的逻辑

        按照后序非递归算法遍历的二叉树，访问一个节点cur时，栈中的节点恰好都是cur的祖先，从栈底到栈顶元素恰好构成了从
        根节点到cur节点的一条路径，可以利用这一点求根到某节点的路径，求两个节点的最近公共祖先等
*/
void PostOrder(Stack &S, BiTree T)
{
    InitStack(S);   //初始化栈
    BiTNode *cur = T; //记录当前遍历到的节点
    BiTNode *r = NULL; //辅助指针r，用于指向最近访问过的节点
    
    //循环时间步
    while (cur != NULL || !IsEmpty(S)) //当遍历节点为空，并且栈为空时结束循环
    {
        if (cur != NULL) //沿着左子树一直往下搜索，直到没有左孩子节点
        {
            Push(S, cur);
            cur = cur->LeftNode;
        }
        else
        {
            GetTop(S, cur); //读取栈顶指针,但不出栈
            if (cur->RightNode != NULL && cur->RightNode != r) //若右孩子不为空并且没有被访问过
            {
                cur = cur->RightNode; //对栈顶节点的右子树重复上面的操作
            }
            else
            {
                Pop(S, cur);
                printf(" %c ",cur->data); //满足条件即可出栈并访问
                r = cur; //记录最近访问的节点
                cur = NULL; //节点访问完，重置cur指针
            }
        }
    }
}

int main()
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

    Stack s;

    printf("前序遍历:\n");
    PreOrder(s, &RootNode);

    printf("\n中序遍历:\n");
    InOrder(s, &RootNode);

    printf("\n后序遍历:\n");
    PostOrder(s, &RootNode);

    return 0;
}