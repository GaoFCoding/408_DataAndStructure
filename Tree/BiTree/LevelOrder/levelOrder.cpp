#include<stdio.h>
#include<malloc.h>

/*
    树的层次遍历
*/

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *LeftNode;
    struct BiTNode *RightNode;
} BiTNode, *BiTree;

typedef struct LNode
{
    BiTNode* data;
    LNode * next;
} LNode,*LinkList;

struct Queue
{
    LNode *front; //队头指针
    LNode *rear;  //队尾指针
};

//队列的一些基本操作

bool InitQueue(Queue &q)
{
    q.front = q.rear = (LNode *)malloc(sizeof(LNode));
    q.front->next = NULL;
    return true;
}

//判断是否队空
bool IsEmpty(Queue q)
{
    if (q.front == q.rear)
    {
        return true;
    }
    return false;
}

//入队
bool EnQueue(Queue &q, BiTNode* newdata)
{
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = newdata;
    s->next = NULL;

    q.rear->next = s;
    q.rear = s; //移动尾节点
}

//出队
bool DeQueue(Queue &q, BiTNode* &res)
{
    if (q.front == q.rear)
    {
        return false;
    }
    LNode* first = q.front->next;
    res = first->data;

    q.front->next = first->next;
    
    if (first == q.rear) //若当前为最后一个元素，则将尾指针移动至头节点
    {
        q.rear = q.front;
    }
    free(first); //释放被删除元素的内存空间
    return true;
}

//层次遍历
void LevelOrder(BiTree tree)
{
    Queue q;
    BiTNode *p; //取出的队头元素
    InitQueue(q); //初始化队列

    //先将根节点入队
    EnQueue(q,tree);

    while (!IsEmpty(q)) //若队列不空，则一直循环
    {
        //取出队头元素
        DeQueue(q,p);
        printf(" %c ",p->data); //访问队头元素

        if (p->LeftNode != NULL)
        {
            EnQueue(q,p->LeftNode);
        }
        if (p->RightNode != NULL)
        {
            EnQueue(q,p->RightNode);
        }    
    }
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

    printf("层次遍历:\n");
    LevelOrder(&RootNode);
    return 0;
}