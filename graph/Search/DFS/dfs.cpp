#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 100

/*
    图的深度优先算法

        递归的思想

        和树的深度优先(先根遍历)很类似，不同点是需要增加一个
        visited数组用于记录已经被访问过的节点

        空间复杂度
            
            复杂度来自递归工作栈

            最好空间复杂度为o(1)
            最坏空间复杂度为o(n)

        时间复杂度
            邻接矩阵：O(|v|^2)
            邻接表：O(|v| + |E|)

*/

//邻接矩阵类型的图类型声明
typedef struct
{
    int Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图当前的顶点数和边数/弧数 
} MGraph;

//二叉树类型声明
typedef struct BiTNode
{
    int data;
    struct BitNode *Lchild;
    struct BitNode *Rchild;
} BitNode, *BiTree;


//基本操作声明
int FirstNeighbor(MGraph g, int x); //求图中顶点x的第一个邻接点，若有则返回顶点号，没有则返回-1
int NextNeighbor(MGraph g, int x, int y); //y是x的一个邻近点，返回y的下一个邻接点的顶点号，无则返回-1
bool Visit(int v); //访问顶点

/************树的先根遍历************/

void PreOrder(BiTNode *T)
{
    if (T != NULL)
    {
        Visit(T->data);
        while (/*T还有下一个子树Tn*/)
        {
            PreOrder(T); //先根遍历下一棵子树
        }
    }
}

/************图的深度优先************/
typedef bool VisitList[MaxVertexNum]; //声明一个标记数组类型

bool InitVL(VisitList &vl) //初始化标记数组
{
    for (int i = 1; i <= g.vexnum; i++)
    {
        vl[i] = false;
    }
}

//对图进行深度优先遍历
void DFS(MGraph g, int v)
{
    //先访问第一个顶点
    Visit(v);
    VisitList[v] = true; //标记已访问的顶点

    for (int w = FirstNeighbor(g, v); w > 0; w = NextNeighbor(g, v, w))
    {
        if (!VisitList[w]) //判断是否之前已经被访问
        {
            DFS(g, w); //递归调用
        }       
    }
    
}

void DFSTraverse(MGraph g)
{
    VisitList vl; //声明一个标记数组
    InitVL(vl); //初始化vl数组

    for (int i = 1; i <= g.vexnum; i++)
    {
        if (!VisitList[i])
        {
            DFS(g, i); //对图进行深度优先遍历
        }
    }
}

int main()
{

}