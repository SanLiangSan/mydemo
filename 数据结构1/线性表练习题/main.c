//
//  main.c
//  线性表练习题
//
//  Created by xingling xu on 2020/4/11.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define SUCCESS 1
#define ERROR 0
#define MAXSIZE 20

typedef int ListData;
typedef int Status;

typedef struct Node {
    ListData data;
    struct Node *next;
} Node;

typedef Node* LinkList;

Status InitList(LinkList *L) {
    //产生头结点,并使用L指向此头结点
    *L = (LinkList)malloc(sizeof(Node));
    //存储空间分配失败
    if(*L == NULL) return ERROR;
    //将头结点的指针域置空
    (*L)->next = NULL;
    return SUCCESS;
}

Status ListInsert(LinkList *L,int i,ListData e){
    
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    
    //寻找第i个结点
    while (p && j<i) {
        p = p->next;
        ++j;
    }
    //第i个元素不存在
    if(!p || j>i) return ERROR;
    
    //生成新结点s
    s = (LinkList)malloc(sizeof(Node));
    //将e赋值给s的数值域
    s->data = e;
    //将p的后继结点赋值给s的后继
    s->next = p->next;
    //将s赋值给p的后继
    p->next = s;
    
    return SUCCESS;
}

Status ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        printf("%d  ",p->data);
        p=p->next;
    }
    printf("\n");
    return SUCCESS;
}

/*
 
 作业1:
 题目:
 将2个递增的有序链表合并为一个有序链表; 要求结果链表仍然使用两个链表的存储空间,不另外占用其他的存储空间. 表中不允许有重复的数据
 
 关键词:递增有序链表,不允许有重复数据,保留递增关系(后插法)
 不占用额外的存储空间指的是不能开辟新节点,赋值在链接到链表上;
 
 算法思想:
 (1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
 (2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时,依次摘取其中较小值重新链表在Lc表的最后.
 (3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素,这样确保合并后表中无重复的元素;
 (4)当一个表达到表尾结点为空时,非空表的剩余元素直接链接在Lc表最后.
 (5)最后释放链表Lb的头结点;
 
 */
Status MergeList(LinkList *La,LinkList *Lb,LinkList *Lc) {
    // 找到首元节点，依次遍历
    Node *pa = (*La)->next;
    Node *pb = (*Lb)->next;
    // 由于不能开辟新的空间，我们借用La的空间
    Node *pc = *La;
    // pc是一个局部变量 保存的是Lc的尾节点，每次都指向两个值中的最小值，如果相等则保持其一，删除释放另外一个
    while (pa && pb) {
        if (pa->data < pb->data) {
            pc->next = pa;
            pc = pa;// 这地方相当于pc = pc->next 也就是说pc指针也要后移
            pa = pa->next;
        } else if (pa->data > pb->data) {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        } else {
            Node *temp = pb;
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            pb = pb->next;
            free(temp);
        }
    }
    
    // 最后多余的数据一定是后续最大的
    pc->next = pa?pa:pb;
    *Lc = *La;
    return SUCCESS;
}

/*
 作业2:
 题目:
 已知两个链表A和B分别表示两个集合.其元素递增排列. 设计一个算法,用于求出A与B的交集,并存储在A链表中;
 例如:
 La = {2,4,6,8}; Lb = {4,6,8,10};
 Lc = {4,6,8}
 
 关键词:依次摘取2个表中相等的元素重新进行链接,删除其他不等的元素;
 
 
 算法思想:
 (1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
 (2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时.
 (3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素;
 (4)如果其中一个表中的元素较小,删除此表中较小的元素. 此表的工作指针后移;
 (5)当链表La和Lb有一个先到达表尾结点为空时,依次删除另一个非空表中的所有元素,最后释放链表lb;
 
 */
Status Intersection(LinkList *La,LinkList *Lb,LinkList *Lc) {
    Node *pa = (*La)->next;
    Node *pb = (*Lb)->next;
    Node *pc = *La;
    Node *temp;
    while (pa && pb) {
        // 每次碰到小的就过滤掉并释放
        if (pa->data < pb->data) {
            temp = pa;
            pa = pa->next;
            free(temp);
        } else if (pa->data > pb->data) {
            temp = pb;
            pb = pb->next;
            free(temp);
        } else {
            // 碰到相等的保留其中一个并释放另外一个
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
            temp = pb;
            pb = pb->next;
            free(temp);
        }
    }
    // 要额外判断多余的情况
    while (pa) {
        temp = pa;
        pa = pa->next;
        free(temp);
    }

    while (pb) {
        temp = pb;
        pb = pb->next;
        free(temp);
    }
    pc->next = NULL;
    *Lc = *La;
    return SUCCESS;
}

/*
 作业3:
 题目:
 设计一个算法,将链表中所有节点的链接方向"原地旋转",即要求仅仅利用原表的存储空间. 换句话说,要求算法空间复杂度为O(1);
 例如:L={0,2,4,6,8,10}, 逆转后: L = {10,8,6,4,2,0};
 
 关键词:不能开辟新的空间,只能改变指针的指向; 可以考虑逐个摘取结点,利用前插法创建链表的思想,将结点一次插入到头结点的后面; 因为先插入的结点为表尾,后插入的结点为表头,即可实现链表的逆转;
 
 
 算法思想:
 (1)利用原有的头结点*L,p为工作指针, 初始时p指向首元结点. 因为摘取的结点依次向前插入,为确保链表尾部为空,初始时将头结点的指针域置空;
 (2)从前向后遍历链表,依次摘取结点,在摘取结点前需要用指针q记录后继结点,以防止链接后丢失后继结点;
 (3)将摘取的结点插入到头结点之后,最后p指向新的待处理节点q(p=q);
 */

void Inverse(LinkList *L) {
    //  头插法每次要插入的节点，初始是首元节点
    Node *target = (*L)->next;
    Node *tNext;
    // 为了让链表的尾结点指向NULL
    (*L)->next = NULL;
    while (target) {
        // 每次让tNext保存target之后的数据
        tNext = target->next;
        target->next = (*L)->next;
        (*L)->next = target;
        target = tNext;
    }
}

/*
 作业4:
 题目:
 设计一个算法,删除递增有序链表中值大于等于mink且小于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素;
 
 关键词: 通过遍历链表能够定位带删除元素的下边界和上边界, 即可找到第一个值大于mink的结点和第一个值大于等于maxk的结点;
 
 
 算法思想:
 (1)查找第一个值大于mink的结点,用q指向该结点,pre 指向该结点的前驱结点;
 (2)继续向下遍历链表, 查找第一个值大于等于maxk的结点,用p指向该结点;
 (3)修改下边界前驱结点的指针域, 是其指向上边界(pre->next = p);
 (4)依次释放待删除结点的空间(介于pre和p之间的所有结点);
 */

void DeleteDataRange(LinkList *L, int min,int max) {
    Node *p = (*L)->next;
    Node *left = *L,*right=NULL;
    // 找到左边节点
    while (p && p->data < min) {
        left = p;
        p = p->next;
    }
    
    // 找到右边节点
    while (p && p->data <= max) {
        right = p;
        p = p->next;
    }
    right = right->next;
    
    // 左边节点指向右边节点
    left->next = right;

    // 临时保存要删除的节点进行释放
    Node *temp = left->next;
    while (temp && temp != right) {
        Node *del = temp;
        temp = temp->next;
        free(del);
    }
}

/*
 题目5:
 设将n(n>1)个整数存放到一维数组R中, 试设计一个在时间和空间两方面都尽可能高效的算法;将R中保存的序列循环左移p个位置(0<p<n)个位置, 即将R中的数据由(x0,x1,......,xn-1)变换为(xp,xp+1,...,xn-1,x0,x1,...,xp-1).
 
 例如: pre[10] = {0,1,2,3,4,5,6,7,8,9},
 n = 10,p = 3;
 pre[10] = {3,4,5,6,7,8,9,0,1,2}
 
 算法思路:
 1. 先将n个数据原地逆置 9,8,7,6,5,4,3,2,1,0;
 2. 将n个数据拆解成[9,8,7,6,5,4,3] [2,1,0]
 2. 将前n-p个数据和后p个数据分别原地逆置; [3,4,5,6,7,8,9] [0,1,2]
 
 复杂度分析:
 时间复杂度: O(n); 时间复杂度:O(1);
 */

// 将数组指定范围的数据进行倒序
void Reverse (int *array,int left,int right ) {
    int i = left,j = right ;
    // 首位对调
    int temp;
    while (i < j) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        // i右移  j左移
        i++;
        j--;
    }
}
//将长度为n的数组pre 中的数据循环左移p个位置
void LeftShift(int *pre,int n,int p){
    // 比如 {1,2,3,4,5} 向左移2位
    if (p > 0 && p < n) {
        // 整个数组数据全部倒序 {5,4,3,2,1}
        Reverse(pre, 0, n-1);
        // 前部分倒序 {3,4,5,2,1}
        Reverse(pre, 0, n-p-1);
        // 后部分倒序 {3,4,5,1,2}
        Reverse(pre, n-p, n-1);
    }
}

/*
 题目6:
 已知一个整数序列A = (a0,a1,a2,...an-1),其中(0<= ai <=n),(0<= i<=n). 若存在ap1= ap2 = ...= apm = x,且m>n/2(0<=pk<n,1<=k<=m),则称x 为 A的主元素. 例如,A = (0,5,5,3,5,7,5,5),则5是主元素; 若B = (0,5,5,3,5,1,5,7),则A 中没有主元素,假设A中的n个元素保存在一个一维数组中,请设计一个尽可能高效的算法,找出数组元素中的主元素,若存在主元素则输出该元素,否则输出-1.
 
 题目分析:
 主元素,是数组中的出现次数超过一半的元素; 当数组中存在主元素时,所有非主元素的个数和必少于一半. 如果让主元素和一个非主元素配对, 则最后多出来的元素(没有元素与之匹配就是主元素.
 
 算法思路:
 1. 选取候选主元素, 从前向后依次扫描数组中的每个整数, 假定第一个整数为主元素,将其保存在Key中,计数为1. 若遇到下一个整数仍然等于key,则计数加1. 否则计数减1. 当计数减到0时, 将遇到的下一个整数保存到key中, 计数重新记为1. 开始新一轮计数. 即可从当前位置开始重上述过程,直到将全部数组元素扫描一遍;
 2. 判断key中的元素是否是真正的主元素, 再次扫描数组, 统计key中元素出现的次数,若大于n/2,则为主元素,否则,序列中不存在主元素;
 
 算法分析:
 时间复杂度: O(n)
 空间复杂度: O(1)
 */


/*
 题目7:
 用单链表保存m个整数, 结点的结构为(data,link),且|data|<=n(n为正整数). 现在要去设计一个时间复杂度尽可能高效的算法. 对于链表中的data 绝对值相等的结点, 仅保留第一次出现的结点,而删除其余绝对值相等的结点.例如,链表A = {21,-15,15,-7,15}, 删除后的链表A={21,-15,-7};
 
 题目分析:
 要求设计一个时间复杂度尽量高效的算法,而已知|data|<=n, 所以可以考虑用空间换时间的方法. 申请一个空间大小为n+1(0号单元不使用)的辅助数组. 保存链表中已出现的数值,通过对链表进行一趟扫描来完成删除.
 算法思路:
 1. 申请大小为n+1的辅助数组t并赋值初值为0;
 2. 从首元结点开始遍历链表,依次检查t[|data|]的值, 若[|data|]为0,即结点首次出现,则保留该结点,并置t[|data|] = 1,若t[|data|]不为0,则将该结点从链表中删除.
 
 复杂度分析:
 时间复杂度: O(m),对长度为m的链表进行一趟遍历,则算法时间复杂度为O(m);
 空间复杂度: O(n)
 */
void DeleteEqualNode(LinkList *L,int n) {
    int *p = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i ++) {
        *(p+i) = 0;
    }
    // r 指向头节点
    Node *r = *L;
    // 首元节点
    Node *temp = (*L)->next;
    while (temp) {
        ListData absData = abs(temp->data);
        if (p[absData] == 1) {// 说明已经有值了
            r->next = temp->next;
            free(temp);
        } else {
            p[absData] = 1;
            r = temp;
        }
        temp = temp->next;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // 算法题1
//    LinkList la,lb,lc;
//    InitList(&la);
//    InitList(&lb);
//    InitList(&lc);
//    for (int i = 6; i > 0; i --) {
//        ListInsert(&la, 1, i);
//    }
//    printf("打印la ：\n");
//    ListTraverse(la);
//
//    for (int i = 10; i > 2; i-=2) {
//        ListInsert(&lb, 1, i);
//    }
//    printf("打印lb ：\n");
//    ListTraverse(lb);
//
//    MergeList(&la, &lb, &lc);
//    printf("打印lc ：\n");
//    ListTraverse(lc);
    
//    // 题目2
//    LinkList la,lb,lc;
//    InitList(&la);
//    InitList(&lb);
//    InitList(&lc);
//    for (int i = 6; i > 0; i --) {
//        ListInsert(&la, 1, i);
//    }
//    printf("打印la ：\n");
//    ListTraverse(la);
//
//    for (int i = 10; i > 2; i-=2) {
//        ListInsert(&lb, 1, i);
//    }
//    printf("打印lb ：\n");
//    ListTraverse(lb);
//
//    Intersection(&la, &lb, &lc);
//    printf("打印lc ：\n");
//    ListTraverse(lc);
    
    // 题目3
//    LinkList la,lb,lc;
//    InitList(&la);
//    InitList(&lb);
//    InitList(&lc);
//    for (int i = 6; i > 0; i --) {
//        ListInsert(&la, 1, i);
//    }
//    printf("打印la ：\n");
//    ListTraverse(la);
//
//    Inverse(&la);
//    printf("打印la ：\n");
//    ListTraverse(la);
    
    // 题目4
//    LinkList la,lb,lc;
//    InitList(&la);
//    InitList(&lb);
//    InitList(&lc);
//    for (int i = 6; i > 0; i --) {
//        ListInsert(&la, 1, i);
//    }
//    printf("打印la ：\n");
//    ListTraverse(la);
//
//    DeleteDataRange(&la, 2, 3);
//    printf("打印la ：\n");
//    ListTraverse(la);
    
    // 题目 5
    int array[] = {1,2,3,4,5,6};
    LeftShift(array, 6, 2);
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        printf("%d-",array[i]);
    }
    printf("\n");
    
    return 0;
}
