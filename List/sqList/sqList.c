/*
	顺序表

	知识点：
		1. 声明和初始化结构体指针
			struct <Person> * p1; //声明p1为Person类型结构体指针
			p1 = &p2 //使用&使p1指向p2结构体实例

		2. 结构体数组声明与访问
			struct Person personList[10];

			personList[0].name = ....


		3. 指针访问结构体成员
			(*p1).name == p1->name //可以理解为是一种语法糖？

		动态分配与静态分配

			熟练使用malloc和free动态分配内存

	顺序表的特点：
		1. 随机访问，可以在O（1）时间内找到第i个元素
			data[i-1]
		2. 存储密度高，每个节点只存储数据元素

		3. 拓展容量不方便，动态分配的复杂度较高
		4. 插入删除不方便，需要移动大量的元素
*/
#include<stdio.h>
#define MaxSize 10
typedef int ElemType;
typedef int Status;
/*
	初始化顺序表 -- 静态分配

	缺点：
		顺序表大小，容量不可调
*/
typedef struct {
	ElemType array[MaxSize];
	int Length;
} sqList_Static;

//初始化静态数据表
Status InitStaticList(sqList_Static* L)
{
	for (int i = 0; i < MaxSize; i++) //这里不对每一位元素进行初始化也不会报错，但是由编译器为我们自动分配的内存会初始化一些奇奇怪怪的数
	{
		L->array[i] = 0; //初始化数组的每一个元素
		//相当于(*L).array[i] = 0;
	}
	L->Length = 0; //初始化长度为0
}

Status InsertNum(sqList_Static* L, int i, int e)
/*
	最坏时间复杂度
		O(n)  问题规模n = L.length

	输入i
		要插入的位置，不是索引值
	输入e
		要插入的值
*/
{
	if (i > L->Length + 1 || i < 1) //检查输入i是否合法
	{
		printf("插入索引无效");
		return -1;
	}

	if (L->Length >= MaxSize) //判断当前长度是否已达到最大长度
	{
		return -2;
	}

	for (int index = L->Length; index >= i; index--) //第i个元素及之后的元素都往后移一个单位
	{
		L->array[index] = L->array[index - 1];
	}
	L->array[i - 1] = e; //插入元素，注意的是要插入的位置是i-1，因为i是索引值，实际上对应的位置是i+1
	L->Length += 1; //当前长度增加1
}

Status DeleteNum(sqList_Static* L, int i, int* e)
{
	if (i > L->Length || i < 1) //判断输入i是否合法
	{
		printf("索引无效");
		return -1;
	}

	*e = L->array[i - 1]; //返回删除的e的值

	for (int index = i; index < L->Length; index++) //删除i后面的元素
	{
		L->array[index - 1] = L->array[index];
	}
	L->array[L->Length - 1] = 0; //将原来的最后一位置零
	L->Length -= 1;
}

//按位查找，时间复杂度O(1)
Status FindByIndex(sqList_Static* L, int index, int* res)
{
	*res = L->array[index - 1];
}

//按值查找
Status FindByNum(sqList_Static* L, int target, int* index)
{
	for (int i = 0; i < L->Length; i++)
	{
		if (L->array[i] == target) {
			*index = i + 1; //返回目标元素的位置
			return;
		}
	}
}
/*
	顺序表 - 动态分配

		通过malloc函数动态分配顺序表内存空间
*/
typedef struct {
	ElemType* data;
	int Length; //当前长度
	int MaxLength; //最大长度
} sqList_Dynamic;

//初始化动态顺序表
Status InitDynamicList(sqList_Dynamic* List)
{
	//使用malloc函数分配内存空间
	List->data = (ElemType*)malloc(sizeof(ElemType) * MaxSize); //malloc返回一个地址，使用强类型转换变换为ElemType的指针类型
	List->Length = 0; //初始化长度为0
	List->MaxLength = MaxSize; //初始化最大长度
}

//动态增加长度
Status IncreaseSize(sqList_Dynamic* List, int len)
{
	int* p = List->data; //拷贝一份*data的指针，可以理解为对data数组拷贝
	List->data = (ElemType*)malloc(sizeof(ElemType) * (len + List->MaxLength)); //重新为data顺序表分配内存地址，长度增加len
	for (int i = 0; i < List->Length; i++) //将p指向的顺序表元素拷贝到新初始化的data顺序表中
	{
		List->data[i] = p[i];
	}
	List->MaxLength += len; //最大长度增加
	free(p); //释放变量p的内存
}


void Test_sqList(void) {

	sqList_Static List_static;
	InitStaticList(&List_static); //静态分配内存

	sqList_Dynamic List_dynamic;
	InitDynamicList(&List_dynamic); //动态分配内存

	InsertNum(&List_static, 1, 1);
	InsertNum(&List_static, 2, 2);
	InsertNum(&List_static, 3, 3);
	InsertNum(&List_static, 4, 4);
	printf("\n");

	int resIndex;
	FindByNum(&InitStaticList, 2, &resIndex);
	printf("res index is : %d\n", resIndex);

	for (int i = 0; i < MaxSize; i++)
	{
		printf("%d", List_static.array[i]);
	}

	int res;
	DeleteNum(&List_static, 1, &res);
	DeleteNum(&List_static, 1, &res);
	printf("\n");
	for (int i = 0; i < MaxSize; i++)
	{
		printf("%d", List_static.array[i]);
	}
	printf("\nres is %d", res);
}

void main(void) {
	Test_sqList();
}


