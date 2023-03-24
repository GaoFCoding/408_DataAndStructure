#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 100

/*

    拓扑排序

    概念：

        1. 有向无环图（DAG图）
            若一个有向图不存在环，则称为有向无环图，简称DAG图
        
        2. AOV网：
            用DAG表示一个工程，顶点表示活动，用有向边表示活动的正确执行顺序
        
        拓扑排序：
            找到一个DAG图代表的工程的各个事件（顶点）的正确执行顺序

    拓扑排序分类：

        1. 正向拓扑排序

        2. 逆向拓扑排序

        ps：以上都可以通过DFS和借助栈的方式实现

    实现方法：

        1. 借助栈
            
        2. DFS(深度优先)

    时间复杂度：
        时间开销来源：输出各个顶点的同时还要删除以它的起点的边，因此需要对当前顶点的出度进行遍历，并将指向的顶点的入度数-1

        1. 邻接矩阵表示 O（|V|^2）
        2. 邻接表      O（|V|+|E|）

*/

//图的邻接表存储结构声明
typedef struct ArcNode
{  
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode *next;
} ArcNode;

typedef struct VNode //顶点表节点
{
    char data; //顶点信息
    ArcNode *first; //指向第一条依附该顶点的弧的指针（出度）
}VNode, AdjList[MaxVertexNum];

typedef struct
{
    AdjList List; //邻接表
    int vexNum, arcNum; //图的顶点数和弧数
} ALGraph; //ALGraph是邻接表存储的图类型

//图的基本操作声明
int FirstNeighbor(ALGraph g, int x); //求图中顶点x的第一个邻接点，若有则返回顶点号，没有则返回-1
int NextNeighbor(ALGraph g, int x, int y); //y是x的一个邻近点，返回y的下一个邻接点的顶点号，无则返回-1

//栈的声明
typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *Stack;

//栈的基本操作声明
bool InitStack(Stack &s); //初始化栈
bool Push(Stack &s, int newdata); //入栈
bool Pop(Stack &s, int &res); //出栈
bool IsEmpty(Stack s); //判断是否为空

bool Visit(int vertex); //访问顶点

/*********************算法实现***************************/

/*
    1. 借助栈实现
*/

int Indegree[MaxVertexNum]; //该数组用于记录各顶点的入度数
int Print[MaxVertexNum]; //顶点输出序列

//假设Indegree[]和Print[]在调用拓扑排序前已经初始化完成了
bool TopologicalSort(ALGraph g)
{
    Stack s;
    InitStack(s); //初始化栈

    int i;
    for (i = 0; i < g.vexNum; i++)
    {
        if (Indegree[i] == 0) //开始前将所有入度为0的顶点入栈
        {
            Push(s, Indegree[i]);
        }
    }

    int count = 0;
    
    while (!IsEmpty(s))
    {
        Pop(s, i); //出栈
        Print[count++] = i; //输出顶点i
        for (int w = FirstNeighbor(g, i); w > 0; w = NextNeighbor(g, i, w))
        {
            if (!(--Indegree[w]))
            {
                Push(s, w); //若入度减1后度数为0，则入栈
            }     
        }
    }
    
    if (count < g.vexNum) //若print数组不包含全部顶点，说明一定存在回路
    {
        return false;
    }
    
    return true; //拓扑排序成功
}

/*
    2. BFS实现逆序的拓扑排序
*/
bool visited[MaxVertexNum];

void BFS_Traverler(ALGraph g)
{
    for (int i = 0; i < g.vexNum; i++) //初始化visited数组
    {
        visited[i] = false;
    }
    
    for (int i = 0; i < g.vexNum; i++)
    {
        if (!visited[i])
        {
            BFS(g, i);
        }
    }
}

void BFS(ALGraph g, int cur)
{
    visited[cur] = true;

    for (int w = FirstNeighbor(g, cur); w > 0; w = NextNeighbor(g, cur, w))
    {
        if (!visited[w])
        {
            BFS(g, w);    
        }
    }

    Visit(cur);
}