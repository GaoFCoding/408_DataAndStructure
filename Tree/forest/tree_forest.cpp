#include<stdio.h>
#include<malloc.h>
#define MaxSize 100

typedef char ElemType;

//双亲表示法
typedef struct
{       
    ElemType data;
    int parent; //父节点的数组下标，无则为-1
} TreeNode;

struct Tree1
{
    TreeNode* TreeNodes[MaxSize];
    int nums;
};


//孩子表示法
typedef struct LNode
{
    int index; //孩子节点的数组下标
    struct LNode* next;
} LNode, *LinkList;

typedef struct
{
    ElemType data;
    LNode * firstChild;
} NodeData;

struct Tree2
{
    NodeData* TreeNodes[MaxSize];
    int NodesNum;
};


