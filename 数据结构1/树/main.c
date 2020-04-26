//
//  main.c
//  树
//
//  Created by xingling xu on 2020/4/26.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;        /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int CElemType;      /* 树结点的数据类型，目前暂定为整型 */
typedef CElemType SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点  */
CElemType Nil = 0;   /*设整型以0为空 或者以 INT_MAX(65535)*/

typedef struct {
    int level; //结点层
    int order; //本层的序号(按照满二叉树给定序号规则)
}Position;

#pragma mark -- 二叉树的基本操作
//6.1 visit
Status visit(CElemType c){
    printf("%d ",c);
    return OK;
}

//6.2 构造空二叉树T,因为T是固定数组,不会改变.
Status InitBiTree(SqBiTree T){
    
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        //将二叉树初始化值置空
        T[i] = Nil;
    }
    
    return OK;
}

//6.3 按层序次序输入二叉树中的结点值(字符型或整型),构造顺序存储的二叉树T
Status CreateBiTree(SqBiTree T){
    int i = 0;
    
    //printf("按层序输入结点的值(整型),0表示空结点, 输入999结束.结点数<=%d\n",MAX_TREE_SIZE);
    /*
     1      -->1
     2     3   -->2
     4  5  6   7 -->3
     8  9 10       -->4
     
     1 2 3 4 5 6 7 8 9 10 Nil Nil Nil
     */
    
    while (i < 10) {
        T[i] = i+1;
        printf("%d ",T[i]);
        
        //结点不为空,且无双亲结点
        if (i != 0 && T[(i+1)/2-1] == Nil && T[i] != Nil) {
            printf("出现无双亲的非根结点%d\n",T[i]);
            exit(ERROR);
        }
        
        i++;
        
    }
    
    //将空赋值给T的后面的结点
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil;
        i++;
    }
    
    return OK;
}

//技巧:
//如果大家想要2个函数的结果一样,但是目的不同;
//在顺序存储结构中, 两个函数完全一样的结果
#define ClearBiTree InitBiTree

/*6.4 判断二叉树是否为空
 初始条件: 二叉树已存在
 操作结果: 若T为空二叉树,则返回TRUE,否则返回FALSE;
 */
Status BiTreeEmpty(SqBiTree T){
    //根结点为空,则二叉树为空
    if (T[0] == Nil)
        return TRUE;
    
    return FALSE;
}

/*6.5 获取二叉树的深度
 初始条件: 二叉树已存在
 操作结果: 返回二叉树T深度;
 */
int BiTreeDepth(SqBiTree T){
    
    int j = -1;
    int i;
    
    //找到最后一个结点
    //MAX_TREE_SIZE -> 100 -> 10 目的找到最后一个结点10的位置
    for (i = MAX_TREE_SIZE-1 ; i>=0; i--) {
        if (T[i] != Nil)
            break;
    }
    
    do {
        j++;
    } while ( powl(2, j) <= i); //计算2的次幂
    
    return j;
}

/*6.6 返回处于位置e(层,本层序号)的结点值
 初始条件: 二叉树T存在,e是T中某个结点(的位置)
 操作结构: 返回处于位置e(层,本层序号)的结点值
 */
CElemType Value(SqBiTree T,Position e){
    
    /*
     Position.level -> 结点层.表示第几层;
     Position.order -> 本层的序号(按照满二叉树给定序号规则)
     */
    
    //pow(2,e.level-1) 找到层序
    printf("%d\n",(int)pow(2,e.level-1));
    
    //e.order
    printf("%d\n",e.order);
    
    //4+2-2;
    return T[(int)pow(2, e.level-1)+e.order-2];
    
}


/*6.7 获取二叉树跟结点的值
 初始条件: 二叉树T存在
 操作结果: 当T不空,用e返回T的根, 返回OK; 否则返回ERROR
 */
Status Root(SqBiTree T,CElemType *e){
    if (BiTreeEmpty(T)) {
        return ERROR;
    }
    
    *e = T[0];
    return OK;
}

/*
 6.8 给处于位置e的结点赋值
 初始条件: 二叉树存在,e是T中某个结点的位置
 操作结果: 给处于位置e的结点赋值Value;
 */
Status Assign(SqBiTree T,Position e,CElemType value){
    
    //找到当前e在数组中的具体位置索引
    int i = (int)powl(2, e.level-1)+e.order -2;
    
    //叶子结点的双亲为空
    if (value != Nil &&  T[(i+1)/2-1] == Nil) {
        return ERROR;
    }
    
    //给双亲赋空值但是有叶子结点
    if (value == Nil && (T[i*2+1] != Nil || T[i*2+2] != Nil)) {
        return  ERROR;
    }
    
    T[i] = value;
    return OK;
}

/*
 6.9 获取e的双亲;
 初始条件: 二叉树存在,e是T中的某一个结点
 操作结果: 若e是T的非根结点, 则返回它的双亲,否则返回"空"
 */
CElemType Parent(SqBiTree T, CElemType e){
    
    //空树
    if (T[0] == Nil) {
        return Nil;
    }
    
    for (int i = 1 ; i < MAX_TREE_SIZE; i++) {
        //找到e
        if (T[i] == e) {
            return T[(i+1)/2 - 1];
        }
    }
    
    //没有找到
    return Nil;
    
}

/*
 6.10 获取某个结点的左孩子;
 初始条件:二叉树T存在,e是某个结点
 操作结果:返回e的左孩子,若e无左孩子,则返回"空"
 */
CElemType LeftChild(SqBiTree T,CElemType e){
    
    //空树
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i = 0 ; i < MAX_TREE_SIZE-1; i++) {
        //找到e
        if (T[i] == e) {
            return T[i*2+1];
        }
    }
    
    //没有找到
    return Nil;
    
}

/*
 6.11 获取某个结点的右孩子;
 初始条件:二叉树T存在,e是某个结点
 操作结果:返回e的左孩子,若e无左孩子,则返回"空"
 */
CElemType RightChild(SqBiTree T,CElemType e){
    
    //空树
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i = 0 ; i < MAX_TREE_SIZE-1; i++) {
        //找到e
        if (T[i] == e) {
            return T[i*2+2];
        }
    }
    
    //没有找到
    return Nil;
    
}

/*
 6.12 获取结点的左兄弟
 初始条件:  二叉树T存在,e是T中某个结点
 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
 */
CElemType LeftSibling(SqBiTree T,CElemType e)
{
    /* 空树 */
    if(T[0]==Nil)
        return Nil;
    
    for(int i=1;i<=MAX_TREE_SIZE-1;i++)
    /* 找到e且其序号为偶数(是右孩子) */
        if(T[i]==e&&i%2==0)
            return T[i-1];
    
    return Nil; /* 没找到e */
}

/* 6.13 获取结点的右兄弟
 初始条件: 二叉树T存在,e是T中某个结点
 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
 */
CElemType RightSibling(SqBiTree T,CElemType e)
{
    /* 空树 */
    if(T[0]==Nil)
        return Nil;
    
    for(int i=1;i<=MAX_TREE_SIZE-1;i++)
    /* 找到e且其序号为奇数(是左孩子) */
        if(T[i]==e&&i%2==1)
            return T[i+1];
    
    return Nil; /* 没找到e */
}

#pragma mark -- 二叉树的遍历

/*
 6.14 层序遍历二叉树
 */
void LevelOrderTraverse(SqBiTree T){
    
    int i = MAX_TREE_SIZE-1;
    
    //找到最后一个非空结点的序号
    while (T[i] == Nil) i--;
    
    //从根结点起,按层序遍历二叉树
    for (int j = 0; j <= i; j++)
        //只遍历非空结点
        if (T[j] != Nil)
            visit(T[j]);
    
    printf("\n");
}

/*
 6.15 前序遍历二叉树
 */
void PreTraverse(SqBiTree T,int e){
    
    //打印结点数据
    visit(T[e]);
    
    //先序遍历左子树
    if (T[2 * e + 1] != Nil) {
        PreTraverse(T, 2*e+1);
    }
    //最后先序遍历右子树
    if (T[2 * e + 2] != Nil) {
        PreTraverse(T, 2*e+2);
    }
}

Status PreOrderTraverse(SqBiTree T){
    
    //树不为空
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\n");
    return  OK;
}

/*
 6.16 中序遍历
 */
void InTraverse(SqBiTree T, int e){
    
    /* 左子树不空 */
    if (T[2*e+1] != Nil)
        InTraverse(T, 2*e+1);
    
    visit(T[e]);
    
    /* 右子树不空 */
    if (T[2*e+2] != Nil)
        InTraverse(T, 2*e+2);
}

Status InOrderTraverse(SqBiTree T){
    
    /* 树不空 */
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

/*
 6.17 后序遍历
 */
void PostTraverse(SqBiTree T,int e)
{   /* 左子树不空 */
    if(T[2*e+1]!=Nil)
        PostTraverse(T,2*e+1);
    /* 右子树不空 */
    if(T[2*e+2]!=Nil)
        PostTraverse(T,2*e+2);
    
    visit(T[e]);
}
Status PostOrderTraverse(SqBiTree T)
{
    if(!BiTreeEmpty(T)) /* 树不空 */
        PostTraverse(T,0);
    printf("\n");
    return OK;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("二叉树顺序存储结构实现!\n");
    
    Status iStatus;
    Position p;
    CElemType e;
    SqBiTree T;
    
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后,树空否？%d(1:是 0:否) \n",BiTreeEmpty(T));
    printf("树的深度=%d\n",BiTreeDepth(T));
    
    p.level=3;
    p.order=2;
    e=Value(T,p);
    printf("第%d层第%d个结点的值: %d\n",p.level,p.order,e);
    
    
    iStatus = Root(T, &e);
    if (iStatus) {
        printf("二叉树的根为:%d\n",e);
    }else
    {
        printf("树为空,无根!\n");
    }
    
    //向树中3层第2个结点位置上结点赋值99
    e = 99;
    Assign(T, p, e);
    
    //获取树中3层第2个结点位置结点的值是多少:
    e=Value(T,p);
    printf("第%d层第%d个结点的值: %d\n",p.level,p.order,e);
    
    //找到e这个结点的双亲;
    printf("结点%d的双亲为%d_",e,Parent(T, e));
    //找到e这个结点的左右孩子;
    printf("左右孩子分别为:%d,%d\n",LeftChild(T, e),RightChild(T, e));
    //找到e这个结点的左右兄弟;
    printf("结点%d的左右兄弟:%d,%d\n",e,LeftSibling(T, e),RightSibling(T, e));
    
    
    Assign(T, p, 5);
    
    printf("二叉树T层序遍历:");
    LevelOrderTraverse(T);
    
    printf("二叉树T先序遍历:");
    PreOrderTraverse(T);
    
    printf("二叉树T中序遍历:");
    InOrderTraverse(T);
    
    printf("二叉树T后序遍历:");
    PostOrderTraverse(T);
    
    return 0;
}
