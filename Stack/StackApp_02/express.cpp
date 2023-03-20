/*
    实现中缀表达式的计算
*/
#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef char ElemType;
typedef int Status;

//顺序栈
typedef struct 
{
    ElemType * data;
    int top;
} SqStack;

//以下为栈的基本操作

//初始化顺序栈
bool InitStack(SqStack &s)
{
    s.data = (ElemType *)malloc(MaxSize*sizeof(ElemType));
    if (s.data == NULL)
    {
        printf("Init stack with error");
        return false;
    }
    s.top = -1; //初始化栈顶指针
    return true;
}

//入栈
bool Push(SqStack &s, ElemType newdata)
{
    if (s.top >= MaxSize - 1) //判断当前是否栈满
    {
        return false;
    }
    s.data[++s.top] = newdata; //入栈
    return true;
}

//出栈
bool Pop(SqStack &s, ElemType &res)
{
    if (s.top == -1) //是否栈空判断
    {
        return false;
    }

    res = s.data[s.top--];
    return true;
}


//判断栈是否为空
bool IsEmpty(SqStack s)
{
    if (s.top == -1)
    {
        return true;
    }
    return false;
}

/*
    实现中缀表达式的计算

    1. 初始化两个栈，一个存放操作数，一个存放运算符
    2. 若扫描到操作数，则压入操作数栈
    3. 若扫描到运算符或界限符，则按照中缀转后缀相同的逻辑压入运算符栈（期间也会弹出运算符），
       每次弹出一个运算符时，该运算符生效，就需要弹出两个操作数栈的栈顶元素并执行相应的计算，
       运算结果再压入操作数栈
*/

//两个操作数的运算
Status Caculate2Nums(ElemType cur) //输入是当前弹出的操作符
{
    
}

Status Caculation(ElemType arr[], int length) //输入为表达式数组与该数组的长度
{
    //初始化操作数栈与运算符栈
    SqStack numsStack, charStack;
    InitStack(numsStack),InitStack(charStack);

    for (int i = 0; i < length; i++) //遍历中缀表达式
    {
        ElemType cur = arr[i];
        if (cur == '+' || cur == '-' || cur == '*' || cur == '/') //遇到运算符
        {
            ElemType res;

            for (int i = charStack.top; i > -1; i--)
            {   
                //判断是否遇到左括号，是则退出扫描
                if (charStack.data[i] == '(')
                {
                    Pop(charStack,res); //左括号出栈
                    break;
                }

                //若遇到优先级高的运算符，则弹出并参与运算
                switch (cur)
                {
                case '+':
                    break;
                case '-':
                    break;
                case '*':
                    break;
                case '/':
                    break;

                default:
                    break;
                }
                
                
                //最后再把当前的运算符压入栈中
                Push(charStack,cur);
            }
            
           
        }

        
    } 
  
    
    
    
}

void main(void)
{

}


