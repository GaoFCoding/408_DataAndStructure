/*
    括号匹配问题
*/

/**************代码实现*****************/
#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef int Status;
typedef char ElemType;

typedef struct {
    ElemType * data;
    int top; //栈顶指针
} SqStack;

//以下的基本操作考试可以直接用!

//初始化栈
Status InitStack(SqStack &s)
{
    s.data = (ElemType *)malloc(MaxSize*sizeof(ElemType)); //分配内存空间
    if (s.data == NULL)
    {
        printf("init error\n");
        return -1;
    }
    
    s.top = -1;
    return 0;
}

//判断栈是否为空
bool IsEmpty(SqStack s)
{
    if (s.top == -1)
    {
        printf("is empty!\n");
        return true;
    }
    return false;
}

//新元素入栈
Status Push(SqStack &s, ElemType newdata)
{
    if (s.top >= MaxSize - 1) //判断是否栈满
    {
        printf("is full !\n");
        return -1;
    }

    s.data[++s.top] = newdata;
    return 0;
}

//栈顶元素出栈并返回
Status Pop(SqStack &s, ElemType &res)
{
    if (s.top == -1)
    {
        printf("already empty!\n");
        return -1;
    }

    res = s.data[s.top--];
    return 0;
}

//符号匹配算法
/*
    用栈实现括号匹配:
    依次扫描所有字符，遇到左括号入栈，遇到右括号则弹出栈顶元素检查是否匹配

    匹配失败的情况：
        1. 左括号单身，左括号多了
        2. 右括号单身，右括号多了
        3. 左右括号不匹配
*/


bool BrackMatching(ElemType str[], int length) //输入参数为待检验的字符数组与字符数组的长度
{
    //栈初始化
    SqStack sq;
    InitStack(sq);

    //依次遍历字符数组的字符
    for (int i = 0; i < length; i++)
    {
        ElemType cur = str[i]; //当前指向的字符
        if (cur == '[' || cur == '(' || cur == '{')
        {
            //若当前字符为左括号，则入栈
            Push(sq,cur);
        } 
        else {
            //若为右括号，则出栈
            ElemType curLef;
            int err = Pop(sq, curLef);
            if (err == -1)
            {
                printf("match error！right bracket is more than left\n");
                return false;
            }
            
            
            //若括号不匹配，则直接结束循环，匹配失败
            if (cur==')'&&curLef!='(')
            {
                printf("error！\n");
                return false;
            }

            if (cur=='}'&&curLef!='{')
            {
                printf("error！\n");
                return false;
            }

            if (cur==']'&&curLef!='[')
            {
                printf("error！\n");
                return false;
            }
        }    
    }
    
    //判断栈是否还有剩余，有则匹配失败
    if (!IsEmpty(sq))
    {
        printf("match error！left bracket is more than right！\n");
        return false;
    }

    printf("success!");
    return true;
}

int main(void)
{
    ElemType str[3] = {'[','}','}'};
    BrackMatching(str,3);
}