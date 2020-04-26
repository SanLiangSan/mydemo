#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;        /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;    /* ElemType类型根据实际情况而定，这里假设为int */
typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */

//----字符串相关操作---
/* 生成一个其值等于chars的串T */
Status StrAssign(String  T,char *chars)
{
    int i;
    if(strlen(chars)>MAXSIZE)
        return ERROR;
    else
    {
        T[0]=strlen(chars);
        for(i=1;i<=T[0];i++)
            T[i]=*(chars+i-1);
        return OK;
    }
}

Status ClearString(String S)
{
    S[0]=0;/*  令串长为零 */
    return OK;
}

/*  输出字符串T。 */
void StrPrint(String T)
{
    int i;
    for(i=1;i<=T[0];i++)
        printf("%c",T[i]);
    printf("\n");
}

/* 返回串的元素个数 */
int StrLength(String S)
{
    return S[0];
}

//----KMP 模式匹配算法---
//1.通过计算返回子串T的next数组;
//注意字符串T[0]中是存储的字符串长度; 真正的字符内容从T[1]开始;
void get_next(String T,int *next){
    int i,j;
    j = 1;
    i = 0;
    next[1] = 0;
    //abcdex
    //遍历T模式串, 此时T[0]为模式串T的长度;
    //printf("length = %d\n",T[0]);
    while (j < T[0]) {
        //printf("i = %d j = %d\n",i,j);
        if(i ==0 || T[i] == T[j]){
            //T[i] 表示前缀的单个字符;
            //T[j] 表示后缀的单个字符;
            ++i;
            ++j;
            next[j] = i;
            //printf("next[%d]=%d\n",j,next[j]);
        }else
        {
            //如果字符不相同,则i值回溯;
            i = next[i];
        }
    }
}

//输出Next数组值
void NextPrint(int next[],int length)
{
    int i;
    for(i=1;i<=length;i++)
        printf("%d",next[i]);
    printf("\n");
}

int count = 0;
//KMP 匹配算法(1)
//返回子串T在主串S中第pos个字符之后的位置, 如不存在则返回0;
int Index_KMP(String S,String T,int pos){
    
    //i 是主串当前位置的下标准,j是模式串当前位置的下标准
    int i = pos;
    int j = 1;
    
    //定义一个空的next数组;
    int next[MAXSIZE];
    
    //对T串进行分析,得到next数组;
    get_next(T, next);
    count = 0;
    //注意: T[0] 和 S[0] 存储的是字符串T与字符串S的长度;
    //若i小于S长度并且j小于T的长度是循环继续;
    while (i <= S[0] && j <= T[0]) {
        
        //如果两字母相等则继续,并且j++,i++
        if(j == 0 || S[i] == T[j]){
            i++;
            j++;
        }else{
            //如果不匹配时,j回退到合适的位置,i值不变;
            j = next[j];
        }
    }
    
    if (j > T[0]) {
        return i-T[0];
    }else{
        return -1;
    }
    
}

//KMP 匹配算法(2)
//求模式串T的next函数值修正值并存入nextval数组中;
void get_nextVal(String T,int *nextVal){
    int i,j;
    j = 1;
    i = 0;
    nextVal[1] = 0;
    while (j < T[0]) {
        if (i == 0 || T[i] == T[j]) {
            ++j;
            ++i;
            //如果当前字符与前缀不同,则当前的j为nextVal 在i的位置的值
            if(T[i] != T[j])
                nextVal[j] = i;
            else
                //如果当前字符与前缀相同,则将前缀的nextVal 值赋值给nextVal 在i的位置
                nextVal[j] = nextVal[i];
        }else{
            i = nextVal[i];
        }
    }
}

//KMP 匹配算法(2)
//返回子串T在主串S中第pos个字符之后的位置, 如不存在则返回0;
int Index_KMP2(String S,String T,int pos){
    
    //i 是主串当前位置的下标准,j是模式串当前位置的下标准
    int i = pos;
    int j = 1;
    
    //定义一个空的next数组;
    int next[MAXSIZE];
    
    //对T串进行分析,得到next数组;
    get_nextVal(T, next);
    count = 0;
    //注意: T[0] 和 S[0] 存储的是字符串T与字符串S的长度;
    //若i小于S长度并且j小于T的长度是循环继续;
    while (i <= S[0] && j <= T[0]) {
        
        //如果两字母相等则继续,并且j++,i++
        if(j == 0 || S[i] == T[j]){
            i++;
            j++;
        }else{
            //如果不匹配时,j回退到合适的位置,i值不变;
            j = next[j];
        }
    }
    
    if (j > T[0]) {
        return i-T[0];
    }else{
        return -1;
    }
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, KMP匹配算法实现!\n");
    int i,*p,*t;
    String s1,s2;
    int Status;
    
    /*关于next数组的求解*/
    StrAssign(s1,"abeabf");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
//    t=(int*)malloc((i+1)*sizeof(int));
//    get_nextVal(s1, t);
//    printf("NextVal为: ");
//    NextPrint(t,StrLength(s1));
//    printf("\n");
    
    //KMP算法调用
//    StrAssign(s1,"abcababca");
//    printf("主串为: ");
//    StrPrint(s1);
//    StrAssign(s2,"abcdex");
//    printf("子串为: ");
//    StrPrint(s2);
//    Status = Index_KMP(s1,s2,1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP算法）[返回位置为负数表示没有匹配] \n",Status);
//    Status = Index_KMP2(s1, s2, 1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP_2算法）[返回位置为负数表示没有匹配] \n\n",Status);
//
//    StrAssign(s1,"abccabcceabc");
//    printf("主串为: ");
//    StrPrint(s1);
//    StrAssign(s2,"abcce");
//    printf("子串为: ");
//    StrPrint(s2);
//    Status = Index_KMP(s1,s2,1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP算法）[返回位置为负数表示没有匹配] \n",Status);
//    Status = Index_KMP2(s1, s2, 1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP_2算法）[返回位置为负数表示没有匹配] \n\n",Status);
//
//    StrAssign(s1,"aaaabcde");
//    printf("主串为: ");
//    StrPrint(s1);
//    StrAssign(s2,"aaaaax");
//    printf("子串为: ");
//    StrPrint(s2);
//    Status = Index_KMP(s1,s2,1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP算法）[返回位置为负数表示没有匹配] \n",Status);
//    Status = Index_KMP2(s1, s2, 1);
//    printf("主串和子串在第%d个字符处首次匹配（KMP_2算法）[返回位置为负数表示没有匹配] \n\n",Status);
    
    
    return 0;
}
