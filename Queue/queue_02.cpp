#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

/*
	链式队列的特点
		1. 一般不会存在队满的问题，除非内存不够分配了，所以一般只用考虑是否为空的问题
		2. 队列一般不是循环队列，实现链式队列的头节点front一般不会动，动的是rear节点
		3. 带头节点一般通过front == rear来判断是否为空，而不带头节点一般通过front == null来判断是否为空
			带头节点在取出最后一个元素后，将rear指向front，front始终代表链表的头节点
			不带头节点在取出最后一个元素后，将rear和front同时置为Null
			
*/

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LinkNode;

typedef struct {
	LinkNode* front, * rear;
} LinkQueue;

//初始化队列（带头节点）
bool InitQueueWithHead(LinkQueue& q)
{
	q.front = q.rear = (LinkNode*)malloc(sizeof(LinkNode)); //为头、尾节点分配内存空间
	q.front->next = NULL; //头节点的下一个节点为null
	return true;
}

//初始化队列（不带头节点）
bool InitQueueWithNoHead(LinkQueue& q)
{
	q.front = q.rear = NULL;
	return true;
}


//判断队列是否为空(带头节点)
bool QueueEmptyWithHead(LinkQueue q)
{
	if (q.front == q.rear)
		//或者是q.front == null均可
	{
		return true;
	}
	return false;
}

//判断队列是否为空(带头节点)
bool QueueEmptyWithNoHead(LinkQueue q)
{
	if (q.front == NULL)
	{
		return true;
	}
	return false;
}

//入队，带头节点
//相当于后插操作
bool enQueueWithHead(LinkQueue& q, ElemType data)
{
	LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode)); //为新节点分配内存
	newNode->data = data;
	newNode->next = NULL;
	q.rear->next = newNode; //新节点插入到尾节点之后
	q.rear = newNode; //更新尾节点指针（向后移动一位，指向最新插入的节点的位置）
	return true;
}

//入队，不带头节点
//相当于后插操作
bool enQueueWithNoHead(LinkQueue& q, ElemType data)
{
	LinkNode* newNode = (LNode*)malloc(sizeof(LinkNode));
	newNode->data = data;
	newNode->next = NULL;

	//判断是否为空队列
	if (q.front == NULL) //不带头节点时，需要进行判断
	{
		q.front = newNode;
		q.rear = newNode;
	}
	else {
		q.rear->next = newNode; //新的节点加入到rear节点之后
		q.rear = newNode; //修改rear指针
	}
}

//带头节点出队
//尾插法入队，从头部取出元素
bool DequeueWithHead(LinkQueue& q, ElemType& res)
{
	if (q.front == q.rear) //判断队列是否为空
	{
		return false;
	}
	
	LinkNode* p = q.front->next; //要出队的节点,即头节点的下一个节点
	res = p->data;

	q.front->next = p->next; //删除头部元素(出队)

	if (q.rear == p) //此时是最后一个元素出队
	{
		q.rear = q.front; //将尾指针回退到头部，代表队列再次变为空队列
	}
	free(p); //释放内存

	return true;
}

//不带头节点的队列出队
bool DequeueWithNoHead(LinkQueue& q, ElemType& res)
{
	if (q.front == NULL)
	{
		return false;
	}
	LinkNode* p = q.front; //p指向要出队的节点(即头节点)
	res = p->data;
	q.front = p->next; //修改头节点

	if (q.rear == p) //最后一个出队
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