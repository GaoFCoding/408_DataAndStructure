#include<stdio.h>
#include<malloc.h>
#define MaxSize 10
typedef int ElemType;


/*
	ջ Stack
	
	ջ�Ǿ�����ͬ�������͵�n������Ԫ�ص��������У�����nΪ������n = 0ʱ
	���Ա���һ���ձ�

	ջ��ֻ������һ�˽��в����ɾ�����������Ա�

	��Ҫ����:
		1. ջ��
			��������ɾ����һ��
		2. ջ��
			����������ɾ����һ��
		3. ��ջ

	��������
	1. InitStack(&S) ��ʼ��ջ
	2. DestoryStack(&L) �ݻ�ջ�����ͷ�����ռ�õ��ڴ�ռ�
	3. Push(&S,x) ��ջ����ջSδ������x����ʹ֮��Ϊ��ջ��
	4. Pop(&S,&x) ��ջ����ջS�ǿգ��򵯳�ջ��Ԫ�أ�����x����
	5. GetTop(S,&s) ��ȡջ��Ԫ�أ���ջS�ǿգ�����x����ջ��Ԫ��
	
	n����ͬԪ�ؽ�ջ����ջԪ�ز�ͬ�����еĸ���Ϊ 1/(n+1)C(n,2n)
	�����Ĺ�ʽ��Ϊ��������

*/

//˳��ջ
typedef struct {
	ElemType data[MaxSize]; //��̬������ջ��Ԫ��
	int top; //ջ��ָ�룬�յ�ʱ��Ϊ-1��������ΧΪ[0,maxSize - 1]
} SqStack;

//��ʼ��˳��ջ
void InitStack(SqStack& s)
{
	s.top = -1;
}

//�ж�ջ�Ƿ�Ϊ��
bool IsEmpty(SqStack s)
{
	if (s.top == -1)
	{
		return true;
	}
	return false;
}

//˳��ջ��ջ����
bool Push(SqStack& s, ElemType data)
{
	if (s.top == MaxSize - 1) 
	{
		return false; //ջ�����޷�����
	}
	s.top = s.top + 1; //ָ���1
	s.data[s.top] = data; //��Ԫ����ջ
	return true;
}

//˳��ջ��ջ����
//ע�⣬�����ɾ��ֻ���߼��ϵ�ɾ����ʵ���϶�Ӧ��Ԫ�ػ��Ǳ������ڴ浱�е�
bool Pop(SqStack& s, ElemType& res)
{
	if (s.top == -1)
	{
		return false; //ջ�Ѿ�Ϊ��
	}
	res = s.data[s.top]; //����ջ��Ԫ��
	s.top -= 1;

	return true;
}

//����ջ
typedef struct {
	ElemType data[MaxSize];
	int top0; //0��ջջ��ָ��
	int top1; //1��ջջ��ָ��
} ShStack;

//��ʼ��ջ
void InitShStack(ShStack& S)
{
	S.top0 = -1;
	S.top1 = MaxSize;
}

//�жϹ���ջ��������: top0 + 1 == top1