/*
    串

    串的基本操作
    
        1. StrAssign(&T, chars)  赋值操作，把T赋值为chars
        2. StrCopy(&T, S)        复制操作，把S复制到T中
        3. StrEmpty(S)           判空操作，若S为空串，则返回True
        4. StrCompare(S, T)      比较操作，若S > T, 则返回值 > 0；S = T则返回值=0 ;若S < T则返回值<0
        5. StrLength(S)          求串长
        6. SubString(&Sub, S, pos, len) 求子串，用sub返回串s的第pos个字符起长度为len的子串
        7. Concat(&T, S1, S2)    串连接，用T返回S1，S2连接的新串
        8. Index(S, T)           定位操作，若主串S存在与串T值相同的子串，则返回他在主串中第一次出现的位置，否则函数值为0
        9. ClearString(&S)
        10. DestoryString(&S)
*/
#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef struct {
    char * data;
    int length;
} Str;

bool SubString(Str &sub, Str s, int pos, int len)
{
    if (pos + len - 1 > s.length)
    {
        return false;
    }
    for (int i = pos; i <= pos+len-1 ; i++)
    {
        sub.data[i-pos+1] = s.data[i];
    }
    sub.length = len;
    return true;
}

int StrCompare(Str s, Str t)
{
    for (int i = 1; i<=s.length && i<=t.length; i++)
    {
        if (s.data[i]!=t.data[i])
        {
            return s.data[i]-t.data[i];
        }
    }
    return s.length - t.length;
}

//带基本操作的简单模式匹配（暴力法）
int Index(Str s, Str t)
{
    int i = 1;
    Str sub;
    while (i <= s.length-t.length+1)
    {
        SubString(sub,s,i,t.length); //获取后移一个单位后的新子串
        if (!StrCompare(sub,t)) //比较
        {
            return i;  
        }
        i++;
    }
    return 0;
}

//不带基本操作的简单模式匹配（暴力法）
int IndexRaw(Str s, Str t)
{
    int cur = 1; //主串移动指针
    int si = cur,  ti = 1; //扫描指针

    while (cur <= s.length && ti <= t.length)
    {
        if (s.data[si] == t.data[ti]) //若匹配成功，则扫描指针后移
        {
            si++;
            ti++;
        }
        else 
        { //若匹配失败，则主串移动指针+1，扫描指针回溯
            ti = 1;
            cur++;
            si = cur;
        }
    }
    //如果ti扫描了一整片的模式串，则匹配成功，返回主串当前指针位置cur即为当前子串在主串第一个位置处的索引
    if (ti > t.length)
    {
        return cur;
    }
    return 0;
}

//next数组求解
void get_next(Str T, int next[])
{
    int i=1, j=0;
    next[1] = 0;
    while (i < T.length)
    {
        if (j==0 || T.data[i] == T.data[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    
}

//nextval数组求解
void get_nextval(Str T, int nextval[])
{
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T.length)
    {
        if (j == 0 | T.data[i] == T.data[j])
        {
            ++i;
            ++j;
            if (T.data[i] != T.data[j])
            {
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            } 
        }
        else
        {
            j = nextval[j];
        }
    }
    
}

//KMP算法
int Index_KMP(Str s, Str t, int next[])
{
    int si = 1, ti = 1; //初始化两个指针，分别指向主串和模式串
    while (si <= s.length && ti <= s.length)
    {
        if (ti == 0 || s.data[si] == t.data[ti]) //若ti=1时就不匹配了，则也让si与ti 也同时往后移(next[1] == 0)
        {
            si++;
            ti++;
        }
        else{
            ti = next[ti]; //根据next数组找到ti要回溯到模式串的某个位置   
        }
    }
    if (ti > t.length)
    {
        return si - t.length; //减去扫描过的那部分
    }
    return 0;

}
  

void main(void)
{

}