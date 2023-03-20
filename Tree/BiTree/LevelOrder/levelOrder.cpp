#include<stdio.h>
#include<malloc.h>

/*
    ���Ĳ�α���
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
    LNode *front; //��ͷָ��
    LNode *rear;  //��βָ��
};

//���е�һЩ��������

bool InitQueue(Queue &q)
{
    q.front = q.rear = (LNode *)malloc(sizeof(LNode));
    q.front->next = NULL;
    return true;
}

//�ж��Ƿ�ӿ�
bool IsEmpty(Queue q)
{
    if (q.front == q.rear)
    {
        return true;
    }
    return false;
}

//���
bool EnQueue(Queue &q, BiTNode* newdata)
{
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = newdata;
    s->next = NULL;

    q.rear->next = s;
    q.rear = s; //�ƶ�β�ڵ�
}

//����
bool DeQueue(Queue &q, BiTNode* &res)
{
    if (q.front == q.rear)
    {
        return false;
    }
    LNode* first = q.front->next;
    res = first->data;

    q.front->next = first->next;
    
    if (first == q.rear) //����ǰΪ���һ��Ԫ�أ���βָ���ƶ���ͷ�ڵ�
    {
        q.rear = q.front;
    }
    free(first); //�ͷű�ɾ��Ԫ�ص��ڴ�ռ�
    return true;
}

//��α���
void LevelOrder(BiTree tree)
{
    Queue q;
    BiTNode *p; //ȡ���Ķ�ͷԪ��
    InitQueue(q); //��ʼ������

    //�Ƚ����ڵ����
    EnQueue(q,tree);

    while (!IsEmpty(q)) //�����в��գ���һֱѭ��
    {
        //ȡ����ͷԪ��
        DeQueue(q,p);
        printf(" %c ",p->data); //���ʶ�ͷԪ��

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
    BiTNode RootNode, BNode, CNode, DNode, ENode, FNode, GNode; //��ʼ�����ĸ����ڵ�
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

    printf("��α���:\n");
    LevelOrder(&RootNode);
    return 0;
}