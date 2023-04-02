#include<stdio.h>

typedef int ElemType;

/*
    交换排序

        1. 冒泡排序
        2. 快速排序
*/

/*
    1. 冒泡排序

        思想：
            基于比较和交换的排序，从前往后两两比较相邻元素的值，若为逆序，则交换他们
            直到序列比较完。我们称他为第一趟冒泡，结果是将最小的元素交换到待排序列的第一个位置。

            每一次冒泡都确定一个元素的最终位置，即按序不断往前面/后面 冒泡

        优化思路：
            可以设置一个flag，若有一趟不存在任何交换，则说明排序已经完成，可以直接退出

        空间复杂度：O（1）
        
        最坏时间复杂度：O（n^2）
        平均时间复杂度：O（n^2）
        最好时间复杂度：O（n） //只需比较n-1次，就可以直接跳出循环

        ps：冒泡排序支持链式实现
*/

//交换
void Swap(int &a, int &b)
{
    int temp;
    temp = b;
    b = a;
    a = temp;
}

//冒泡排序，从后往前冒，按升序，其他同理
void BubbleSort1(ElemType List[], int n)
{
    bool flag;
    for (int i = 0; i < n-1; i++)
    {
        flag = false;
        for (int j = n-1; j > i; j--)
        {
            if (List[j] < List[j-1])
            {
                Swap(List[j],List[j-1]);
                flag = true;
            }    
        }
        if (flag == false)
        {
            return;
        }
    }
}

//冒泡排序，从前往后冒，按升序，其他同理
void BubbleSort2(ElemType List[], int n)
{
    int flag;
    for (int i = n-1; i > 0; i--)
    {
        flag = false;
        for (int j = 0; j < i; j++)
        {
            if (List[j] > List[j+1])
            {
                Swap(List[j],List[j+1]);
                flag = true;
            }
        }
        if (flag == false)
        {
            return;
        }   
    }
}




int main()
{
    int arr1[] = {5, 3, 8, 6, 7, 2};
    BubbleSort1(arr1,6);

    printf("Sort1 result is : \n");

    for (int i = 0; i < 6; i++)
    {
        printf(" %d ",arr1[i]);
    }

    int arr2[] = {5, 3, 8, 6, 7, 2};
    BubbleSort2(arr2,6);

    printf("\nSort2 result is : \n");

    for (int i = 0; i < 6; i++)
    {
        printf(" %d ",arr2[i]);
    }
    return 0;
}