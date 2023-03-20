#include<stdio.h>
#include<malloc.h>

/*
    �������ķǵݹ����

    ˼·������ջʵ�ֶ������ĵݹ�Ч��ת��

        ǰ�����
            ��->��->��
        �������
            ��->��->��
        �������
            ��->��->��

    ����:
        1. ���Ÿ������ӣ�������ջ��ֱ������Ϊ��
        2. ջ��Ԫ�س�ջ�����ʣ������Һ���Ϊ�գ������ִ����һ��������Ϊ�գ�������������ת����һ��
        3. ֱ��ջ�ղ��ҵ�ǰָ��ָ��գ����һ��ѭ���϶���ʹcurָ�����һ���ڵ����һ����Ҳ����NULL��
*/

typedef char ElemType;

typedef struct BiTNode //������
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


//��ʼ��ջ
bool InitStack(Stack &s)
{
    s = (LNode *)malloc(sizeof(LNode)); //��ʼ��ͷ�ڵ�
    if (s == NULL)
    {
        return false;
    }
    s->next = NULL;
    return true;
}
 
//�ж��Ƿ�Ϊ��
bool IsEmpty(Stack s)
{
    if (s->next == NULL)
    {
        return true;
    }
    return false;
}

//��ջ
bool Push(Stack &s, BiTNode* data)
{
    LNode* newdata = (LNode *)malloc(sizeof(LNode));
    newdata->data = data;
    
    newdata->next = s->next;
    s->next = newdata;
    return true;
}

//��ջ
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

//��ȡջ��Ԫ��
void GetTop(Stack S, BiTNode* &res)
{
    res = S->next->data;
}

//�������
void PreOrder(Stack &S, BiTree T)
{
    InitStack(S); //��ʼ��ջ
    BiTNode *cur = T; //��¼��ǰ�ڵ�

    //ѭ��ʱ�䲽
    while (cur != NULL || !IsEmpty(S)) //��ջ�͵�ǰ�ڵ�ͬʱΪ��ʱ���˳�ѭ��
    {
        if (cur != NULL)
        {
            printf(" %c ",cur->data); //���ʽڵ�
            Push(S, cur); //��ڵ�������ջ��ֱ�������µĽڵ�
            cur = cur->LeftNode;
        }
        else
        {
            Pop(S, cur); //��ջ
            cur = cur->RightNode; //����ÿһ����ջ���ҽڵ�
        }
    }
    

}

//�������
void InOrder(Stack &S, BiTree T)
{
    InitStack(S); //��ʼ��ջ
    BiTNode *cur = T; //��¼��ǰ�ڵ�

    //ѭ��ʱ�䲽
    while (cur != NULL || !IsEmpty(S)) //��ջ�͵�ǰ�ڵ�ͬʱΪ��ʱ���˳�ѭ��
    {
        if (cur != NULL)
        {
            Push(S, cur); //��ڵ�������ջ��ֱ�������µĽڵ�
            cur = cur->LeftNode;
        }
        else
        {
            Pop(S, cur); //��ջ
            printf(" %c ",cur->data); //���ʽڵ�
            cur = cur->RightNode; //����ÿһ����ջ���ҽڵ�
        }
    }
}

//�������
/*
    ���������ͬ��ǰ���������Ҫ��֤���ڵ��ڳ�ջǰ�����������������Ѿ����ʹ���

    ����ǵݹ��㷨˼·������
        1. �Ӹ��ڵ㿪ʼ��������ջ��Ȼ����������һֱ����������ֱ��û�����ӵĽڵ�
        2. ��ʱ���ܳ�ջ���ʣ��������ж�ջ���ڵ��Ƿ����������������������Ƿ��Ѿ�����
            1�������������������ֱ�ӳ�ջ������һ��ջ��Ԫ�ؽ����ظ����ж�
            2) ����������������������ظ���1��ʼ�Ĳ���

        ע��:
            ÿ�γ�ջ������һ���ڵ���൱�ڱ������Ըýڵ�Ϊ������������Ҫ������ָ��cur��ΪNULL��
            �Ա�����һ��ջ��Ԫ�س�ջ������������ѭ�������ظ�����ջ���߼�

        ���պ���ǵݹ��㷨�����Ķ�����������һ���ڵ�curʱ��ջ�еĽڵ�ǡ�ö���cur�����ȣ���ջ�׵�ջ��Ԫ��ǡ�ù����˴�
        ���ڵ㵽cur�ڵ��һ��·��������������һ�������ĳ�ڵ��·�����������ڵ������������ȵ�
*/
void PostOrder(Stack &S, BiTree T)
{
    InitStack(S);   //��ʼ��ջ
    BiTNode *cur = T; //��¼��ǰ�������Ľڵ�
    BiTNode *r = NULL; //����ָ��r������ָ��������ʹ��Ľڵ�
    
    //ѭ��ʱ�䲽
    while (cur != NULL || !IsEmpty(S)) //�������ڵ�Ϊ�գ�����ջΪ��ʱ����ѭ��
    {
        if (cur != NULL) //����������һֱ����������ֱ��û�����ӽڵ�
        {
            Push(S, cur);
            cur = cur->LeftNode;
        }
        else
        {
            GetTop(S, cur); //��ȡջ��ָ��,������ջ
            if (cur->RightNode != NULL && cur->RightNode != r) //���Һ��Ӳ�Ϊ�ղ���û�б����ʹ�
            {
                cur = cur->RightNode; //��ջ���ڵ���������ظ�����Ĳ���
            }
            else
            {
                Pop(S, cur);
                printf(" %c ",cur->data); //�����������ɳ�ջ������
                r = cur; //��¼������ʵĽڵ�
                cur = NULL; //�ڵ�����꣬����curָ��
            }
        }
    }
}

int main()
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

    Stack s;

    printf("ǰ�����:\n");
    PreOrder(s, &RootNode);

    printf("\n�������:\n");
    InOrder(s, &RootNode);

    printf("\n�������:\n");
    PostOrder(s, &RootNode);

    return 0;
}