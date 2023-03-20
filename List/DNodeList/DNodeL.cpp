#include<stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
} DNode,*DLinkList;

//��ʼ��˫����
bool InitDLinkList(DLinkList& L)
{
	L = (DNode*)malloc(sizeof(DNode)); //��ʼ��ͷ�ڵ�
	if (L == NULL)
	{
		printf("�����ڴ�ʧ��");
		return false;
	}
	L->next = NULL;
	L->prior = NULL;
	return true;
}

//˫�������
/*
	Ŀ�꣺��p�ڵ�������s�ڵ�

	//�ϸ���1��2��3��4˳�����ǰ��ڵ�ָ�����
	//��ȵ�����������2��3����
*/
bool InsertNextDNode(DNode* p, DNode* s)
{
	if (p == NULL || s == NULL)
	{
		return false;
	}
	s->next = p->next; //1. s�ĺ���ָ��ָ��p����һ���ڵ�
	if (p->next != NULL) //���p�ڵ��к�̽ڵ�
	{
		p->next->prior = s; //2. p����һ���ڵ��ǰ��ָ��ָ��s
	}
	s->prior = p; //3. s��ǰ��ָ��ָ��p
	p->next = s; //4. p�ĺ���ָ��ָ��s
	
	return true;
}

//˫�����ɾ��
//ɾ��p�ڵ�ĺ�̽ڵ�
bool DeleteNextDNode(DNode* p)
{
	if (p == NULL || p->next == NULL)
	{
		return false;
	}
	DNode* q = p->next; //qΪp�ĺ�̽ڵ�
	p->next = q->next;
	if (q->next != NULL)
	{
		q->next->prior = p; //q�ĺ�̽ڵ��ǰ��ָ��ָ��p
	}
	free(q);
	return true;
}

//ɾ��˫����
void Destory(DLinkList& L)
{
	while (L->next != NULL)
	{
		DeleteNextDNode(L);
	}
	free(L); //�ͷ�ͷ�ڵ�
	L = NULL; //ͷ�ڵ�ָ��null
}

void main(void)
{

}