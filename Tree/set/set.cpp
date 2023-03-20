#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

/*
    查并集
*/

typedef int nodeNum;

typedef struct UFSet
{
    nodeNum List[MaxSize]; //存放双亲节点编号的数组
    int nums; //当前森林中树的数量 
} UFSet;

//初始化操作
bool InitUFset(UFSet &set)
{
    for (int i = 0; i < MaxSize; i++)
    {
        set.List[i] = -1;
    }
    set.nums = MaxSize;
    return true;
}   

/*
    Find操作
        函数在并查集中查找并返回包含元素x的树的根
*/
nodeNum Find(UFSet s, nodeNum x)
{
    if (s.List[x] < 0)
    {
        return x;
    }
    Find(s, s.List[x]); //尾递归寻找到该树的根节点
}

/*
    判断两个元素是否属于同一集合，只需要分别找到他们的根节点，
    比较根节点是否相同即可
*/

/*
    Union操作
        函数求两个不相交子集合的并集
        root1和root2是通过find操作得到的两个子集合的根（他的所属的树）
*/
bool Union(UFSet &s, nodeNum root1, nodeNum root2)
{
    if (root1 == root2)
    {
        return false;
    }
    s.List[root2] = root1;
    s.nums--; //合并后森林中的树数量减一
    return true;
}

int main()
{
    return 0;
}

