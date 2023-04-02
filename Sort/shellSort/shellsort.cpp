#include<stdio.h>

typedef int ElemType;

/*
    希尔排序

        思想:
            先将排序表分割成若干个特殊的子表[i,i+d,i+2d,...,i+kd]，对各子表分别进行直接插入排序，缩小增量d，
            重复上述过程，直到d为1位置
*/

//使用List[0]作为暂存单元，他不是哨兵，因此仍然需要做数组越界判断
void ShellSort1(ElemType List[], int n)
{
    int i, j;
    int d; //步长
    for (d = n/2; d >= 1; d/=2) //对各个子序列分别进行希尔排序，并不断缩小步长d的值，直到d=1
    {
        for (i = d+1; i <= n; i++)
        {
            if (List[i] < List[i-d])
            {
                List[0] = List[i]; //待插入元素暂存到数组暂存单元中

                for (j = i-d; j > 0 && List[j] > List[0]; j-=d) //子序列比List[0]小的元素都右移d个单位
                {
                    List[j+d] = List[j];
                }
                List[j+d] = List[0];
            } //if
        }
    }
}

//另外使用变量作为暂存单元
void ShellSort2(ElemType List[], int n)
{
    int i, j, temp;
    int d; //步长
    for (d = n/2; d >= 1; d/=2) //对各个子序列分别进行希尔排序，并不断缩小步长d的值，直到d=1
    {
        for (i = d; i < n; i++)
        {
            if (List[i] < List[i-d])
            {
                temp = List[i]; //待插入元素暂存到数组暂存单元中

                for (j = i-d; j >= 0 && List[j] > temp; j-=d) //子序列比List[0]小的元素都右移d个单位
                {
                    List[j+d] = List[j];
                }
                List[j+d] = temp;
            } //if
        }
    }
}

int main() {

    int i, n = 5;

    int arr1[] = {0, 12, 34, 54, 2, 3};
    printf("Array1 before sorting: \n");
    for (i = 1; i <= n; i++)
        printf("%d ", arr1[i]);
    ShellSort1(arr1, n);
    printf("\nArray1 after sorting: \n");
    for (i = 1; i <= n; i++)
        printf("%d ", arr1[i]);

    printf("\n");

    int arr2[] = {12, 34, 54, 2, 3};
    printf("Array2 before sorting: \n");
    for (i = 0; i < n; i++)
        printf("%d ", arr2[i]);
    ShellSort2(arr2, n);
    printf("\nArray2 after sorting: \n");
    for (i = 0; i < n; i++)
        printf("%d ", arr2[i]);
    return 0;
}