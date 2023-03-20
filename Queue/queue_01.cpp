#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef int ElemType;

/*
	队列
		先进先入FIFO(first in first out)
		从一端输入，从另一端删除

	专业术语:
		队头，队尾，空队列

	队列也是一种线性表，准确来说是操作受限的线性表

	队列的基本操作
		1. 初始化队列
		InitQueue(&Q)

		2. 销毁队列
		DestoryQueue(&Q)

		3. 入队
		EnQueue(&Q,x)

		4.出队
		DeQueue(&Q,&x)

		5.读队尾元素
		GetHead(Q,&x)

		6.判断是否为空
		QueueEmpty(Q)

		循环队列
			通过‘模运算’将存储空间在逻辑上限制为0-10的环状区域
			比如;
				rear指针到9时，即指向最后一个元素时，rear+1 = 10 --> 10%MaxSize == 0 -->又回到队首
			队列满的条件：
				队尾的下一个位置是队头
				即：
					(rear+1)%MaxSize == front

			循环队列要牺牲掉一个元素的存储空间，用于区分队列是否已满或者为空，即：
				MaxSize = 10时，实际上占用的存储空间只有9个元素

			队列元素的个数：
				(rear + MaxSize - front) % MaxSize

			如何判断队满和队空?
				1. 
					front == rear时队空
					(rear+1)%MaxSize == front时队满
						头指针在尾指针的后一个位置
				
					缺点:
						损失了一个元素的储存空间用于区分队满和队空，即不允许队满时rear和front指向同一个地方

				2. 
					加入一个变量size，初始化为0，加入一个元素时size++，拿出一个元素时size--
					当队空时size == 0，队满时size == MaxSize

					优点：
						允许队满和队空时，rear == front

				3. 
					新增一个变量tag，每次删除操作成功时，tag = 0；插入操作成功时，tag = 1
					队满条件：front == size && tag == 1
						意思是插入操作使得队列满
					队空条件：front == size && tag == 0

					优点：
						允许队满和队空时，rear == front
					

			以上都是基于rear队尾指针指向最后一个元素的下一位，若rear指向队尾元素，则代码需要以下调整：
				
				1. 初始化队列时，需要令front = 0 ，rear = MaxSize - 1 

					注意：
						此时，判断队空的条件变成了 (rear+1)%MaxSize == front

						队满条件
							1. 牺牲一个存储单元
								头指针在尾指针的后一个位置为空 
								头指针在尾指针的后两个位置为满（头指针与尾指针之间隔着一个元素）
							2. 增加辅助变量
								增加size或tag均可

				2. 插入操作时，先将队尾指针往后移一位，再赋值


*/	

//队列的顺序表实现
typedef struct {
	ElemType* data;
	int front, rear; //队头，队尾指针
} sqQueue;

//初始化顺序队列
bool InitSqQueue(sqQueue& q)
{
	q.data = (ElemType*)malloc(MaxSize * sizeof(ElemType));
	for (int i = 0; i < MaxSize; i++) //初始化队列中的所有元素为0
	{
		q.data[i] = 0;
	}
	q.front = q.rear = 0; //队头，队尾指针初始值设为0
	return true;
}

//判断队列是否为空
bool QueueEmpty(sqQueue q)
{
	if (q.front == q.rear)
	{
		return true;
	}
	return false;
}

//入队
bool EnQueue(sqQueue& q, ElemType data)
{
	if ((q.rear+1)%MaxSize == q.front) 
	{
		return false; //此时队列已存满
	}
	q.data[q.rear] = data;
	q.rear = (q.rear + 1) % MaxSize; //队尾指针往后移一位
	return true;
}

//出队
bool DeQueue(sqQueue& q, ElemType& res)
{
	//判断队列是否已为空
	if (q.rear == q.front)
	{
		return false;
	}
	res = q.data[q.front]; //这里的出队是逻辑上的出，实际上还是占用着内存空间
	q.front = (q.front + 1) % MaxSize; //队头指针往后移一位
	return true;
}

//获取队头元素
bool GetHead(sqQueue& q, ElemType& res)
{
	if (q.rear == q.front)
	{
		return false;
	}
	res = q.data[q.front];
	return true;
}

