#include<stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode,*LinkList; //这里使用别称LNode强调这是一个节点，使用LinkList强调这是一个链表 LinkList == LNode*

//初始化一个空链表,无头节点
Status InitListWithoutHead(LinkList &L)
{
	L = NULL; //初始化LinkList*
	return 0;
}

//判断单链表是否为空
bool IsEmpty(LinkList L)
{ 
	if (L == NULL)
	{
		printf("is empty");
		return true;
	}
	return false;
}

//带头节点的单链表初始化
Status InitListWithHead(LinkList &L) //引用类型
{
	L = (LNode*)malloc(sizeof(LNode)); //为头节点分配一块占LNode大小的内存
	if (L == NULL)
	{
		return -1; //内存不足，初始化失败
	}
	L->next = NULL; //初始化L中的next节点
	return 0;
}

//判断带头节点的单链表是否为空
bool IsEmpty_head(LinkList L) 
{
	if (L->next == NULL) //判断头节点的下一个节点是否为空
	{
		printf("is empty");
		return true;
	}
	return false;
}

//插入节点（若不带头节点，在i=1处需要做特殊处理）
// 
// if (i == 1)
// {
//		LNode* newNode = (LNode*)malloc(sizeof(LNode));
//      newNode->data = data;
//		newNode->next = L;
//		L = newNode;
// }
// 
// 

//在第i个节点插入内容为data的节点（后插操作）
bool InsertNode(LinkList &L,ElemType data,int i)
{
	if (i < 1) //i的合法性判断，要插入的位置必须大于1
	{
		printf("输入i不合法，请输入大于等于1的位置索引");
		return false;
	}

	LNode* currentNode = L; //获取头节点指针
	int current = 0; //p指向的当前节点位置

	while (currentNode != NULL && current < i-1) //找到0开始的第i-1个节点，即i的前一个节点
	{
		currentNode = currentNode->next; //向下一个节点移动
		current++; //更改指针当前节点索引记录
	}

	if (currentNode == NULL) //当移动到链表末尾的下一个节点时触发
	{
		printf("i位置不合法");
		return false; //i值不合法
	}

	LNode* newNode = (LNode*)malloc(sizeof(LNode)); //分配一个新的节点作为插入节点
	newNode->data = data; //初始化data参数

	newNode->next = currentNode->next; //先将新节点指向第i个节点
	currentNode->next = newNode; //再将第i-1个节点指向这个新节点
	printf("插入成功");
	return true; //插入成功
}

//指定节点的后插操作：O（1）
bool InsertBehind(LNode* Node,ElemType data) {
	//初始化一个新节点
	//以下操作同上
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
	{
		printf("分配内存失败");
		return false;
	}
	newNode->data = data;
	newNode->next = Node->next;
	Node->next = newNode;
	printf("插入成功");
	return true;
}

//指定节点的前插操作：O（1）
bool InsertBefore(LNode* Node,ElemType data)
{
	//初始化一个新节点
	//以下操作同上
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
	{
		printf("分配内存失败");
		return false;
	}
	newNode->next = Node->next;
	Node->next = newNode;

	newNode->data = Node->data; //实际上也是后插操作，只不过把前节点的值拷贝给新节点，再把data赋值给前节点
	Node->data = data;
	printf("插入成功");
	return true;
	//要实现真正的前插操作，则需要引入头节点，并进行O（n）的操作
}

//删除节点(含头节点的情况)
bool DeleteNode(LinkList &L,int i,ElemType &res)
{
	if (i < 1)
	{
		printf("索引值i不能小于1");
		return false;
	}

	LNode* currentNode = L; //定义当前遍历的所在节点
	int current = 0; //定义当前遍历的所在节点的索引

	while (currentNode != NULL && current < i-1) //找到目标节点的前一个节点
	{
		currentNode = currentNode->next; //移动指针，找到第i-1个节点
		current++;
	}
	if (currentNode == NULL || currentNode->next == NULL)
	{
		printf("输入索引值i不合法，找不到需要删除的对象");
		return false;
	}

	LNode* targetNode = currentNode->next; //targetNode指向需要删除节点
	res = targetNode->data; //将要删除的节点的data值返回

	currentNode->next = targetNode->next; //跳过需要删除的节点
	free(targetNode); //释放节点储存空间
	
	printf("删除节点成功");
	return true;
}

//删除指定的节点
bool DeleteTargetNode(LNode* targetNode)
{
	if (targetNode == NULL || targetNode->next == NULL)
	{
		printf("不合法的目标节点");
		return false;
	}

	LNode* nextNode = targetNode->next; //获取要删除的节点的下一个节点
	targetNode->data = nextNode->data; //将下一个节点的data值拷贝给目标节点
	targetNode->next = nextNode->next; // 指向下下个节点
	free(nextNode); //释放内存
	printf("删除节点成功");
	return true;
}

//按位查找 O(n)
LNode* getElementByIndex(LinkList &L,int i)
{
	if (i < 1)
	{
		printf("索引值i不能小于1");
		return L;
	}

	LNode* currentNode = L; //定义当前遍历的所在节点
	int current = 0; //定义当前遍历的所在节点的索引

	while (currentNode != NULL && current < i)
	{
		currentNode = currentNode->next;
		current++;
	}

	return currentNode;
}

//按值查找 O(n)
LNode* getElementByData(LinkList& L, ElemType target)
{
	LNode* currentNode = L; //定义当前遍历的所在节点

	while (currentNode != NULL && currentNode->data != target)
	{
		currentNode = currentNode->next; //移动指针，找到第i-1个节点
	}

	return currentNode;
}

//尾插法创建单链表
LinkList CreateList(LinkList &L)
{
	int data; //声明每个节点的值data
	L = (LNode*)malloc(sizeof(LNode)); //建立头节点
	LNode* newNode; //声明新节点
	LNode* lastNode = L; //声明并初始化最后一个节点
	
	scanf_s("%d",&data);
	while (data != -1)
	{
		newNode = (LNode*)malloc(sizeof(LNode)); //创建一个新的节点
		newNode->data = data; //将data值置入新节点
		lastNode->next = newNode; //将尾节点指向新节点
		lastNode = newNode; //更新尾节点位置
		scanf_s("%d",&data);
	}
	lastNode->next = NULL;
	return L;
}

//链表的逆置（头插法）
//本质上是对头节点的后插操作
LinkList List_HeadInsert(LinkList& L)
{	
	LNode* newNode;
	L = (LNode*)malloc(sizeof(LNode)); //初始化头节点
	L->next = NULL; //这里不能省略，否则会指向一片不可预知的内存区域！！
	ElemType data; //声明要输入的数据

	scanf_s("%d",&data);
	while (data != -1)
	{
		//对头节点指向尾插操作
		newNode = (LNode*)malloc(sizeof(LNode)); //初始化一个新的节点
		newNode->data = data;
		newNode->next = L->next;
		L->next = newNode;
		scanf_s("%d",&data);
	}
	return L;
}


void main(void) {
	LinkList L;
	CreateList(L);
	LNode* targetNode = getElementByIndex(L, 2);
	printf("data is : %d",targetNode->data);
}
