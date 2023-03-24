#include<stdio.h>
#include<malloc.h>
#define MaxVertexNum 100

/*
    带权的最短路径问题（无权图的最短路径算法在BFS章节）

        1. 单源最短路径问题
            
            Dijkstra算法

                基于贪心策略，类似于Prim最小生成树算法

                对权值有负数的图不适用

            
            思想：

                初始化三个数组：
                    Final[] : 用于标记各顶点是否已找到最短路径
                    Dist[]：  最短路径长度（权值）
                    path[]:   路径上顶点的前驱  

            算法结束后通过path数组可以找到最短路径


        2. 一对顶点间的最短路径

            Floyd算法

                基于动态规划的思想，将问题求解分为多个阶段
              
            思想：

                初始化矩阵A和矩阵path

                矩阵A记录各个顶点之间的最短加权路径
                矩阵path记录各顶点间的中转顶点

                算法结束后通过path数组可以找到最短路径

*/

//邻接矩阵类型的图类型声明
typedef struct
{
    int Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵，边表
    int vexnum, arcnum; //图当前的顶点数和边数/弧数 
} MGraph;

//弗洛伊德核心代码
int A[MaxVertexNum][MaxVertexNum];
int Path[MaxVertexNum][MaxVertexNum];



int Floyd(MGraph g)
{
    //....准备工作，根据图的信息初始化矩阵A和Path

    //....前面的代码太简单捏，懒得写捏

    for (int i = 0; i < g.vexnum; i++)
    {
        for (int j = 0; j < g.vexnum; j++)
        {
            Path[i][j] = -1;
        }
        
    }

    /*
        下面是弗洛伊德算法的核心部分，暴力三层遍历！！时间复杂度为O（|V|^3) ！！！
    */

    for (int k = 0; k < g.vexnum; k++) //考虑以Vk作为中转点，每一轮迭代都添加一个新的中转点，需n-1次
    {
        for (int i = 0; i < g.vexnum; i++) //每一轮迭代都需要遍历整个矩阵进行更新
        {
            for (int j = 0; j < g.vexnum; j++)
            {
                if (A[i][j] > A[i][k] + A[k][j]) //若考虑加入中转顶点后，他的路径比原来的路径要短
                {
                    A[i][j] = A[i][k] + A[k][j]; //更新最短路径长度
                    Path[i][j] = k; //中转顶点
                }   
            }   
        }   
    }
}