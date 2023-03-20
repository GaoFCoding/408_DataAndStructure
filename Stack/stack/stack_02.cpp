#include<stdio.h>
#include<malloc.h>
#define MaxSize 10
typedef int ElemType;

//ͨ�����������ʵ��ջ����ʽ�洢


typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode,*LNodeStack;


//��ʼ��һ����ͷ�ڵ����ʽջ
bool InitStackWithHead(LNodeStack& Stack)
{
	Stack = (LNode*)malloc(sizeof(LNode)); //��ʼ��һ��ͷ�ڵ�
	if (Stack == NULL)
	{
		return false; //�����ڴ�ʧ��
	}
	Stack->next = NULL;
	return true;
}


bool InitStackWithNoHead(LNodeStack& Stack)
{
	Stack = NULL;
	return true;
}

//��ջ������ͷ�ڵ㣩
bool Push_noHead(LNodeStack& L, ElemType data)
{
	//����һ���µĽڵ�
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	newNode->data = data;
	newNode->next = L;
	L = newNode;
	return true;
}


//��ջ������ͷ�ڵ㣩
bool Pop_noHead(LNodeStack &L,ElemType &res)
{
	if (L == NULL)
	{
		printf("ջ��Ϊ��");
		return false;
	}
	LNode* top = L; //ջ��
	L = top->next;
	res = top->data;
	free(top);
	return true;
}

//��ջ����ͷ�ڵ㣩��ʵ���Ͼ���ͷ�巨����
bool Push_Head(LNodeStack& L, ElemType newData)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode)); //����һ���µĽڵ�
	newNode->data = newData; //����������

	newNode->next = L->next; //�½ڵ�ָ��ͷ�ڵ����һ���ڵ�
	L->next = newNode; //ͷ�ڵ�ָ���½ڵ�

	return true;
}

//��ջ��ʵ���Ͼ���ɾ��ͷ�ڵ�������һ���ڵ�
bool Pop_Head(LNodeStack &L, ElemType &res)
{
	if (L->next == NULL)
	{
		printf("ջ��Ϊ��");
		return false;
	}
	LNode* deleteNode = L->next;
	L->next = deleteNode->next;
	free(deleteNode); //�ͷ��ڴ���Դ

	return true;
}

void main(void)
{
	LNodeStack Stack;
	ElemType res;
	InitStackWithNoHead(Stack);
	Push_noHead(Stack, 12);
	Push_noHead(Stack, 15);
	Push_noHead(Stack, 18);
	Push_noHead(Stack, 22);
	Pop_noHead(Stack, res);
	Pop_noHead(Stack, res);
	Pop_noHead(Stack, res);
	Pop_noHead(Stack, res);
	Pop_noHead(Stack, res);
	printf("res is %d\n", res);
		
	int num = 1;
	LNode* current = Stack;
	while (current != NULL)
	{
		printf("node %d is %d\n", num,current->data);
		current = current->next;
		num++;
	}
}