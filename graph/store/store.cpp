#include<stdio.h>
#define MaxVertexNum 10

/*
    无向图的存储结构
*/

/*
    1. 邻接矩阵法
        适合存储稠密图，空间复杂度很高，O（n^2）
*/
typedef struct 
{
    char Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图当前的顶点数和边数/弧数 
} MGraph;

//查找无向图一个顶点的度, 时间复杂度为O（n）,n为顶点数，只需要查找该顶点对应的某行或者某列的非零点的个数
int FindDu(MGraph G, char vex)
{
    int i = 0;
    int duNum = 0; //记录一个顶点的度数
    while (G.Vex[i] != vex && i < G.vexnum)
    {
        i++;
    }
    if (i >= G.vexnum)
    {
        return false;
    }
    for (int j = 0; j < G.vexnum; j++)
    {
        if (G.Edge[i][j] > 0)
        {
            duNum++;
        }
    }
    return duNum;    
}  

//若查找的是有向图的一个顶点的度，则需要遍历该顶点号所在的行和列，并且把非零个数相加，时间复杂度也为O（n）
int FindDu_direct(MGraph G, char vex)
{
    int i = 0;
    int induNum = 0; //记录一个顶点入度数
    int outduNum = 0; //记录一个顶点出度数
    while (G.Vex[i] != vex && i < G.vexnum)
    {
        i++;
    }
    if (i >= G.vexnum)
    {
        return false;
    }
    for (int j = 0; j < G.vexnum; j++) //遍历行，求入度
    {
        if (G.Edge[i][j] > 0)
        {
            induNum++;
        }
        if (G.Edge[j][i] > 0)
        {
            outduNum++;
        }
        
    }
    return induNum + outduNum;
}

/*
    2. 邻接表法

        顺序 + 链式存储

    与树的孩子表示法存储结构类似，可以进行比较学习
*/
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



int main()
{

}