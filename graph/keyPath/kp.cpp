#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 100

/*
    关键路径

    AOE网
    
        在带权图中，以顶点表示事件，以有向边表示活动，以边上的权值表示完成该活动
        的开销。称之为用边表示活动的网络，简称AOE网。
        
        AOE网和AOV网都是有向无环图
        
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

