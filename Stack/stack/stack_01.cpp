#include<stdio.h>
#include<malloc.h>
#define MaxSize 10
typedef int ElemType;


/*
	栈 Stack
	
	栈是具有相同数据类型的n个数据元素的有限序列，其中n为表长，当n = 0时
	线性表是一个空表

	栈是只允许在一端进行插入或删除操作的线性表

	重要术语:
		1. 栈顶
			允许插入和删除的一端
		2. 栈底
			不允许插入和删除的一端
		3. 空栈

	基本操作
	1. InitStack(&S) 初始化栈
	2. DestoryStack(&L) 摧毁栈，并释放其所占用的内存空间
	3. Push(&S,x) 进栈，若栈S未满，则将x加入使之成为新栈顶
	4. Pop(&S,&x) 出栈，若栈S非空，则弹出栈顶元素，并用x返回
	5. GetTop(S,&s) 读取栈顶元素，若栈S非空，则用x返回栈顶元素
	
	n个不同元素进栈，出栈元素不同的排列的个数为 1/(n+1)C(n,2n)
	上述的公式称为卡特兰数

*/

//顺序栈
typedef struct {
	ElemType data[MaxSize]; //静态数组存放栈中元素
	int top; //栈顶指针，空的时候为-1，索引范围为[0,maxSize - 1]
} SqStack;

//初始化顺序栈
void InitStack(SqStack& s)
{
	s.top = -1;
}

//判断栈是否为空
bool IsEmpty(SqStack s)
{
	if (s.top == -1)
	{
		return true;
	}
	return false;
}

//顺序栈进栈操作
bool Push(SqStack& s, ElemType data)
{
	if (s.top == MaxSize - 1) 
	{
		return false; //栈满，无法插入
	}
	s.top = s.top + 1; //指针加1
	s.data[s.top] = data; //新元素入栈
	return true;
}

//顺序栈出栈操作
//注意，这里的删除只是逻辑上的删除，实际上对应的元素还是保留在内存当中的
bool Pop(SqStack& s, ElemType& res)
{
	if (s.top == -1)
	{
		return false; //栈已经为空
	}
	res = s.data[s.top]; //返回栈顶元素
	s.top -= 1;

	return true;
}

//共享栈
typedef struct {
	ElemType data[MaxSize];
	int top0; //0号栈栈顶指针
	int top1; //1号栈栈顶指针
} ShStack;

//初始化栈
void InitShStack(ShStack& S)
{
	S.top0 = -1;
	S.top1 = MaxSize;
}

//判断共享栈满的条件: top0 + 1 == top1