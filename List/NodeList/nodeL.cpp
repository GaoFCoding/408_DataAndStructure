#include<stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef int Status;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode,*LinkList; //����ʹ�ñ��LNodeǿ������һ���ڵ㣬ʹ��LinkListǿ������һ������ LinkList == LNode*

//��ʼ��һ��������,��ͷ�ڵ�
Status InitListWithoutHead(LinkList &L)
{
	L = NULL; //��ʼ��LinkList*
	return 0;
}

//�жϵ������Ƿ�Ϊ��
bool IsEmpty(LinkList L)
{ 
	if (L == NULL)
	{
		printf("is empty");
		return true;
	}
	return false;
}

//��ͷ�ڵ�ĵ������ʼ��
Status InitListWithHead(LinkList &L) //��������
{
	L = (LNode*)malloc(sizeof(LNode)); //Ϊͷ�ڵ����һ��ռLNode��С���ڴ�
	if (L == NULL)
	{
		return -1; //�ڴ治�㣬��ʼ��ʧ��
	}
	L->next = NULL; //��ʼ��L�е�next�ڵ�
	return 0;
}

//�жϴ�ͷ�ڵ�ĵ������Ƿ�Ϊ��
bool IsEmpty_head(LinkList L) 
{
	if (L->next == NULL) //�ж�ͷ�ڵ����һ���ڵ��Ƿ�Ϊ��
	{
		printf("is empty");
		return true;
	}
	return false;
}

//����ڵ㣨������ͷ�ڵ㣬��i=1����Ҫ�����⴦��
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

//�ڵ�i���ڵ��������Ϊdata�Ľڵ㣨��������
bool InsertNode(LinkList &L,ElemType data,int i)
{
	if (i < 1) //i�ĺϷ����жϣ�Ҫ�����λ�ñ������1
	{
		printf("����i���Ϸ�����������ڵ���1��λ������");
		return false;
	}

	LNode* currentNode = L; //��ȡͷ�ڵ�ָ��
	int current = 0; //pָ��ĵ�ǰ�ڵ�λ��

	while (currentNode != NULL && current < i-1) //�ҵ�0��ʼ�ĵ�i-1���ڵ㣬��i��ǰһ���ڵ�
	{
		currentNode = currentNode->next; //����һ���ڵ��ƶ�
		current++; //����ָ�뵱ǰ�ڵ�������¼
	}

	if (currentNode == NULL) //���ƶ�������ĩβ����һ���ڵ�ʱ����
	{
		printf("iλ�ò��Ϸ�");
		return false; //iֵ���Ϸ�
	}

	LNode* newNode = (LNode*)malloc(sizeof(LNode)); //����һ���µĽڵ���Ϊ����ڵ�
	newNode->data = data; //��ʼ��data����

	newNode->next = currentNode->next; //�Ƚ��½ڵ�ָ���i���ڵ�
	currentNode->next = newNode; //�ٽ���i-1���ڵ�ָ������½ڵ�
	printf("����ɹ�");
	return true; //����ɹ�
}

//ָ���ڵ�ĺ�������O��1��
bool InsertBehind(LNode* Node,ElemType data) {
	//��ʼ��һ���½ڵ�
	//���²���ͬ��
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
	{
		printf("�����ڴ�ʧ��");
		return false;
	}
	newNode->data = data;
	newNode->next = Node->next;
	Node->next = newNode;
	printf("����ɹ�");
	return true;
}

//ָ���ڵ��ǰ�������O��1��
bool InsertBefore(LNode* Node,ElemType data)
{
	//��ʼ��һ���½ڵ�
	//���²���ͬ��
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL)
	{
		printf("�����ڴ�ʧ��");
		return false;
	}
	newNode->next = Node->next;
	Node->next = newNode;

	newNode->data = Node->data; //ʵ����Ҳ�Ǻ�������ֻ������ǰ�ڵ��ֵ�������½ڵ㣬�ٰ�data��ֵ��ǰ�ڵ�
	Node->data = data;
	printf("����ɹ�");
	return true;
	//Ҫʵ��������ǰ�����������Ҫ����ͷ�ڵ㣬������O��n���Ĳ���
}

//ɾ���ڵ�(��ͷ�ڵ�����)
bool DeleteNode(LinkList &L,int i,ElemType &res)
{
	if (i < 1)
	{
		printf("����ֵi����С��1");
		return false;
	}

	LNode* currentNode = L; //���嵱ǰ���������ڽڵ�
	int current = 0; //���嵱ǰ���������ڽڵ������

	while (currentNode != NULL && current < i-1) //�ҵ�Ŀ��ڵ��ǰһ���ڵ�
	{
		currentNode = currentNode->next; //�ƶ�ָ�룬�ҵ���i-1���ڵ�
		current++;
	}
	if (currentNode == NULL || currentNode->next == NULL)
	{
		printf("��������ֵi���Ϸ����Ҳ�����Ҫɾ���Ķ���");
		return false;
	}

	LNode* targetNode = currentNode->next; //targetNodeָ����Ҫɾ���ڵ�
	res = targetNode->data; //��Ҫɾ���Ľڵ��dataֵ����

	currentNode->next = targetNode->next; //������Ҫɾ���Ľڵ�
	free(targetNode); //�ͷŽڵ㴢��ռ�
	
	printf("ɾ���ڵ�ɹ�");
	return true;
}

//ɾ��ָ���Ľڵ�
bool DeleteTargetNode(LNode* targetNode)
{
	if (targetNode == NULL || targetNode->next == NULL)
	{
		printf("���Ϸ���Ŀ��ڵ�");
		return false;
	}

	LNode* nextNode = targetNode->next; //��ȡҪɾ���Ľڵ����һ���ڵ�
	targetNode->data = nextNode->data; //����һ���ڵ��dataֵ������Ŀ��ڵ�
	targetNode->next = nextNode->next; // ָ�����¸��ڵ�
	free(nextNode); //�ͷ��ڴ�
	printf("ɾ���ڵ�ɹ�");
	return true;
}

//��λ���� O(n)
LNode* getElementByIndex(LinkList &L,int i)
{
	if (i < 1)
	{
		printf("����ֵi����С��1");
		return L;
	}

	LNode* currentNode = L; //���嵱ǰ���������ڽڵ�
	int current = 0; //���嵱ǰ���������ڽڵ������

	while (currentNode != NULL && current < i)
	{
		currentNode = currentNode->next;
		current++;
	}

	return currentNode;
}

//��ֵ���� O(n)
LNode* getElementByData(LinkList& L, ElemType target)
{
	LNode* currentNode = L; //���嵱ǰ���������ڽڵ�

	while (currentNode != NULL && currentNode->data != target)
	{
		currentNode = currentNode->next; //�ƶ�ָ�룬�ҵ���i-1���ڵ�
	}

	return currentNode;
}

//β�巨����������
LinkList CreateList(LinkList &L)
{
	int data; //����ÿ���ڵ��ֵdata
	L = (LNode*)malloc(sizeof(LNode)); //����ͷ�ڵ�
	LNode* newNode; //�����½ڵ�
	LNode* lastNode = L; //��������ʼ�����һ���ڵ�
	
	scanf_s("%d",&data);
	while (data != -1)
	{
		newNode = (LNode*)malloc(sizeof(LNode)); //����һ���µĽڵ�
		newNode->data = data; //��dataֵ�����½ڵ�
		lastNode->next = newNode; //��β�ڵ�ָ���½ڵ�
		lastNode = newNode; //����β�ڵ�λ��
		scanf_s("%d",&data);
	}
	lastNode->next = NULL;
	return L;
}

//��������ã�ͷ�巨��
//�������Ƕ�ͷ�ڵ�ĺ�����
LinkList List_HeadInsert(LinkList& L)
{	
	LNode* newNode;
	L = (LNode*)malloc(sizeof(LNode)); //��ʼ��ͷ�ڵ�
	L->next = NULL; //���ﲻ��ʡ�ԣ������ָ��һƬ����Ԥ֪���ڴ����򣡣�
	ElemType data; //����Ҫ���������

	scanf_s("%d",&data);
	while (data != -1)
	{
		//��ͷ�ڵ�ָ��β�����
		newNode = (LNode*)malloc(sizeof(LNode)); //��ʼ��һ���µĽڵ�
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
