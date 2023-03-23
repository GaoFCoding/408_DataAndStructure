#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 100

/*
    树的广度优先算法

    要点：
        1. 找到与一个顶点相邻的所有顶点
        2. 标记哪些顶点被访问过
        3. 需要一个辅助队列
        4. 需要一个visited辅助数组来记录已经访问过的顶点
*/

//邻接矩阵类型的图类型声明
typedef struct 
{
    int Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图当前的顶点数和边数/弧数 
} MGraph;

//基本操作声明
int FirstNeighbor(MGraph g, int x); //求图中顶点x的第一个邻接点，若有则返回顶点号，没有则返回-1
int NextNeighbor(MGraph g, int x, int y); //y是x的一个邻近点，返回y的下一个邻接点的顶点号，无则返回-1



//队列类型声明
typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LinkNode;

typedef struct {
	LinkNode* front, * rear;
} LinkQueue;

//队列的基本操作声明
bool InitQueue(LinkQueue &q); //初始化
bool Enqueue(LinkQueue &q, int s); //入队
bool Dequeue(LinkQueue &q, int &res); //出队
bool IsEmpty(LinkQueue q); //判断是否为空

bool Visit(int v); //访问元素

/***********BFS算法***********/ 

typedef bool visited[MaxVertexNum]; //标记数组类型声明

bool InitVisited(visited &v) //对标记数组进行初始化
{
    for (int i = 1; i <= g.vexnum ; i++)
    {
        v[i] = false; 
    }
    return true;
}

void BFSTraverse(MGraph g) //对图进行广度优先遍历
{ 
    visited v; //标记数组声明
    LinkQueue q; //顶点队列声明
    InitVisited(v); //初始化标记数组
    InitQueue(q); //顶点队列初始化

    for (int i = 1; i <= g.vexnum; i++)
    {
        if (!v[i]) //对每个顶点进行一次BFS确保所有连通分量都进行了BFS
        {
            BFS(g, q, v, i);
        }
    }
}

void BFS(MGraph g, LinkQueue &q, visited &visitList, int v)
{
    Visit(v); //先访问初始顶点
    visitList[v] = true;

    Enqueue(q, v); //初始顶点入队
    
    while (!IsEmpty(q))
    {
        Dequeue(q, v); //队首顶点出队
        for (int w = FirstNeighbor(g, v); w >= 0; w = NextNeighbor(g, v, w)) //检测与v相邻的顶点
        {
            if (!visitList[w]) //判断之前是否已经访问过
            {
                Enqueue(q, w); //相邻的顶点依次入队
                Visit(w); //访问这些顶点元素
                visitList[w] = true; //更改标记数组
            }
        }
    }
}

int main()
{

}