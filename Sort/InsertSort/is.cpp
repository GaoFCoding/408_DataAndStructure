#include<stdio.h>

typedef int ElemType;

/*
    插入排序

        思想：
            每次将一个待排序的记录按其关键字的大小插入前面已排好序的子序列中，
            直到全部记录插入完成

        1. 直接插入排序
        2. 折半插入排序
        3. 希尔排序
*/

/*
    1. 直接插入排序
        升序

    时间复杂度O（n^2）
*/

void Direct_InsertSort1(ElemType List[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++) //依次遍历待排序数组的各个元素
    {
        if (List[i] < List[i-1]) //判断当前元素关键字是否小于前面一个元素
        {
            temp = List[i]; //暂存当前元素

            for (j = i-1; j >= 0 && List[j] > temp; j--) //把大于当前元素关键字的所有元素往后移一位
            {
                List[j+1] = List[j]; //后移一位
            }

            List[j+1] = temp;
        }
    }
}

//带哨兵实现，数组元素从下标1开始
void Direct_InsertSort2(ElemType List[], int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        if (List[i] < List[i-1])
        {
            List[0] = List[i];
            for (j = i-1; List[j] > List[0]; j--)
            {
                List[j+1] = List[j];
            }
            List[j+1] = List[0];
        }
    }
}

/*
    2. 折半插入排序
        升序

        比较的时间复杂度：O（n*log2n）
        总时间复杂度不变，仍然为O(n^2)

        注意：
            当low > high时停止查找，将[low, i-1]内的元素全部右移，并将A[0]复制到low所指的位置

            当A[mid] == A[0]时，为了保证算法的“稳定性”，应该继续在mid位置的右边寻找插入的位置
*/

void Binary_InsertSort(ElemType List[], int n)
{
    int Left, Right;
    int mid;

    for (int i = 2; i <= n; i++)
    {
        List[0] = List[i]; //暂存到哨兵中

        Left = 1;
        Right = i-1;
        while (Left <= Right) //二分查找
        {
            mid = (Left+Right)/2;
            if (List[mid] > List[0])
            {
                Right = mid - 1;
            }
            else
            {
                Left = mid + 1;
            }
        }
        
        for (int j = i-1; j >= Right+1; j--)
        {
            List[j+1] = List[j]; //把从low（right+1）指针到i-1的全体元素右移
        }
        List[Right+1] = List[0];
        
    }
}

int main()
{
    int arr1[] = { 12, 11, 13, 5, 6 }, n = 5;

    printf("Direct_InsertSort1:\n");

    Direct_InsertSort1(arr1, n);
    for (int i = 0; i < n; i++)
    {
        printf(" %d ",arr1[i]);
    }

    printf("\nDirect_InsertSort2:\n");

    int arr2[] = {0, 12, 11, 13, 5, 6 };
    Direct_InsertSort2(arr2, n);
    for (int i = 1; i <= n; i++)
    {
        printf(" %d ",arr2[i]);
    }
    
    printf("\nDirect_InsertSort3:\n");
    int arr3[] = {0, 12, 11, 13, 5, 6 };
    Binary_InsertSort(arr3, n);
    for (int i = 1; i <= n; i++)
    {
        printf(" %d ",arr3[i]);
    }
}