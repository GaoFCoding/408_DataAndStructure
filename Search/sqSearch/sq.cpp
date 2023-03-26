#include<stdio.h>

/*
    顺序查找

    查找各元素概率相同时
        ASL成功 = (n+1)/2
        ASL失败 = n+1
    查找各元素概率不相同时
        可以把概率大的放到查找表前面进行查找长度的优化

    可以通过对顺序查找前先进行有序排列，然后通过判定树减少查找次数

        ASL成功 = (n+1)/2
        ASL失败 = n/2 + n/(1+n)

    时间复杂度：O(n)
*/

typedef int ElemType;

typedef struct
{
    ElemType *data;
    int TableLen; //表长
} SSTable;

int Search_Seq1(SSTable s, ElemType target) //顺序查找，返回数组下标，找不到则返回0
{
    int i;
    s.TableLen[0] = target; //哨兵，减少数组越界判断
    for (i = s.TableLen; s.data[i] != target; i--); //数组下标有效范围从1到TableLen
    return i;
}

//无哨兵情况，需要判断是否越界
int Search_Seq2(SSTable s, ElemType target) //顺序查找，返回数组下标，找不到则返回0
{
    int i = 0;
    while (s.data[i] != target && i < s.TableLen)
    {
        i++;
    }
    if (i >= s.TableLen)
    {
        return 0;
    }
    return i;
}