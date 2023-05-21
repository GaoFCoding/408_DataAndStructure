#include<stdio.h>
#include<malloc.h>
#define MaxSize 10
typedef int ElemType;
typedef int Status;

/*
	静态链表
	参考书本P32
*/

typedef struct Node {
	ElemType data;
	int next; //指向下一个节点
}component,SlinkList[MaxSize];

//初始化静态链表
bool InitSpace_SL(SlinkList &SL)
{
	for (int i = 0; i < MaxSize-1; i++) 
	{
		SL[i].next = i+1;
		SL[i].data = 0;		
	}
	SL[MaxSize-1].next = 0; //最后一个元素指向头元素
	SL[MaxSize-1].data = 0;

	return true;
}

Status LocateElem_Sl(SlinkList sl,ElemType e)
{
	//在静态链表中找到第一个值为e的元素
	//若找到则返回它在sl中的位序，找不到则返回0

	int curr = sl[0].next; //获取静态链表头指向的下一个位置
	while (curr && sl[curr].data != e)
	{
		curr = sl[curr].next; //指针移动
	}
	return curr; //若找不到，则curr回到表头的0；若找到则返回curr值，即为从1开始计数的该元素第一次出现的所在的位置
}

int main(void)
{
	SlinkList SL;
	InitSpace_SL(SL); //初始化
}
