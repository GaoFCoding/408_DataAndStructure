#include<stdio.h>
#include<malloc.h>
#define MAXSIZE 10

typedef int ElemType;

typedef struct
{
    ElemType *Data;
    int Length, MaxSize;
} SqList;

//初始化线性表
void InitSqList(SqList &sq)
{
    sq.Length = 0; //初始化长度为0
    sq.MaxSize = MAXSIZE;
    sq.Data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType)); //分配内存
}

/*
    P17 .01
    从顺序表中删除具有最小值的元素，并由函数返回被删除元素的值，空出的位置由最后一个元素填补，若顺序表为空，
    则显示出错信息并退出运行
*/
bool DeleteMinElem(SqList &sq, ElemType &res)
{
    //判断顺序表是否为空
    if (sq.Length == 0)
    {
        printf("顺序表为空，无法进行操作！");
        return false;
    }
    
    int i = 0; //记录最小元素的下标
    for (int j = 0; j < sq.Length; j++)
    {
        if (sq.Data[j] < sq.Data[i])
        {
            i = j; //更新最小元素的下标
        }
    }
    
    res = sq.Data[i];
    sq.Data[i] = sq.Data[sq.Length - 1]; //删除最小值元素并且返回被删除元素的值，空出的位置由最后一个元素填补
    sq.Length--;

    return true;
}

/*
    p17 .02
    设计一个高效算法，将顺序表所有元素逆置，要求算法的空间复杂度为O（1）
*/
bool ReverseSqList(SqList &sq)
{
    int l = 0, r = sq.Length-1; //声明左右指针
    while (l <= r)
    {
        int temp;
        temp = sq.Data[l];
        sq.Data[l] = sq.Data[r]; //左右指针所指数据交换
        sq.Data[r] = temp;

        l++; //左指针向右移动
        r--; //右边指针向左移动
    }
    
    return true;
}

/*
    p17 .03
    对长度为n的顺序表L，编写一个时间复杂度为O(n),空间复杂度为O(1)的算法，该算法删除线性表中所有值为
    x的数据元素
*/
bool DeleteElem(SqList &sq, int i) //删除指定元素的基本操作
{
    for (int j = i+1; j < sq.Length ; j++)
    {
        sq.Data[j-1] = sq.Data[j];
    }
    sq.Length--;
    return true;
}

bool DeleteTargetElem(SqList &sq, ElemType target)
{
    for (int i = 0; i < sq.Length; i++)
    {
        if (target == sq.Data[i])
        {
            DeleteElem(sq, i); //删除该元素
        }
    }
    return true;
}

//以上方法的时间复杂度已经超过O(n)，是最基本的方法

//快慢指针法如下
bool DeleteElem2(SqList &sq, ElemType target)
{
    int f=0, s=0; //定义快慢指针
    for (f = 0; f < sq.Length; f++)
    {
        if (sq.Data[f] != target) //如果不相同
        {
            sq.Data[s++] = sq.Data[f];
        }
    }
    sq.Length = s; //更新顺序表的长度
    
    return true;
}


/*
    从有序顺序表中删除其值在给定值s与t之间(s < t)的所有元素，若s或t不合理或顺序表为空则显示错误信息并退出运行
*/

bool DeleteElemsBetweenST1(SqList &sq, ElemType s, ElemType t)
{

    int fast=0;
    int slow=0; //定义快慢指针

    if (s >= t)
    {
        printf("s,t输入不合理");
        return false;
    }
    
    if (sq.Length == 0)
    {
        printf("顺序表为空");
        return false;
    }

    for (fast = 0; fast < sq.Length; fast++)
    {
        if (sq.Data[fast] <= s || sq.Data[fast] >= t) //删除s与t之间（不包括s，t本身）的所有元素
        {
            sq.Data[slow++] = sq.Data[fast];
        }
    }
    
    sq.Length = slow; //更新数组长度

    return true;
}

/*
    5.从顺序表中删除值在s与t之间的所有元素（包含s和t，要求s<t），若s或t不合理或顺序表为空则显示错误信息并退出运行
*/
bool DeleteElemsBetweenST2(SqList &sq, ElemType s, ElemType t)
{

    int fast=0;
    int slow=0; //定义快慢指针

    if (s >= t)
    {
        printf("s,t输入不合理");
        return false;
    }
    
    if (sq.Length == 0)
    {
        printf("顺序表为空");
        return false;
    }

    for (fast = 0; fast < sq.Length; fast++)
    {
        if (sq.Data[fast] < s || sq.Data[fast] > t) //删除s与t之间（包括s，t本身）的所有元素
        {
            sq.Data[slow++] = sq.Data[fast];
        }
    }
    
    sq.Length = s; //更新数组长度

    return true;
}

/*
    6. 从有序顺序表中删除所有值重复的元素，使表中的所有元素的值均不相同(力扣原题)
*/

bool DeleteSameElems(SqList &sq)
{
    int f=0, s=0; //定义快慢指针
    
    for (f = 0; f < sq.Length; f++)
    {
        if (sq.Data[f] != sq.Data[s])
        {
            sq.Data[++s] = sq.Data[f];
        }
    }

    sq.Length = s; //更新数组长度

    return true;
}

/*
    7. 将两个有序顺序表合并成一个新的有序顺序表，并由函数返回结果顺序表（力扣原题）
*/

SqList MergeSqList(SqList s1, SqList s2)
{
    SqList resList; //初始化一个线性表

    resList.Data = (ElemType *)malloc(sizeof(ElemType)*MAXSIZE); //为线性表的数组分配内存空间

    resList.Length = s1.Length + s2.Length;

    resList.MaxSize = MAXSIZE;

    int p1=0, p2=0; //定义两个指针分别指向s1和s2
    int t=0; //指向resList的指针

    while (p1 < s1.Length && p2 < s2.Length)
    {
        if (s1.Data[p1] <= s2.Data[p2])
        {
            resList.Data[t++] = s1.Data[p1++]; //把小的放入res表
        }
        else
        {
            resList.Data[t++] = s2.Data[p2++]; //把小的放入res表
        }
    }
    
    while (p1 < s1.Length) //添加剩余部分
    {
        resList.Data[t++] = s1.Data[p1++]; 
    }

    while (p2 < s2.Length) //添加剩余部分
    {
        resList.Data[t++] = s2.Data[p2++];
    }
    
    return resList;
    
}


/*
    已知在一维数组A[m+n]中，依次放入两个线性表，编写一个函数，将数组中两个顺序表的位置互换
*/


/*
    暴力解法如下：
        时间复杂度O（3n）
*/
bool ExchangeTwoLists(SqList &sq, int m, int n)
{
    ElemType *temp = (ElemType *)malloc(sizeof(ElemType)*sq.MaxSize); //定义一个暂存数组
    
    int p = 0; //暂存数组的指针
    int t = 0; //指向原数组的指针

    for (int i = 0; i < m; i++) //把前m个元素暂存
    {
        temp[p++] = sq.Data[i];
    }
    
    for (int j = m; j < m+n; j++) //把后面的元素放到前面
    {
        sq.Data[t++] = sq.Data[j];
    }
    
    //把暂存数组中的元素加入到原数组后面
    for (int i = 0; i < p; i++)
    {
        sq.Data[t++] = temp[i];
    }

    return true;
}

//解法二：逆置法
/*
    思想：
        对于数组A：{a1,a2,a3...an,b1,b2,b3,b4...bn}

        先整体逆置：
            {bn,bn-1...b1,an-1,an-2,...a1}

        再对两部分局部逆置
            {b1,b2,b3,b4...bn,a1,a2,a3...an}
*/

//逆置算法
bool Reverse(SqList &sq, int low, int high)
{
    ElemType temp;
    if (low > high || high >= sq.Length)
    {
        return false;
    }
    

    while (low <= high)
    {
        temp = sq.Data[low]; //首尾指针所指元素互换
        sq.Data[low] = sq.Data[high];
        sq.Data[high] = temp;

        low++;
        high--;
    }
    return true;
}

//主函数
bool ExchangeTwoList(SqList &sq, int m, int n)
{
    Reverse(sq,0,sq.Length-1); //整体逆置
    Reverse(sq,0,n-1); //左边逆置
    Reverse(sq,n,m+n-1); //右边逆置

    return true;
}

/*
    9. 线性表中元素递增有序，按顺序存储在计算机内，设计一个算法，用最少时间在表中查找数值为x的元素，
    若找到则与后继元素位置交换，找不到则插入表中使表中元素仍递增
*/

//折半查找

bool FindTargetElem(SqList &sq, ElemType target)
{
    int l = 0, r = sq.Length-1; //定义左右指针
    int mid;

    while (l <= r)
    {
        mid = (l + r)/2;
        if (sq.Data[mid] == target) //找到目标元素，并保证后继元素存在
        {
            if (mid != sq.Length-1)
            {
                int temp = sq.Data[mid]; //交换
                sq.Data[mid] = sq.Data[mid+1];
                sq.Data[mid+1] = temp;
                return true;
            }
            else
            {
                printf("目标元素无后继");
                return false;
            }

        }
        else if (sq.Data[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    //l即为要插入的位置
    for (int i = sq.Length-1; i >= l; i--) //左移+插入元素
    {
        sq.Data[i] = sq.Data[i-1];
    }
    sq.Data[l-1] = target; //插入数据

    return true;
}

/*
    10. 2010统考真题
    
        设将n（n>1）个整数存放在一维数组R中，设计一个在时间和空间两方面都尽可能高的算法，
        将R中保存的序列循环左移p（0<p<n）位
*/

/*
    算法设计思想:
        1. 逆置法
            对于数组R：{X0,X2,X3,X4....Xn-1}
            先将其整体逆置:{Xn-1,Xn-2,Xn-3,....X0}
            再对其前面部分的n-p个元素进行逆置
            再对后面的p个元素进行逆置
            共进行三次逆置

        2. 时间空间复杂度分析：
            空间复杂度：O（1）
            时间复杂度：O（n）
*/

bool Reverse(ElemType R[], int low, int high)
{
    if (low > high)
    {
        return false;
    }
    
    ElemType temp;
    while (low <= high)
    {
        temp = R[low]; //exchange
        R[low] = R[high];
        R[high] = temp;

        low++;
        high--;
    }
    return true;
}

void LeftShift(ElemType R[],int length, int p) //左移p位,数组长为length
{
    Reverse(R, 0, length-1); //整体逆置
    Reverse(R, 0, length-p-1); //右边逆置
    Reverse(R, length-p, length-1); //左边逆置
}

/*
    11. （2013统考真题）
     一个长度为L的升序序列S，处在第[L/2]（向上取整）位置的数称为S的中位数。例如，
     若序列S1 = {11,13,15,17,19}，则S1的中位数为15，两个序列的中位数是含他们所有元素的升序序列的中位数，
     例如若s2 = {2,4,6,8,20}，则s1和s2的中位数是11，现在两个等长升序序列A和B，试设计一个在时间和空间复杂度两方面
     都尽可能高效的算法，找出两个序列A和B的中位数。
*/
/*
    算法设计思想：
        将两个数组合并成一个升序的数组，再通过该升序数组求他的中位数。

    时空复杂度：
        时间复杂度：O(n)
        空间复杂度：O(n)
*/

//暴力解法如下，需要分配一个暂存数组，空间复杂度O（n）

void GetMiddleElem(ElemType s1[], ElemType s2[], int l1, int l2, ElemType &res) //l1是s1的长度，l2是s2的长度
{
    ElemType* temp = (ElemType*)malloc(sizeof(ElemType)*(l1+l2)); //定义一个暂存数组

    int p1=0, p2=0; //指向p1和p2的指针
    int t=0; //指向暂存数组的指针

    while (p1 <= l1-1 && p2 <= l2-1)
    {
        if (s1[p1] <= s2[p2])
        {
            temp[t++] = s1[p1++]; 
        }
        else
        {
            temp[t++] = s2[p2++];
        }
    }
    
    //把剩余的元素加入数组
    while (p1 <= l1-1)
    {
        temp[t++] = s1[p1++];
    }

    while (p2 <= l2-1)
    {
        temp[t++] = s2[p2++];
    }
    
    int index; //中位数所在数组下标

    //奇偶判断，计算L/2向上取整

    if ((l1+l2)%2 == 0) //偶数
    {
        index = (l1+l2)/2 - 1;
    }
    else //奇数
    {
        index = (l1+l2)/2;
    }
    
    res = temp[index];

}

/*
    解法2： 

        算法思想：

        分别求两个升序序列A、B的中位数，设为a,b，求序列A，B的中位数过程如下
        1. 若a=b,则a或b即为中位数，直接返回

        2. 若a<b，则舍弃A中较小的一半，同时舍弃序列B中较大的一半，要求两次舍弃的长度相等。

        3. 若a>b, 则舍弃A中较大的一半，同时舍弃序列B中较小的一半，要求两次舍弃的长度相等。

        4. 重复上述操作，直到两个序列中，均只含一个元素时为止

        时间空间复杂度：
            时间复杂度：
                序列A和B不断划分，设共需n次划分，则可以看成是一颗高度为n的二叉树，
                树高即为时间复杂度O（log2n）

            空间复杂度：
                O（1）
*/

bool GetMiddleElem2(ElemType A[], ElemType B[], int length, ElemType &res) // length A,B数组的长度，等长
{
    int r1=0, l1=length-1, mid1; //r为右指针，l为左指针，mid为中间下标指针
    int r2=0, l2=length-1, mid2;

    while (l1 < r1 || l2 < r2) //直到两个数组都划分剩下一个
    {
        mid1 = (r1+l1)/2;
        mid2 = (r2+l2)/2;

        if (A[mid1] == B[mid2])
        {
            res = A[mid1];
            return true;
        }
        else if (A[mid1] > B[mid2])
        {
            if (length%2 == 0) //偶数长度情况
            {
                r1 = mid1;//A数组舍弃大的部分，保留中点
                l2 = mid2+1;//B数组舍弃小的部分，舍弃中点，保证A和B分割后长度相等
            }
            else //奇数长度情况
            {
                r1 = mid1; //A数组舍弃大的部分，保留中点
                l2 = mid2; //B数组舍弃小的部分，保留中点
            }
        }
        else
        {
            if (length%2 == 0) //偶数长度情况
            {
                l1 = mid1+1;//A数组舍弃小的部分，舍弃中点
                r2 = mid2;//B数组舍弃大的部分，保留中点
            }
            else //奇数长度情况
            {
                l1 = mid1;
                r2 = mid2;
            }
        }
        
    }
    
    if (A[l1] > B[l2]) //此时l1==r1 , l2==r2
    {
        res = B[l2]; //返回较小的
    }
    else
    {
        res = A[l1]; //返回较小的
    }
    
    return true;
}


/*
    12. 已知一个整数序列A = （a0,a1,...,an-1），其中0<= ai <= n (o<=i<n)，若
    存在ap1 = ap2 = ... = apm = x，且m > n/2 (0<=pk<n,1<=k<=m)，则称x为A的主元素
    
    假设A中的n个元素保存在一个一维数组中，设计一个尽可能高效的算法，找出A的主元素，若存在，则输出，不存在则输出-1
*/

/*
    算法设计思想：
        1. 先遍历一次整个数组，得出一个最可能成为主元素的元素
        2. 再次遍历一次数组，判断这个元素的个数是否大于n/2，若大于则为主元素，否则返回-1

        如果得出最有可能成为主元素的元素？
            设置一个计数器和标识变量P，先将第一个元素放入p，计数器+1，
            在后序的遍历中，若遇到的不为（p），则计数器-1，若计算器减到0，则将新的元素放入（p）中
            若遇到的为（p），则计数器+1

    时间空间复杂度：
        空间复杂度：O（1）
        时间复杂度：O（n）    
*/

int FindMainElem(ElemType A[], int length)
{   
    ElemType p; //标识变量
    int nums = 0; //计数器
    int pNums = 0; //统计p中元素的个数

    for (int i = 0; i < length; i++)
    {
        if (nums == 0) //若计数器为0，则p更换新的元素，并且计数器置1
        {
            p = A[i];
        }

        if (A[i] == p) //判断下一个元素是否和p中的一样？
        {
            nums++; //计数器加1
        }
        else
        {
            nums--; //若不一样，则计数器-1
        }
    }

    for (int j = 0; j < length; j++) //统计p中元素的个数
    {
        if (A[j] == p)
        {
            pNums++;
        }
    }
    
    //判断该元素是否满足条件
    if (pNums > length/2)
    {
        return p;
    }

    return -1; 
}

/*
    解法二：
        先排序后计数，先将数组按从小到大的顺序排序（快排），再遍历数组计数

    时空复杂度：
        时间复杂度：O（nlog2n）
        空间复杂度：O（n）
*/

int Partition(ElemType A[], int low, int high)
{
    ElemType pivot = A[low]; //将第一个元素设置为中枢

    while (low < high)
    {
        while (low < high && A[high] >= pivot)
        {
            high--;
        }

        A[low] = A[high];

        while (low < high && A[low] <= pivot)
        {
            low++;
        }
        
        A[high] = A[low];
    }
    
    A[low] = pivot; //每一次划分都确定一个元素的最终位置

    return low;
}

void QuickSort(ElemType A[], int low, int high)
{
    if (low < high) //递归退出条件
    {
        int pivotpos = Partition(A, low, high); //划分
        QuickSort(A, low, pivotpos-1);
        QuickSort(A, pivotpos+1, high);
    }
    
}

int FindMainElem2(ElemType A[], int length)
{
    //先对数组A进行快速排序

    QuickSort(A,0,length-1);

    //再对排好序的数组中的元素进行计数

    int count=0;
    ElemType p = A[0]; //当前计数的元素 

    for (int i = 0; i < length; i++)
    {
        if (A[i] == p)
        {
            count++;
        }
        else
        {
            p = A[i];
            count = 1;
        }
        
        if (count > length/2)
        {
            return p;
        }
    }
    
    return -1;
}

/*
    13. 2018统考真题

    给定一个n长的数组，找出数组中未出现的最小正整数，如数组{-5,3,2,3}中未出现的最小正整数是1；
    数组{1，2，3}中未出现的最小正整数是4

    算法设计思想：  

        1. 先将数组排序（按照快速排序）

        2. 设置一个标识变量p记录最小正整数，默认初始值为1，遍历整个数组：
            若遇到小于等于0或下一个数比p中的大，继续遍历下一个元素
            若下一个数等于p，则p中的数加1

    时间空间复杂度:
        时间复杂度O（nlog2n）
        空间复杂度O（n）
*/

void FindMinNum(ElemType A[], int length, int &res)
{
    QuickSort(A, 0, length-1); //快排

    ElemType p=1; //标识变量p

    for (int i = 0; i < length; i++)
    {
        if (A[i] <= 0 || A[i] > p)
        {
            continue;
        }
        else
        {
            p++;
        }
    }
    
    res = p;
}

/*
    2020统考真题

    定义一个三元组(a,b,c)的距离D= |a-b|+|b-c|+|c-a|
    给定三个非空整数集合S1,S2和S3，按升序分别存储在3个数组中，
    计算并输出所有可能的三元组(a,b,c)中的最小距离
*/

/*
    暴力法：
        算法思想：
            列出所有可能的三元组，并分别计算他们的距离D，最后得出所有这些三元组中距离的最小值

        时空复杂度分析：
            时间复杂度：O（n1n2n3）
            空间复杂度: O（1）
*/

void GetMinDistance(ElemType A[], ElemType B[], ElemType C[], int length1, int length2, int length3, int &res)
{

    int minDis = 10000; //最短距离变量
    int Dis; //三元组的距离
    int a,b,c; //三元组对应的三个元素
    int p1,p2,p3; //计算三元组的三部分

    //暴力法列举出所有可能的三元组，并分别计算他们的距离
    for (int i = 0; i < length1; i++)
    {
        for (int j = 0; j < length2; j++)
        {
            for (int k = 0; k < length3; k++)
            {
                a = A[i];
                b = B[j];
                c = C[k];

                p1 = a-b;
                p2 = b-c;
                p3 = c-a;

                //取绝对值
                if (p1 < 0)
                {
                    p1 = -p1;
                }
                if (p2 < 0)
                {
                    p2 = -p2;
                }
                if (p3 < 0)
                {
                    p3 = -p3;
                }
                
                //计算距离
                Dis = p1+p2+p3;
                
                if (Dis < minDis)
                {
                    minDis = Dis;
                }   
            }   
        }    
    }
    
    res = minDis;
    
}

int main()
{
    int s1[5] = {11,13,15,17,19};
    int s2[4] = {2,4,6,8};

    ElemType res;

    GetMiddleElem(s1,s2,5,4,res);

    printf("res is : %d", res);

    int A[8] = {6,6,6,3,6,6,5,7};
    res = FindMainElem2(A, 8);

    printf("\nres is : %d", res);

    int Test[3] = {1,2,3};
    FindMinNum(Test,3,res);

    printf("\nres is : %d", res);

    //14题测试
    int A1[3] = {-1,0,9};
    int B1[4] = {-25,-10,10,11};
    int C1[5] = {2,9,17,30,41};

    GetMinDistance(A1,B1,C1,3,4,5,res);
    printf("\nres is : %d", res);

    return 0;
}
