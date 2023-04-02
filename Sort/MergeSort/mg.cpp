#include<stdio.h>
#include<malloc.h>
#define len 10

/*
    归并排序
*/
int *B = (int *)malloc(len*sizeof(int)); //辅助数组

void Merge(int list[], int low, int mid, int high)
{
    int i,j,k;
    for (int k = low; k <= high; k++) //将两个相邻的待排序序列复制进辅助数组
    {
        B[k] = list[k];
    } //for

    for (i=low, j=mid+1,k=i;i <= mid && j <= high;k++) //逐位比较左右两个已排序子序列的大小
    {
        if (B[i]<=B[j])
        {
            list[k] = B[i];
            i++;
        }
        else
        {
            list[k] = B[j];
            j++;
        }
    } //for

    while (i<=mid) //将左边序列剩余的加入list
    {
        list[k] = list[i];
        k++;
        i++;
    }
    while (j<=mid) //将右边序列剩余的加入list
    {
        list[k] = list[j];
        k++;
        i++;
    }
}

void MergeSort(int list[], int low, int high) //归并排序
{
    if (low < high)
    {
        int mid = (low + high)/2;
        MergeSort(list[],low,mid); //左归并排序，直到只剩一个元素
        MergeSort(list[],mid+1,high); //右归并排序，直到只剩一个元素
        Merge(list[],low,mid,high); //归并
    }
    
}