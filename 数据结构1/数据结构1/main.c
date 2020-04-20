//
//  main.c
//  数据结构1
//
//  Created by xingling xu on 2020/3/31.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 1
#define FAILURE 0
#define SUCCESS 1

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如 SUCCESS、FAILURE等 */
typedef int ListData;/* ListData类型根据实际情况而定，这里假设为int */


typedef struct Node {
    ListData data;
    struct Node *next;
} Node;

typedef struct Node* LinkList;
// 初始化单链表 并创建头节点
Status InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return ERROR;
    (*L)->data = -1;
    (*L)->next = NULL;
    return SUCCESS;
}


// location from 1...
Status InsertNode(LinkList *L,int location,ListData data) {
    // 找到需要location-1位置的节点
    Node *pre = *L;
    // 因为0位置被头节点占了，所以要从1位置开始
    int currentLocation = 1;
    while (pre && currentLocation < location) {
        pre = pre->next;
        currentLocation ++;
    }
    if (!pre || currentLocation < location) return ERROR;
    
    // 根据data生成一个新节点
    Node *insertNode = (Node *)malloc(sizeof(Node));
    insertNode->data = data;
    // 让新节点的next 指向 pre->next
    insertNode->next = pre->next;
    // 让前一个节点的next指向新节点
    pre->next = insertNode;
    return SUCCESS;
}

// 删除节点
Status DeleteNode (LinkList *L ,int location,ListData *deleteData) {
    Node *pre = *L;
    int currentLocation = 1;
    // 还是找到location-1位置的节点
    while (pre && currentLocation < location) {
        pre = pre->next;
        currentLocation++;
    }
    if (!pre || currentLocation < location) return ERROR;
    // 创建临时变量 保存即将被删除的节点
    Node *temp = pre->next;
    if (!temp) return ERROR;
    // 前驱节点指向后驱节点
    pre->next = temp->next;
    // 将我们删除的内容返回出去
    *deleteData = temp->data;
    // 释放内存
    free(temp);
    return SUCCESS;
}


Status clearList(LinkList *L) {
    // 由于第一个是头节点，我们从第二个节点开始删除，这个地方可以根据实际情况来
    Node *pre = (*L)->next;
    Node *nextNode;
    while (pre) {
        // 用一个临时变量保存当前要删除的节点指向的下一个节点，有点像递归的意思
        nextNode = pre->next;
        // 释放
        free(pre);
        // 将要删除的指针偏移到下一个指针
        pre = nextNode;
    }
    // 此处将头节点指向NULL ，否则就出现野指针了
    (*L)->next = NULL;
    return SUCCESS;
}


Node *reverseList(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node *nowHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return nowHead;
}


Status InitFromHead(LinkList *L,int n) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return ERROR;
    (*L)->next = NULL;
    Node *pre = *L;
    for (int i = 1; i <= n; i ++) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = i;
        temp->next = pre->next;
        pre->next = temp;
    }
    return SUCCESS;
}

Status InitFromTail(LinkList *L,int n) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return ERROR;
    // 初始化的时候尾结点就是头节点
    Node *tail = *L;
    for (int i = 1; i <= n; i ++) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = i;
        temp->next = NULL;
        tail->next = temp;
        // 尾节点偏移
        tail = tail->next;
    }
    return SUCCESS;
}

// 尾部添加节点
Status AddNodeToTheTail(LinkList *L,ListData data) {
    Node *temp = *L;
    while (temp->next) {
        temp = temp->next;
    }
    if (!temp) return ERROR;
    Node *add = (Node *)malloc(sizeof(Node));
    add->data = data;
    add->next = NULL;
    temp->next = add;
    return SUCCESS;
}

// 打印方法 我们不用修改链表 无需传指针
Status printList (LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d\n",p->data);
        p = p->next;
    }
    return SUCCESS;
}



int main(int argc, const char * argv[]) {
    LinkList L;
    Status status = InitList(&L);
    printf("s is %d\n",status);
    // 插入元素
    for (int i = 5; i >= 1; i --) {
        InsertNode(&L, 1, i);// 此处1表示，总是从头节点后面插入新节点，也就是头插法，比较简单，因为尾插法还要保留链表长度
    }
    
    Node *reverse = reverseList(L);
    printList(reverse);
//    // 打印链表
//    printf("链表是 :\n");
//    printList(L);
//    // 删除第五个节点
//    ListData data;
//    DeleteNode(&L, 5, &data);
//    printf("删除第五个元素后的链表是 :\n");
//    printList(L);
//    printf("被删除的值是 %d\n",data);
//
//    clearList(&L);
//    for (int i = 0; i < 20; i ++) {
//        AddNodeToTheTail(&L, i);
//    }
//    printf("链表是 :\n");
//    printList(L);
//
//    clearList(&L);
//    InitFromHead(&L, 30);
//    printf("链表是 :\n");
//    printList(L);
//
//
//
//    clearList(&L);
//    InitFromTail(&L, 30);
//    printf("链表是 :\n");
//    printList(L);
    
    return 0;
}
