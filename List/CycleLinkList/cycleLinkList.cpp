#include<stdio.h>
#include<malloc.h>
typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode,* LinkList;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
} DNode,*DLinkList;

//��ʼ��һ��ѭ��������
bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode)); //��ʼ��ͷ�ڵ�
	if (L == NULL)
	{
		return false; //�����ڴ�ʧ��
	}
	L->next = L; //β�ڵ�ָ��ͷ�ڵ㣬ʵ��ѭ��
}

//��ʼ��һ��ѭ��������
bool InitDList(DLinkList& DL)
{
	DL = (DNode*)malloc(sizeof(DNode)); //��ʼ��ͷ�ڵ�
	if (DL == NULL)
	{
		return false; //�����ڴ�ʧ��
	}
	DL->prior = DL;
	DL->next = DL;
	return true;
}

//�ж�ѭ����\˫�����Ƿ�Ϊ��
bool IsEmpty(LinkList &L)
{
	if (L->next == L)
	{
		return true;
	}
	return false;
}

//�жϵ�/˫�����ĳ�ڵ�p�Ƿ�Ϊβ�ڵ�
bool IsTail(LinkList& L, LNode p)
{
	if (p.next == L)
	{
		return true;
	}
	return false;
}

//˫����Ĳ��룬��p�ڵ�����s�ڵ�
bool InsertS(DNode* p,DNode *s)
{
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//˫�����ɾ��,ɾ��p�ڵ�ĺ�̽ڵ�q
bool DeleteS(DNode* p)
{
	DNode* q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}

