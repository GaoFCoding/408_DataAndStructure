#include<stdio.h>

/*
    二分查找

        仅使用与有序的顺序表，只能基于顺序表，不能基于链表

        判定树树高h = [log2(n + 1)]向上取整，与完全二叉树的树高相同，并且判定树是二叉平衡树
        有n个圆形结点（元素个数）和n+1个方形结点（空链域，代表查找失败）

        mid = [(low + high)/2]向下或向上取整
            如果向上取整：
                mid和high为奇数个元素时，被mid分割后左右两部分元素个数相同
                若为偶数个元素，则分割后左半部分比右半部分少一个元素

            如果向下取整：
                mid和high为奇数个元素时，被mid分割后左右两部分元素个数相同
                若为偶数个元素，则分割后左半部分比右半部分多一个元素

            ps:mid向上和向下取整，得到的判定树会不同

        ASL：
            log2(n+1)-1

        由判定树可以推出时间复杂度：
            O（log2n）
*/

typedef int ElemType;

typedef struct
{
    ElemType *data;
    int TableLen; //表长
} SSTable;

//循环实现
int Binary_search1(SSTable s, ElemType target)
{
    int l = 0, r = s.TableLen - 1; //左右指针
    int mid;
    while (l <= r)
    {
        mid = (l + r)/2;
        if (s.data[mid] == target)
        {
            return mid;
        }
        else if (s.data[mid] > target)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }       
    }
    return -1;
}

//递归实现
int Binary_search2(SSTable s, ElemType target, int l, int r)
{
    int mid = (l + r)/2;

    if (l > r)
    {
        return -1; //查找失败
    }

    if (s.data[mid] == target)
    {
        return mid;
    }
    else if (s.data[mid] > target)
    {
        Binary_search2(s, target, l, mid-1);
    }
    else
    {
        Binary_search2(s, target, mid+1, r);
    }
}