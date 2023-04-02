#include<stdio.h>

/*
    简单选择排序

        思想：
            每一趟在待排序元素中选取关键字最小的元素加入有序子序列
*/

typedef int ElemType;

void Swap(int &a, int &b)
{
    int temp;
    temp = b;
    b = a;
    a = temp;
}

void SelectSort(ElemType List[], int n)
{
    int min;
    for (int i = 0; i < n-1; i++)
    {
        min = i;
        for (int j = i+1; j < n; j++)
        {
            if (List[j] < List[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            Swap(List[i],List[min]); //与待排序序列中的最小元素交换
        }
    }
}