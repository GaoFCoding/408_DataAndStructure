#include<stdio.h>
#include<malloc.h>

/*
    图的最小生成树

        两个算法设计上都采用了贪心的算法思想

        1. Prim
            类似图的最短路径Dijkstra算法
            
            时间复杂度：O（|V|^2）

            适合用于处理边稠密的图

            key:
                BFS

        2. Kruskal
            按权递增次序选择合适的边来构造最小生成树

            时间复杂度：O（|E|*log2|E|）

            适合用于处理顶点多且边稀疏的图

            key：
                堆、查并集
*/