#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

/*
	��ʽ���е��ص�
		1. һ�㲻����ڶ��������⣬�����ڴ治�������ˣ�����һ��ֻ�ÿ����Ƿ�Ϊ�յ�����
		2. ����һ�㲻��ѭ�����У�ʵ����ʽ���е�ͷ�ڵ�frontһ�㲻�ᶯ��������rear�ڵ�
		3. ��ͷ�ڵ�һ��ͨ��front == rear���ж��Ƿ�Ϊ�գ�������ͷ�ڵ�һ��ͨ��front == null���ж��Ƿ�Ϊ��
			��ͷ�ڵ���ȡ�����һ��Ԫ�غ󣬽�rearָ��front��frontʼ�մ��������ͷ�ڵ�
			����ͷ�ڵ���ȡ�����һ��Ԫ�غ󣬽�rear��frontͬʱ��ΪNull
			
*/

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LinkNode;

typedef struct {
	LinkNode* front, * rear;
} LinkQueue;

//��ʼ�����У���ͷ�ڵ㣩
bool InitQueueWithHead(LinkQueue& q)
{
	q.front = q.rear = (LinkNode*)malloc(sizeof(LinkNode)); //Ϊͷ��β�ڵ�����ڴ�ռ�
	q.front->next = NULL; //ͷ�ڵ����һ���ڵ�Ϊnull
	return true;
}

//��ʼ�����У�����ͷ�ڵ㣩
bool InitQueueWithNoHead(LinkQueue& q)
{
	q.front = q.rear = NULL;
	return true;
}


//�ж϶����Ƿ�Ϊ��(��ͷ�ڵ�)
bool QueueEmptyWithHead(LinkQueue q)
{
	if (q.front == q.rear)
		//������q.front == null����
	{
		return true;
	}
	return false;
}

//�ж϶����Ƿ�Ϊ��(��ͷ�ڵ�)
bool QueueEmptyWithNoHead(LinkQueue q)
{
	if (q.front == NULL)
	{
		return true;
	}
	return false;
}

//��ӣ���ͷ�ڵ�
//�൱�ں�����
bool enQueueWithHead(LinkQueue& q, ElemType data)
{
	LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode)); //Ϊ�½ڵ�����ڴ�
	newNode->data = data;
	newNode->next = NULL;
	q.rear->next = newNode; //�½ڵ���뵽β�ڵ�֮��
	q.rear = newNode; //����β�ڵ�ָ�루����ƶ�һλ��ָ�����²���Ľڵ��λ�ã�
	return true;
}

//��ӣ�����ͷ�ڵ�
//�൱�ں�����
bool enQueueWithNoHead(LinkQueue& q, ElemType data)
{
	LinkNode* newNode = (LNode*)malloc(sizeof(LinkNode));
	newNode->data = data;
	newNode->next = NULL;

	//�ж��Ƿ�Ϊ�ն���
	if (q.front == NULL) //����ͷ�ڵ�ʱ����Ҫ�����ж�
	{
		q.front = newNode;
		q.rear = newNode;
	}
	else {
		q.rear->next = newNode; //�µĽڵ���뵽rear�ڵ�֮��
		q.rear = newNode; //�޸�rearָ��
	}
}

//��ͷ�ڵ����
//β�巨��ӣ���ͷ��ȡ��Ԫ��
bool DequeueWithHead(LinkQueue& q, ElemType& res)
{
	if (q.front == q.rear) //�ж϶����Ƿ�Ϊ��
	{
		return false;
	}
	
	LinkNode* p = q.front->next; //Ҫ���ӵĽڵ�,��ͷ�ڵ����һ���ڵ�
	res = p->data;

	q.front->next = p->next; //ɾ��ͷ��Ԫ��(����)

	if (q.rear == p) //��ʱ�����һ��Ԫ�س���
	{
		q.rear = q.front; //��βָ����˵�ͷ������������ٴα�Ϊ�ն���
	}
	free(p); //�ͷ��ڴ�

	return true;
}

//����ͷ�ڵ�Ķ��г���
bool DequeueWithNoHead(LinkQueue& q, ElemType& res)
{
	if (q.front == NULL)
	{
		return false;
	}
	LinkNode* p = q.front; //pָ��Ҫ���ӵĽڵ�(��ͷ�ڵ�)
	res = p->data;
	q.front = p->next; //�޸�ͷ�ڵ�

	if (q.rear == p) //���һ������
	{
		q.rear = NULL;
		q.front = NULL;
	}
	free(p);
	return true;
}

void main(void)
{
	LinkQueue q;
	InitQueueWithHead(q);
}