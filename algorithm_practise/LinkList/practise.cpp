#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/*
    1. 递归实现删除不带头节点的单链表L中所有值为x的节点

        注意递归退出条件是遍历到空节点时（空节点是链表的最后一个节点所指向的那个节点）

        需要将满足条件的节点的内容释放，通常借助借助一个指针类型变量指向该节点的内存，再执行free()函数释放内存空间

*/

/*
    测试用例生成函数
*/

void ListMaker(LinkList &L)
{
    int s;

    L = (LNode *)malloc(sizeof(LNode)); //构造头节点

    LNode *rear = L; //尾指针

    printf("make test list:\n");

    scanf("%d",&s);
    while (s != 999)
    {
        LNode* node = (LNode *)malloc(sizeof(LNode));
        node->data = s;

        rear->next = node;
        rear = node;
        scanf("%d",&s);
    }
    
    rear->next = NULL;
}



void DeleteTargetX(LinkList &L, ElemType X)
{
    if (L == NULL)
    {
        return;
    }
    
    if (L->data == X)
    {
        LNode *p = L;
        L = L->next; //L指向下一个节点
        free(p); //删除该节点，释放内存空间

        DeleteTargetX(L, X); //递归下一个节点
    }
    else
    {
        DeleteTargetX(L->next, X); //递归调用
    }
       
}

/*
    2. 在带头节点的单链表L中，删除所有值为X的节点，并释放空间，假设值为X的节点不唯一
*/

//带头节点
void DeleteTargetX2(LinkList &L, ElemType X)
{
    LNode *prev = L; //前驱节点指针
    LNode *cur = L->next; //遍历节点指针

    while (cur != NULL)
    {
        if (cur->data == X)
        {
            LNode *p = cur;
            prev->next = p->next;
            cur = p->next;
            free(p); //释放当前节点内存空间
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

}

/*
    3. 设L为带头节点的单链表，编写算法实现从尾到头反向输出每个节点的值
*/

/*
    算法思想：
        1. 逆置法思想，将链表逆置，然后再顺序输出

        2. 利用栈实现，先按顺序依次入栈，再依次出栈并输出；同样地，用递归也可以实现栈这种算法思想
*/

//1. 逆置法
void ReversePrintElement(LinkList &L)
{
    LinkList p = (LNode *)malloc(sizeof(LNode)); //初始化辅助链表的头节点
    p->next = NULL;

    while (L != NULL)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode)); //申请新插入的节点
        s->data = L->data;
        s->next = p->next;
        p->next = s;
        L = L->next;
    }
    
    p = p->next;
    while (p != NULL) //依次输出逆置后的链表
    {
        printf("%d", p->data);
        p = p->next;
    }

}

//2. 递归
void ReversePrintElement2(LinkList &L)
{
    if (L != NULL)
    {
        ReversePrintElement2(L->next);
    }
    printf("%d", L->data); //递归输出
}

//3.栈的顺序实现
typedef struct {
	LNode* data[MaxSize]; //静态数组存放栈中元素
	int top; //栈顶指针，空的时候为-1，索引范围为[0,maxSize - 1]
} SqStack;


//定义栈的基本操作
void InitStack(SqStack &s){}; //栈初始化
void Push(SqStack &s, LNode *node){}; //入栈
LNode* Pop(SqStack &s){}; //出栈并返回值

void ReversePrintElement3(LinkList &L)
{
    SqStack s; //声明栈
    InitStack(s); //初始化栈

    int count = 0; //记录多少数据入栈
    L = L->next;
    while (L != NULL)
    {
        Push(s,L); //入栈
        count++;
        L = L->next;
    }
    
    for (int i = 0; i < count; i++)
    {
        LNode *p = Pop(s);
        printf("%d", p->data); //出栈并输出
    }

} 

/*
    4. 试编写带头节点的单链表L中删除一个最小值节点的高效算法

    思想：
        遍历链表，每当遇到一个节点的值小于上一个节点时，记录下该节点的前驱

        时间复杂度：O（n）
*/

void DeleteTheMin(LinkList &L)
{
    LNode *minPrev = L; //最小值节点的前驱节点(初始值为头节点)
    LNode *prev = L; //当前遍历的节点的前驱（初始值为头节点）
    int min = L->next->data; //当前元素的最小值(初始值为第一个元素的值)

    L = L->next; //工作节点，从第一个节点开始
    while (L != NULL)
    {
        if (L->data < min)
        {
            min = L->data;
            minPrev = prev;
        }
        
        prev = L;
        L = L->next;
    }
    
    LNode *p = minPrev->next;
    minPrev->next = p->next;
    free(p); //删除最小节点，并释放内存空间
}

/*
    5. 编写算法将带头节点的单链表就地逆置，即时间复杂度为O（1）

    算法思想：
        头插法，将头节点摘下，利用头插法重新插入到头节点后面，实现逆置
*/

void ReverseLinkList(LinkList &L)
{
    LNode *p = L->next;
    L->next = NULL; //把头节点摘下

    while (p != NULL)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = p->data;
        s->next = L->next;
        L->next = s;

        p = p->next;
    }
}

//改进,不需要创建一个新的节点
void ReverseLinkList2(LinkList &L)
{
    LNode *p, *r; //p为工作节点，r为p的后缀，防止断链

    L->next = NULL;

    while (p != NULL)
    {
        r = p->next; //记录p节点的后缀
        p->next = L->next;
        L->next = p;

        p = r;
    }
    
}

/*
    6. 在一个带头节点的单链表L，设计一个算法使其元素递增有序
*/

/*
    1. 暴力法, 将链表中的元素复制到数组中，对数组进行排序，再放回到链表中，排序使用快速排序

    时间复杂度：O（nlog2n+n+n） = O(nlog2n)

    空间复杂度：O（n）

    空间换时间
*/

//声明快速排序函数

int GetPosition(int list[], int low, int high)
{
    int pivotpos = list[low];
    while (low < high) //low == high时结束
    {
        while (low < high && list[high] >= pivotpos)
        {
            high--;
        }
        list[low] = list[high];
        while (low < high && list[low] <= pivotpos)
        {
            low++;
        }
        list[high] = list[low];
    }
    
    list[low] = pivotpos; //每一次划分确定一个元素的最终位置
    return low; 
}

void QuickSort(int list[], int low, int high)
{
    if (low < high)
    {
        int position = GetPosition(list, low, high);
        QuickSort(list, low, position-1);   //向左划分
        QuickSort(list, position+1, high);  //向右划分
    }
}

void SortlinkList(LinkList &L)
{   
    int *temp = (int *)malloc(sizeof(int)*MaxSize);
    int i = 0;
    LNode *p = L->next; //工作指针
    
    while (p != NULL) //将链表中的数据复制到数组中
    {
        temp[i] = p->data;
        i++;
        p = p->next;
    }
    
    QuickSort(temp, 0, i-1); //快排

    p = L->next; //重置p指针
    for (int j = 0; j <= i-1; j++)  //将暂存数组中已排序的元素复制回链表中
    {
        p->data = temp[j];
        p = p->next;
    }

    free(temp); //释放暂存数组的内存空间
}

/*
    2. 基于直接插入法排序思想，采用直接插入排序的思想，先构造只含有一个数据节点的有序单链表，然后依次扫描单链表中剩下的节点*p，
    在有序表中通过比较查找插入*p的前驱节点*pre，然后将*p插入到*pre之后

    时间复杂度：O(n^2)

    空间复杂度：O(1)
*/
void SortlinkList2(LinkList &L)
{
    LNode *pre = L;
    LNode *p = L->next->next; //从第二个节点开始
    LNode *r; //实现对单链表的遍历

    L->next->next = NULL; //构造只含一个数据节点的有序单链表

    while (p != NULL) //扫描单链表中剩下的节点
    {
        pre = L; //在插入时都从头开始遍历含头节点L的单链表寻找插入的位置

        r = p->next;
        
        while (pre->next != NULL && pre->next->data < p->data)
        {
            pre = pre->next;
        }
        
        p->next = pre->next; 
        pre->next = p; //插入pre节点后面

        p = r; //扫描原链表中剩下的节点
    }
}

/*
    7. 设在一个带表头节点的单链表中所有元素节点无序，删除表中所有介于给定的两个值之间元素的元素（若存在）

    算法思想：
        直接遍历单链表，若遇到满足条件的节点则删除

    时间复杂度：O(n)

    空间复杂度：O(1)

*/

void DeleteNodeBetweenLH(LinkList &L, int low, int high)
{
    LNode *p = L->next, *pre = L;
    LNode *r;

    while (p != NULL)
    {
        r = p->next;
        if (p->data > low && p->data < high)
        {
            pre->next = p->next;
            // free(p); //删除满足条件的节点

            p = r;
            continue;
        }
        
        pre = pre->next;
        p = r;
    }
    
}


/*
    8. 给定两个单链表，编写算法找出两个链表的公共节点(带头节点)

*/

/*
    1. 暴力法

        遍历第一个链表，每遍历一个元素，遍历整个第二个链表，找到所有可能的公共节点
        
        时间复杂度：O（n^2）

        空间复杂度：O（1）
*/

LinkList FindCommonNode(LinkList &L1, LinkList &L2)
{
    LNode *p1 = L1->next;
    LNode *p2 = L2->next; //工作指针
    LinkList res = (LNode *)malloc(sizeof(LNode)); //返回带头节点的链表
    res->next = NULL;


    while (p1 != NULL)
    {
        p2 = L2->next;
        while (p2 != NULL)
        {
            if (p1 == p2) //p1, p2指向同一个节点，即公共节点
            {
                LNode *s = (LNode *)malloc(sizeof(LNode));
                s->data = p1->data;

                s->next = res->next; //头插法
                res->next = s;
            }
            p2 = p2->next;
        }
        
        p1 = p1->next;
    }

    return res;
}

/*
    方法2：
        链表对齐思想。
        分别遍历两个链表得到他们的长度，并求出两个长度的差，在长度较长的链表上先遍历长度之差个节点后，再同步遍历两个链表，
        直到找到相同的节点

        时间复杂度:O(n)

        空间复杂度：O（1）
*/

int Len(LinkList list) //求链表的长度
{
    LNode *p = list;
    int len = 0;

    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    
    return len;
}

LinkList FindCommonNode2(LinkList &L1, LinkList &L2)
{
    LNode *p1 = L1->next;
    LNode *p2 = L2->next; //工作节点
    int len1 = Len(L1), len2 = Len(L2);
    int dis; //表长差

    //对齐
    if (len1 > len2) //L1比L2长
    {
        dis = len1 - len2;
        while (dis)
        {
            p1 = p1->next;
            dis--;
        }
    }

    if (len1 < len2)
    {
        dis = len2 - len1;
        while (dis)
        {
            p2 = p2->next;
            dis--;
        }
    }

    while (p1 != NULL) // or p2 != null
    {
        if (p1 == p2)
        {
            return p1;
        }

        p1 = p1->next;
        p2 = p2->next; //同步遍历
    }
    
    return NULL; //找不到公共节点链

}



/*
    9. 给定一个带表头的单链表，设head为头指针，节点结构为(data,next)，data为整型元素，next为指针
        按递增次序输出单链表中各节点的数据元素，并释放节点所占的存储空间，要求是不使用辅助数组

        算法思想：
            采用直接插入法的思想，将单链表按递增排序，再遍历单链表输出

        时间复杂度：O（n^2） 同直接插入排序

        空间复杂度：O（1）
*/

void LinkListOrderByInc(LinkList &L)
{
    LNode *p = L->next->next; //待排序链表
    LNode *r;
    L->next->next = NULL; //已排序链表
    LNode *pre;

    while (p != NULL)
    {
        pre = L; //从已排序的链表第一个元素开始遍历
        r = p->next;
        while (pre->next != NULL && pre->next->data < p->data)
        {
            pre = pre->next;
        }
        
        p->next = pre->next; //插入到已排序链表中（pre节点后）
        pre->next = p;

        p = r;
    }
    
    LNode *cur = L->next; //此时L已排好序
    while (cur != NULL)
    {
        r = cur->next;
        printf(" %d ",cur->data);
        free(cur); //释放节点所占空间
        cur = r;
    }

}

/*
    10. 将一个带头节点的单链表A分解为两个带头节点的单链表A和B，使得A中含有原表中序号为奇数的元素
    ，而B表中含有原表中序号为偶数的元素，且保持相对顺序不变

    算法思想：
        遍历整个A链表，当遍历到元素为偶数的节点时，从A链表中摘下该节点并利用尾插法插入到B表

    时间复杂度：O（n）

    空间复杂度：O（1）
*/
void SplitLists(LinkList &A, LinkList &B)
{
    LNode *rearb; //B表的尾指针
    LNode *pre = A; //A链表遍历节点的前驱
    LNode *r; //A链表遍历指针
    LNode *p = A->next; //A链表工作指针

    //初始化B链表
    B = (LNode *)malloc(sizeof(LNode));
    rearb = B;

    while (p != NULL)
    {
        r = p->next;
        if (p->data%2 == 0) //若元素为偶数，则摘下来放到B链表
        {
            pre->next = p->next; //前驱节点指向p的后继
            
            rearb->next = p; //p节点尾插法插入到B链表
            rearb = p; //更新尾指针
            
            p = r;
            continue;
        }
        pre = pre->next;
        p = r;
    }
    
    rearb->next = NULL;
}


/*
    11. 设C = {a1,b1,a2,b2,...,an,bn}为线性表，采用头节点的单链表存放，
    设计一个就地算法，将其拆解为两个线性表，使得A = {a1,a2,a3,...,an}, B = {bn,...,b2,b1}

    算法设计：
        奇数项目为a,偶数项为b,遍历链表C,将所有的偶数项从C中摘下，并使用头插法插入到
        B链表中

    时间复杂度：O（n）

    空间复杂度：O（1)
*/

void SplitTheList(LinkList &A, LinkList &B)
{   
    LNode *p = A->next; //工作指针
    LNode *r;
    LNode *pre = A; //工作指针所指向的节点的前驱节点
    int count = 1; //记录当前遍历到的节点是奇数还是偶数

    //初始化B链表
    B = (LNode *)malloc(sizeof(LNode));
    B->next = NULL;

    while (p != NULL)
    {
        r = p->next;
        if (count%2 == 0) //若为偶数项，则摘下插入到B中
        {
            pre->next = p->next;

            p->next = B->next; //头插法
            B->next = p; 

            p = r;
            count++;
            continue;
        }

        pre = pre->next;
        p = r;
        count++;
    }

}

/*
    12. 在一个递增有序的线性表中，有数值相同的元素存在，若存储方式为单链表，
    设计算法去掉数值相同的元素，使表中不再有重复的元素，例如(7,10,10,21,30,42,42,51,70)
    将变为(7,10,21,30,42,51,70)
*/

/*
    1. 暴力法

    对链表中的每个元素，都遍历一遍他后面的所有节点，若有相同的则删除该节点

    时间复杂度：O（n^2）
    空间复杂度：O(1)
*/
void DeleteTheSameNode(LinkList &L)
{
    LNode *p = L->next; //工作指针
    LNode *pre; //t的前驱节点
    LNode *t; //工作指针，指向p之后的节点
    LNode *r;

    while (p != NULL)
    {
        t = p->next;
        pre = p;
        while (t != NULL) //遍历p的后序节点
        {
            r = t->next;
            if (t->data == p->data) //若有相同，则删除该节点
            {
                pre->next = t->next;
                free(t);
                t = r;
                continue;
            }
            pre = pre->next;
            t = r;
        }
        p = p->next;
    }
}

/*
    13. 假设两个按元素值递增次序排列的线性表，均以单链表形式存储，请编写算法将
    这两个单链表归并为一个按元素值递减次序排列的单链表，并要求利用原来两个单链表
    的节点存放归并后的单链表。
*/

/*
    算法设计：
        采用直接插入法，将其中一个链表按照递增次序归并到另一个链表，再对归并后的链表逆置

    时间复杂度：O（n^2）

    空间复杂度：O(1)
*/
void MergeAndDESC(LinkList A, LinkList B) //将B链表合并到A链表，A和B均有头节点
{
    LNode *pre = A;
    LNode *p = B->next; //B表的工作节点
    LNode *r;

    while (p != NULL)
    {
        r = p->next;
        while (pre->next != NULL && pre->next->data < p->data) //若pre后的节点元素大于p指针的元素，则将p从B中摘下插入到pre后面
        {
            pre = pre->next;
        }
        
        p->next = pre->next;
        pre->next = p;

        p = r;
    }
    
    //逆置链表归并后的链表A
    p = A->next; //工作节点指向A的第一个元素
    A->next = NULL; //摘下头节点

    while (p != NULL)
    {
        r = p->next;

        p->next = A->next; //头插法实现逆置
        A->next = p;
        
        p = r;
    }

}

/*
    14. 设A和B是两个单链表，其中元素递增有序，设计一个算法从A和B中的公共元素产生单链表C，要求
    不破坏A和B的节点

    算法设计：
        （参考王道书）表A,B都有序，从第一个元素起依次比较A、B两表的元素，若元素值不等，则值小的指针往后移，若元素值相等
        则创建一个值等于两节点的元素值的新节点，使用尾插法插入到新的链表中，并将两个原表指针后移一位，直到其中一个链表遍历到表尾

    时间复杂度：O（n）

    空间复杂度：O (1)
*/

LinkList CreateListC(LinkList A, LinkList B)
{
    LNode *pa = A->next, *pb = B->next;
    LNode *rear; //C表的尾指针

    LinkList C = (LNode *)malloc(sizeof(LNode));
    rear = C;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            pb = pb->next;
        }
        else
        {
            LNode *s = (LNode *)malloc(sizeof(LNode));
            s->data = pa->data;
            rear->next = s;
            rear = s; //更新尾指针

            pa = pa->next;
            pb = pb->next;
        }
        
    }

    rear->next = NULL;

    return C;
     
}

/*
    15. 已知两个链表A和B分别表示两个集合，其元素递增排序。编制函数，求A和B的交集，并存放在A链表中

    算法设计：

        暴力法：
            遍历A链表，每遍历一个元素便完整地遍历B链表，若能找到B中一个元素与A中当前元素相同，说明是交集，保留并遍历下一个
            ，若找不到，则说明不是交集元素，从A中删除。并且在遍历A的同时删除A中重复的元素。

    时间复杂度：O（n^2）

    空间复杂度：O(1)
*/

void GetSameEelements(LinkList &A, LinkList &B)
{
    LNode *p = A->next; //工作指针
    LNode *pb = B->next;
    LNode *pre = A; //p的前驱
    LNode *r;

    while (p != NULL)
    {
        r = p->next;
        if (p->data == pre->data) //若当前p指向的节点元素与前一个节点元素相同，则删除该节点
        {
            pre->next = p->next;
            free(p);

            p = r;
            continue;
        }
        
        pb = B->next;
        while (pb != NULL && pb->data != p->data)
        {
            pb = pb->next;
        }

        if (pb == NULL) //未找到与A中当前节点相同的元素，则删除A中的该元素
        {
            pre->next = p->next;
            free(p);
            
            p = r;
            continue;
        }
        
        pre = pre->next;
        p = r;
    }

}

/*
    解法2:
        设计思想：

        时间复杂度：

        空间复杂度：

*/



/*
    16. 两个整数序列A = a1,a2,a3,...am和B = b1,b2,...bn已经存入两个单链表中，设计一个算法，判断
    序列B是否是序列A的连续子序列
*/

/*
    算法设计：

        暴力法：
            遍历A，每当遇到与B中第一个元素值相同的节点时，开始逐一对比A和B当前位置。若能完全匹配，则返回true，
            若不能完全匹配，则A继续往后遍历，重复上面操作。
            
    时间复杂度：O(n^2)

    空间复杂度：O(1)

*/

bool CompareA_B(LinkList &A, LinkList &B)
{
    LNode *pa = A->next;
    LNode *pb = B->next; //AB工作节点
    LNode *temp;
    int s = B->next->data; //存储B的第一个元素


    while (pa != NULL)
    {
        if (pa->data != s) 
        {
            pa = pa->next;
        }
        else //匹配上第一个元素
        {
            temp = pa;
            while (temp != NULL && pb != NULL && temp->data == pb->data) //逐位比较
            {
                temp = temp->next;
                pb = pb->next;
            }

            if (pb == NULL) //说明完全匹配上了，为子序列
            {
                return true;
            }    
        }
    }

    return false;
}

/*
    22. 【2009全国统考真题】

    已知一带头节点的单链表，设计一个算法，查找链表中倒数第k个位置上的结点，若查找成功，算法输出该节点的data值，并返回1，否则返回0

    算法设计：
        1. 设置两个指针p1,p2和一个计数器count，p1先遍历单链表，p1每遍历一次就count++，当count == k 时，p2开始跟p1同步遍历，当p1遍历结束时，p2的位置就是倒数
        第K个位置，输出data值，返回1，若count的值小于k，说明不存在倒数第k个节点，返回0；

    时间复杂度：O（n）

    空间复杂度：O(1)
    
*/
bool FindLastKElement(LinkList &L, int k)
{
    LNode *p1 = L->next;
    LNode *p2 = L->next;
    int count = 0;

    while (p1 != NULL)
    {
        p1 = p1->next;

        if (count != k)
        {
            count++;
        }
        else
        {
            p2 = p2->next;
        }
    }

    if (count == k) //说明不存在倒数第K个节点（链表不够长）
    {
        printf("number %d , data is %d ", k, p2->data);
        return true;
    }

    printf(" %d not found", k);
    return false;
   
}

/*
    23. 【2012统考真题】假定采用带头节点的单链表保存单词，当两个单词有相同的后缀时，可共享
    相同的后缀存储空间，设str1和str2分别指向两个单词所在单链表的头节点，设计一个算法，找出
    str1和str2所指向的两个链表共同后缀的起始位置。
*/

/*
    解法1.
        暴力法，本质上是找出公共节点的起始位置，遍历链表Str1，每遍历一个元素就遍历一遍Str2，直到找到共用存储空间的节点
        （指针指向同一地址）

        时间复杂度：
            O（n^2）
        空间复杂度：
            O (1)
*/
typedef struct Node
{
    char data;
    struct Node *next;
} SNode;


SNode* FindIndexOfShareSpace(SNode *str1, SNode* str2)
{   
    SNode *p1 = str1->next;
    SNode *p2 = str2->next;

    while (p1 != NULL)
    {
        while (p2 != NULL)
        {
            if (p1 == p2) //若为公共节点
            {
                return p1;
            }
            
            p2 = p2->next;
        }

        p1 = p1->next;
        
    }
    
    return NULL; //若找不到则返回Null
}

/*
    解法二：
        双指针法，用指针p、q分别扫描str1和str2，用p,q分别扫描str1,str2，当p,q指向同一地址时，即找到了共同后缀的起始位置

        1. 分别求出str1和str2所指向的两个链表的长度m和n
        2. 将两个链表尾对齐
        3. 反复将指针p和q同步向后移动，当p，q指向同一位置时停止，即为共同后缀的起始位置，算法结束
*/

int Length(SNode *list) //求链表的长度
{
    SNode *p = list;
    int len = 0;

    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    
    return len;
}

SNode* Find_addr(SNode *L1, SNode *L2)
{
    SNode *p1 = L1->next;
    SNode *p2 = L2->next;
    int len1 = Length(L1), len2 = Length(L2);
    int dis;

    if (len1 > len2)
    {
        dis = len1 - len2;
        while (dis)
        {
            p1 = p1->next;
        }
        dis--;
    }

    if (len2 > len1)
    {
        dis = len2 - len1;
        while (dis)
        {
            p2 = p2->next;   
        }
        dis--;
    } //完成对齐
    
    while (p1 != NULL)
    {
        if (p1 == p2)
        {
            return p1;
        }
    }
    
    return NULL; //找不到公共后缀节点

}

/*
    24. 【2015统考真题】
    用单链表保存m个整数，节点的结构为[data][link]，且[data]<=n (n为正整数)，现要求设计一个时间复杂度尽可能高效的算法，对于
    链表中data的绝对值相等的节点，仅保留第一次出现的节点而删除其余绝对值相等的节点。例如：
        给定的单链表的head如下：
            head ——— 21 ———— -15 ———— -15 ———— -7 ———— 15
        则删除节点后的head为：
            head ——— 21 ———— -15 ———— -7

*/

/*
    1. 暴力法
        遍历链表中的每一个节点，每遍历一个节点，就遍历他所有的后序节点，将所有与其绝对值相同的节点都删除

    时间复杂度：O（n^2）

    空间复杂度：O（1）
*/

int abs(int num)
{
    if (num < 0)
    {
        num = -num;
    }
    return num;
}

void DeleteAbsSameElem(LinkList &list)
{
    LNode *pre; //cur的前驱节点
    LNode *p = list->next; //工作节点
    LNode *cur; //遍历p之后的节点
    LNode *r;

    while (p != NULL)
    {
        cur = p->next;
        pre = p;
        while (cur != NULL)
        {
            r = cur->next;
            if (abs(cur->data) == abs(p->data)) //后序节点存在与p的绝对值相同的元素则删除
            {
                pre->next = cur->next;
                free(cur);
                cur = r;
                continue;
            }

            pre = pre->next;
            cur = r;
        }
        
        p = p->next;
    }    
}

/*
    解法2.
        空间换时间，使用辅助数组记录链表中已出现的数值，从而只需对链表进行一趟扫描
        |data|<=n ，辅助数组大小为n+1(1到n，包括n)，各元素初始值为0，依次扫描链表中的每一个节点，
        同时检测q[|data|]的值，若为0则保留该节点，并令q[|data|]=1，否则将该节点从链表中删除。

    时间复杂度：O（n）

    空间复杂度：O(n) //需要辅助数组
*/
void DeleteAbsSameElem2(LinkList &list, int n) //n为辅助数组的长度
{
    LNode *p = list->next; //工作指针
    LNode *pre = list; //前驱节点指针
    LNode *r;

    int *record = (int *)malloc(sizeof(int)*(n+1)); //初始化一个长度为n+1的数组用于存放data的记录
    for (int i = 1; i < n+1; i++) //只需要后n个
    {
        record[i] = 0;
    }
    
    while (p != NULL)
    {
        r = p->next;
        if (record[abs(p->data)]) //若存在，则删除
        {
            pre->next = r;
            free(p);
            p = r;
            continue;
        }

        record[abs(p->data)] = 1;
        pre = pre->next;
        p = p->next;
    }

}

/*
    25. 【2019】统考真题

    设线性表L = (a1,a2,a3,...an-2,an-1,an)采用带头节点的单链表保存，设计一个空间复杂度为O（1）且时间复杂度尽可能高的算法，
    重新排列L中的各个节点，得到线性表L' = (a1,an,a2,an-1,a3,an-2,...)

    算法设计：
        先找到链表中中间节点，将中间结点的后半部分逆置，再其交替地插入到前半部分
    时间复杂度：O（n）

    空间复杂度：O（1）
*/

LNode* FindMidNode(LinkList &list) //寻找链表中间节点（快慢指针）
{
    LNode *p1 = list->next; //快指针
    LNode *p2 = list->next; //慢指针
    int count = 0; //tag

    while (p1 != NULL)
    {
        if (count == 2)
        {
            p2 = p2->next;
            count = 0;
        }

        count++;
        p1 = p1->next;
    }
    
    return p2;
}

void PartlyReverse(LinkList &list)
{
    LNode *p1 = list->next;
    LNode *p2 = FindMidNode(list); //p2为中间节点指针
    LNode *r;

    //逆置后半部分
    LNode *cur = p2->next;
    p2->next = NULL; //保证逆置后的后半段链表尾为NULL
    while (cur != NULL) //实现后半部分的逆置
    {
        r = cur->next;
        cur->next = p2->next;
        p2->next = cur;
        cur = r;
    }

    //交替地插入到前半部分
    cur = p2->next; //cur指向后半段的第一个数据节点
    p2->next = NULL; //保证插入完成后链表尾部为NULL
    while (cur != NULL)
    {
        r = cur->next;
        cur->next = p1->next;
        p1->next = cur; //完成插入

        p1 = cur->next; //指向下一个插入点
        
        cur = r;
    }
}

/*
    总结要点：
        1. 快慢指针法求链表的中间节点
        2. 头插法逆置带头节点的链表
*/

int main(void)
{
    LinkList test;
    LNode *p;

    while (1)
    {
        ListMaker(test);
        // DeleteAbsSameElem2(test,10);
        PartlyReverse(test);
        
        p = test->next;
        while (p != NULL)
        {
            printf(" %d ",p->data);
            p = p->next;
        }
    }
}