#include<stdio.h>

typedef int ElemType;

/*
    快速排序

        分而治之的编程思想
            每一次的划分都确定一个元素的最终位置

        pivot 支点
        pivotpos 枢轴位置
*/

//用第一个元素将待排序序列划分成左右两个部分
int Partition(int A[], int low, int high)
{  
    int pivot = A[low]; //枢轴点选择low指针指向的位置

    while (low < high) //用low、high搜索枢轴的最终位置
    {
        while (low < high && A[high] >= pivot) //high指针一路往右找，直到找到小于pivot值的元素，把他放到前面low的位置
        {
            high--;
        }
        A[low] = A[high];
        while (low < high && A[low] <= pivot) //low指针一路往左找，直到找到大于pivot值得元素，把他放到high指针的位置
        {
            low++;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(int A[], int low, int high)
{
    if (low < high) //若不满足该条件，即划分到只有一个元素时，退出递归
    {
        int pivotpos = Partition(A, low, high); //划分操作,返回划分后low,high两个指针共同指向的位置
        QuickSort(A, low, pivotpos-1);   //划分左子表
        QuickSort(A,pivotpos+1, high);   //划分右子表
    }
}

int main()
{
    int arr1[] = {5, 3, 8, 6, 7, 2};
    QuickSort(arr1,0,5);

    printf("Sort1 result is : \n");

    for (int i = 0; i < 6; i++)
    {
          printf(" %d ",arr1[i]);
    }
}