#include<stdio.h>

/*
    堆排序（选择排序）

        选择排序思想：
            每一趟在待排序元素中选取关键字最小（或最大）的元素加入有序子序列中

        堆数据结构（Heap）


*/

/*
    建立大根堆

        详细内容见书本

        
        由于堆可以看出用顺序结构存储的完全二叉树，因此有必要补充一些前面
        二叉树学的一些知识：
            1. 
                i <= [n/2]向下取整 的所有节点都是分支节点，否则为叶子节点
            2.
                节点i的左孩子是2i,右孩子是2i+1，存在的前提均是2i <= n, 2i+1 <= n
*/

/*
    1. 大根堆排序

        最终得到一个递增序列
*/

void BuildMaxHeap(int List[], int len)
{
    for (int i = len/2; i > 0; i--) //遍历所有非终端节点，并对其进行调整
    {
        HeadAdjust(List,i,len);
    }
    
}

void HeadAdjust(int List[], int k, int len)
{
    List[0] = List[k]; //暂存子树的根节点
    for (int i = 2*k; i <= len; i*=2) //沿着key较大的子结点向下筛选，直到超过树的结点编号，即该孩子结点不存在
    {
        if (i < len && List[i] < List[i+1]) //左孩子i跟顶点k的右孩子i+1对比，取更大的，i < len保证右孩子存在
        {
            i++;
        }
        if (List[i] <= List[0]) //若孩子i小于等于顶点k的值，则满足大根堆，退出比较，该终端节点满足条件
        {
            break;
        }
        else //若孩子i的key比顶点k更大，则把孩子的值赋给k
        {
            List[k] = List[i];
            k = i; //以该孩子节点i为开始，继续往下重复上面的操作，直到找到能够允许List[0]插入的位置
        } //继续下一轮循环，实现小元素不断下坠
    }
    List[k] = List[0]; //最后把List[0]插入到他应该插入的位置
}

//堆排序完整的逻辑
void Swap(int &a, int &b)
{
    int temp;
    temp = b;
    b = a;
    a = temp;
}


void HeapSort(int List[], int len)
{
    BuildMaxHeap(List, len); //初始化，构建大根堆
    for (int i = len; i > 1; i--)
    {
        Swap(List[i],List[1]); //把堆顶和堆底元素交换
        HeadAdjust(List,1,i-1); //把剩下的待排序的元素整理成堆，因为变化的只有堆顶元素，因此只需对堆顶元素再进行下坠调整
    }
}


/*
    2. 小根堆的排序

        最终得到一个递减的序列
*/

/*
    建立小根堆
*/
BuildMixHeap(int List[],int len) //建立小根堆
{
    for (int i = len/2; i > 0; i--) //依次调整每个非终端节点
    {
        HeadAdjust_Mix(List, i, len);
    }
}

void HeadAdjust_Mix(int List[], int k, int len)
{   
    List[0] = List[k];
    for (int i = 2*k; i <= len; i*=2) //往孩子节点下坠
    {
        if (i < len && List[i+1] < List[i]) //选出左右孩子节点较小的一个
        {
            i++;
        }
        if (List[i] >= List[0]) //若孩子比根大，满足小根堆条件
        {
            break;
        }
        else
        {
            List[k] = List[i];
            k = i; //继续基于该节点往下他的孩子节点下坠
        } //if
    }
    List[k] = List[0]; //把list[0]放入经过多轮下坠后的最终位置，垃圾，就该扔到垃圾桶里

}

void HeapSort_Mix(int List[], int len)
{
    BuildMixHeap(List,len); //建立小根堆
    for (int i = len; i > 1; i--)
    {
        Swap(List[1],List[i]); //交换
        HeadAdjust_Mix(List,1,i-1) //交换后对堆顶进行一次调整
    }
    
}

/*
    3.堆的插入与删除
    
        对于小根堆：

            插入元素：
                新元素放表尾，与父节点(i/2)对比，若新元素比父节点更小，则将二者互换，
                新元素就这样一路上升，直到无法继续上升为止。

            删除元素：
                被删除的元素用堆底元素替换，然后让该元素不断下坠，直到无法下坠为止。


    对于大根堆的插入删除也类似，不再赘述

    总之，插入就是不断上升的过程，下坠就是不断下降的过程
*/

