#include<stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
} DNode,*DLinkList;

//初始化双链表
bool InitDLinkList(DLinkList& L)
{
	L = (DNode*)malloc(sizeof(DNode)); //初始化头节点
	if (L == NULL)
	{
		printf("分配内存失败");
		return false;
	}
	L->next = NULL;
	L->prior = NULL;
	return true;
}

//双链表插入
/*
	目标：在p节点后面插入s节点

	//严格按照1，2，3，4顺序进行前后节点指针操作
	//相比单链表，增加了2，3步骤
*/
bool InsertNextDNode(DNode* p, DNode* s)
{
	if (p == NULL || s == NULL)
	{
		return false;
	}
	s->next = p->next; //1. s的后向指针指向p的下一个节点
	if (p->next != NULL) //如果p节点有后继节点
	{
		p->next->prior = s; //2. p的下一个节点的前向指针指向s
	}
	s->prior = p; //3. s的前向指针指向p
	p->next = s; //4. p的后向指针指向s
	
	return true;
}

//双链表的删除
//删除p节点的后继节点
bool DeleteNextDNode(DNode* p)
{
	if (p == NULL || p->next == NULL)
	{
		return false;
	}
	DNode* q = p->next; //q为p的后继节点
	p->next = q->next;
	if (q->next != NULL)
	{
		q->next->prior = p; //q的后继节点的前向指针指向p
	}
	free(q);
	return true;
}

//删除双链表
void Destory(DLinkList& L)
{
	while (L->next != NULL)
	{
		DeleteNextDNode(L);
	}
	free(L); //释放头节点
	L = NULL; //头节点指向null
}

void main(void)
{

}