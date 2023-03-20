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

//初始化一个循环单链表
bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode)); //初始化头节点
	if (L == NULL)
	{
		return false; //分配内存失败
	}
	L->next = L; //尾节点指向头节点，实现循环
}

//初始化一个循环单链表
bool InitDList(DLinkList& DL)
{
	DL = (DNode*)malloc(sizeof(DNode)); //初始化头节点
	if (DL == NULL)
	{
		return false; //分配内存失败
	}
	DL->prior = DL;
	DL->next = DL;
	return true;
}

//判断循环单\双链表是否为空
bool IsEmpty(LinkList &L)
{
	if (L->next == L)
	{
		return true;
	}
	return false;
}

//判断单/双链表的某节点p是否为尾节点
bool IsTail(LinkList& L, LNode p)
{
	if (p.next == L)
	{
		return true;
	}
	return false;
}

//双链表的插入，在p节点后插入s节点
bool InsertS(DNode* p,DNode *s)
{
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//双链表的删除,删除p节点的后继节点q
bool DeleteS(DNode* p)
{
	DNode* q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}

