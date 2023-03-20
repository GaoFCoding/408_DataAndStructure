#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 10
#define MaxArcNum = 10

/*
    邻接矩阵法
*/
int ArcList[MaxArcNum]; //声明一个数组用于存放图G中的边的序号

typedef struct 
{
    int Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图当前的顶点数和边数/弧数 
} MGraph;

/*
    邻接表法
*/

typedef struct ArcNode
{  
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode *next;
} ArcNode;

typedef struct VNode //顶点表节点
{
    int data; //顶点信息
    ArcNode *first; //指向第一条依附该顶点的弧的指针（出度）
}VNode, AdjList[MaxVertexNum];

typedef struct
{
    AdjList List; //邻接表
    int vexNum, arcNum; //图的顶点数和弧数
} ALGraph; //ALGraph是邻接表存储的图类型


/*
    *****基本操作的声明*****
    
    ps：考试的时候以下接口可直接调用！
*/

bool Adjacent(MGraph g, int x, int y); //判断图G是否存在边X，Y
bool Neighbors(MGraph g, int x, int ArcList[]); //列出图G中与结点x邻接的边
bool InsertVertex(MGraph &g, int x); //从图中插入结点x
bool DeleteVertex(MGraph &g, int x); //从图中删除顶点x
bool AddEdge(MGraph &g, int x, int y); //若无向边（x,y）或有向边不存在，则向图中添加该边
bool Remove(MGraph &g, int x, int y); //若无向边（x,y）或有向边存在，则删除该边
int FirstNeighbor(MGraph g, int x); //求图中顶点x的第一个邻接点，若有则返回顶点号，没有则返回-1 *
int NextNeighbor(MGraph g, int x, int y); //y是x的一个邻近点，返回y的下一个邻接点的顶点号，无则返回-1 *
float Get_edge_value(MGraph g, int x, int y); //返回边（x，y）的权值
bool Set_edge_value(MGraph &g, int x, int y, int v) //设置图中边（x，y）的对应的权值

/*
    *****基本操作的实现*****
*/

//FirstNetghbor
//返回图中顶点x的第一个邻接点，若有则返回顶点号，若没有邻接点或者x顶点不存在则返回-1
int FirstNetghbor_MGraph(MGraph g, int x)
{
    int p = 0;
    while (p < g.vexnum && g.Vex[p] != x)
    {
        p++;
    }
    if (p >= g.vexnum)
    {
        return -1;
    }
    for (int j = 0; j < g.vexnum; j++)
    {
        if (g.Edge[p][j] == 1)
        {
            return j + 1;
        }
    }
    return -1;
}

//FirstNetghbor
//返回图中顶点x的第一个邻接点，若有则返回顶点号，若没有邻接点或者x顶点不存在则返回-1
int FirstNetghbor_ALGraph(ALGraph g, int x)
{
    //在邻接表中找到该顶点
    int p = 0;
    while (p < g.vexNum && g.List[p].data != x)
    {
        p++;
    }
    if (p >= g.vexNum)
    {
        return -1;
    }
    
    //找第一个邻接点
    if (g.List[p].first == NULL)
    {
        return -1;
    }
    return g.List[p].first->adjvex;
    
}

//NextNetghbor
int NextNetghbor_MGraph(MGraph g, int x, int y)
{
    int p = 0;
    while (p < g.vexnum && g.Vex[p] != x) //找到p的数组下标
    {
        p++;
    }
    if (p >= g.vexnum)
    {
        return -1;
    }
    for (int j = y - 1; j < g.vexnum; j++) //这里假设y的数组下标是y-1（按序）
    {
        if (g.Edge[p][j] == 1)
        {
            return j + 1;
        }
    }
    return -1;
}

//NextNetghbor
int NextNetghbor_ALGraph(ALGraph g, int x, int y)
{
    //在邻接表中找到该顶点
    int p = 0;
    while (p < g.vexNum && g.List[p].data != x)
    {
        p++;
    }
    if (p >= g.vexNum)
    {
        return -1;
    }
    
    ArcNode *cur = g.List[p]->first; //指向当前弧结点的指针
    while (cur != NULL && cur->adjvex != y) //遍历单链表找到y
    {
        cur = cur->next;    
    }
    if (cur == NULL) //找不到y顶点
    {
        return -1;
    }
    if (cur->next != NULL) //返回y后面链接的顶点信息
    {
        return cur->next->adjvex;
    }
    return -1;
    
}
