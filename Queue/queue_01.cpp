#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef int ElemType;

/*
	����
		�Ƚ�����FIFO(first in first out)
		��һ�����룬����һ��ɾ��

	רҵ����:
		��ͷ����β���ն���

	����Ҳ��һ�����Ա�׼ȷ��˵�ǲ������޵����Ա�

	���еĻ�������
		1. ��ʼ������
		InitQueue(&Q)

		2. ���ٶ���
		DestoryQueue(&Q)

		3. ���
		EnQueue(&Q,x)

		4.����
		DeQueue(&Q,&x)

		5.����βԪ��
		GetHead(Q,&x)

		6.�ж��Ƿ�Ϊ��
		QueueEmpty(Q)

		ѭ������
			ͨ����ģ���㡯���洢�ռ����߼�������Ϊ0-10�Ļ�״����
			����;
				rearָ�뵽9ʱ����ָ�����һ��Ԫ��ʱ��rear+1 = 10 --> 10%MaxSize == 0 -->�ֻص�����
			��������������
				��β����һ��λ���Ƕ�ͷ
				����
					(rear+1)%MaxSize == front

			ѭ������Ҫ������һ��Ԫ�صĴ洢�ռ䣬�������ֶ����Ƿ���������Ϊ�գ�����
				MaxSize = 10ʱ��ʵ����ռ�õĴ洢�ռ�ֻ��9��Ԫ��

			����Ԫ�صĸ�����
				(rear + MaxSize - front) % MaxSize

			����ж϶����Ͷӿ�?
				1. 
					front == rearʱ�ӿ�
					(rear+1)%MaxSize == frontʱ����
						ͷָ����βָ��ĺ�һ��λ��
				
					ȱ��:
						��ʧ��һ��Ԫ�صĴ���ռ��������ֶ����Ͷӿգ������������ʱrear��frontָ��ͬһ���ط�

				2. 
					����һ������size����ʼ��Ϊ0������һ��Ԫ��ʱsize++���ó�һ��Ԫ��ʱsize--
					���ӿ�ʱsize == 0������ʱsize == MaxSize

					�ŵ㣺
						��������Ͷӿ�ʱ��rear == front

				3. 
					����һ������tag��ÿ��ɾ�������ɹ�ʱ��tag = 0����������ɹ�ʱ��tag = 1
					����������front == size && tag == 1
						��˼�ǲ������ʹ�ö�����
					�ӿ�������front == size && tag == 0

					�ŵ㣺
						��������Ͷӿ�ʱ��rear == front
					

			���϶��ǻ���rear��βָ��ָ�����һ��Ԫ�ص���һλ����rearָ���βԪ�أ��������Ҫ���µ�����
				
				1. ��ʼ������ʱ����Ҫ��front = 0 ��rear = MaxSize - 1 

					ע�⣺
						��ʱ���ж϶ӿյ���������� (rear+1)%MaxSize == front

						��������
							1. ����һ���洢��Ԫ
								ͷָ����βָ��ĺ�һ��λ��Ϊ�� 
								ͷָ����βָ��ĺ�����λ��Ϊ����ͷָ����βָ��֮�����һ��Ԫ�أ�
							2. ���Ӹ�������
								����size��tag����

				2. �������ʱ���Ƚ���βָ��������һλ���ٸ�ֵ


*/	

//���е�˳���ʵ��
typedef struct {
	ElemType* data;
	int front, rear; //��ͷ����βָ��
} sqQueue;

//��ʼ��˳�����
bool InitSqQueue(sqQueue& q)
{
	q.data = (ElemType*)malloc(MaxSize * sizeof(ElemType));
	for (int i = 0; i < MaxSize; i++) //��ʼ�������е�����Ԫ��Ϊ0
	{
		q.data[i] = 0;
	}
	q.front = q.rear = 0; //��ͷ����βָ���ʼֵ��Ϊ0
	return true;
}

//�ж϶����Ƿ�Ϊ��
bool QueueEmpty(sqQueue q)
{
	if (q.front == q.rear)
	{
		return true;
	}
	return false;
}

//���
bool EnQueue(sqQueue& q, ElemType data)
{
	if ((q.rear+1)%MaxSize == q.front) 
	{
		return false; //��ʱ�����Ѵ���
	}
	q.data[q.rear] = data;
	q.rear = (q.rear + 1) % MaxSize; //��βָ��������һλ
	return true;
}

//����
bool DeQueue(sqQueue& q, ElemType& res)
{
	//�ж϶����Ƿ���Ϊ��
	if (q.rear == q.front)
	{
		return false;
	}
	res = q.data[q.front]; //����ĳ������߼��ϵĳ���ʵ���ϻ���ռ�����ڴ�ռ�
	q.front = (q.front + 1) % MaxSize; //��ͷָ��������һλ
	return true;
}

//��ȡ��ͷԪ��
bool GetHead(sqQueue& q, ElemType& res)
{
	if (q.rear == q.front)
	{
		return false;
	}
	res = q.data[q.front];
	return true;
}

