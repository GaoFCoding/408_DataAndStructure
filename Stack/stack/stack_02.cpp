#include<stdio.h>
#include<malloc.h>
#define MaxSize 10
typedef int ElemType;

//通过单链表可以实现栈的链式存储


typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode,*LNodeStack;


//初始化一个带头节点的链式栈
bool InitStackWithHead(LNodeStack& Stack)
{
	Stack = (LNode*)malloc(sizeof(LNode)); //初始化一个头节点
	if (Stack == NULL)
	{
		return false; //分配内存失败
	}
	Stack->next = NULL;
	return true;
}


bool InitStackWithNoHead(LNodeStack& Stack)
{
	Stack = NULL;
	return true;
}

//进栈（不带头节点）
bool Push_noHead(LNodeStack& L, ElemType data)
{
	//声明一个新的节点
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	newNode->data = data;
	newNode->next = L;
	L = newNode;
	return true;
}


//出栈（不带头节点）
bool Pop_noHead(LNodeStack &L,ElemType &res)
{
	if (L == NULL)
	{
		printf("栈已为空");
		return false;
	}
	LNode* top = L; //栈顶
	L = top->next;
	res = top->data;
	free(top);
	return true;
}

//进栈（带头节点），实际上就是头插法操作
bool Push_Head(LNodeStack& L, ElemType newData)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode)); //创建一个新的节点
	newNode->data = newData; //存入新数据

	newNode->next = L->next; //新节点指向头节点的下一个节点
	L->next = newNode; //头节点指向新节点

	return true;
}

//出栈，实际上就是删除头节点后面的那一个节点
bool Pop_Head(LNodeStack &L, ElemType &res)
{
	if (L->next == NULL)
	{
		printf("栈已为空");
		return false;
	}
	LNode* deleteNode = L->next;
	L->next = deleteNode->next;
	free(deleteNode); //释放内存资源

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