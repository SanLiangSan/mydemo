//
//  main.c
//  单循环链表
//
//  Created by xingling xu on 2020/4/6.
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

typedef int ListData;
typedef int Status;

typedef struct Node {
    ListData data;
    struct Node *next;
} Node;

typedef struct Node * LinkList;

// 输入的方式尾插法创建单向循环链表
Status InitList(LinkList *L) {
    int number;
    Node *tail = NULL;
    while (1) {
        scanf("%d",&number);
        // 输入0结束创建
        if (number == 0) break;
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            if (*L == NULL)return ERROR;
            (*L)->data = number;
            (*L)->next = *L;
            tail = *L;
        } else {
            //找尾结点  方法1
//            for (tail = *L; tail->next != *L; tail = tail->next);
//            Node *temp = (Node *)malloc(sizeof(Node));
//            if (!temp) return ERROR;
//            temp->data = number;
//            temp->next = *L;
//            tail->next = temp;
//            if (tail == NULL) return ERROR;
            //方法2
            Node *node = (Node *)malloc(sizeof(Node));
            if (!node) return ERROR;
            node->data = number;
            node->next = *L;
            tail->next = node;
            tail = tail->next;
        }
    }
    return SUCCESS;
}

Status DeleteNode(LinkList *List,int location,ListData *deleteData) {
    Node *temp = *List;
    if (temp == NULL) return ERROR;
    Node *target;
    if (location == 1) {// 删除首元节点
        // 找到尾节点
        for (target = *List; target->next != *List; target = target->next);
        if (target == *List) {
            target->next = NULL;
            *List = NULL;
            *deleteData = temp->data;
            free(target);
            return SUCCESS;
        }
        target->next = temp->next;
        *List = target->next;
        *deleteData = temp->data;
        free(temp);
    } else {
        // 找到待删除节点的前一个节点
        target = *List;
        int i;
        for (i = 1,target = *List; i < location-1; i ++) {
            target = target->next;
        }
        Node *deleteNode = target->next;
        target->next = deleteNode->next;
        *deleteData = deleteNode->data;
        free(deleteNode);
    }
    return SUCCESS;
}

void InsertNode(LinkList *List,int location, ListData data) {
    // 创建待插入节点
    Node *insertNode = (Node *)malloc(sizeof(Node));
    if (insertNode == NULL) return;
    insertNode->data = data;
    insertNode->next = NULL;
    if (location == 1) {
        // 找到最后一个节点即尾结点
        Node *tail = NULL;
        for (tail = *List; tail->next != *List; tail = tail->next);
        insertNode->next = tail->next;
        tail->next = insertNode;
        *List = insertNode;
    } else {
        Node *preNode = *List;
        // 找到插入位置的的前一个节点
        for (int i = 1; preNode->next != *List && i != location-1; preNode = preNode->next,i++);
        insertNode->next = preNode->next;
        preNode->next = insertNode;
    }
}

// 单向循环链表的查询
int FindValue(LinkList L,int  value) {
    int location;
    Node *node = L;
    for (location = 0;  node->next != L; location ++) {
        if (node->data == value) {
            break;
        }
        node = node->next;
    }
    // 超出范围了
    if (node->next == L && node->data != value) {
        return -1;
    }
    return location+1;
}

Status PrinttList (LinkList list) {
    if (list == NULL) return ERROR;
    Node *head = list;
    Node *target = list;
    // 此处开始用指针指向首元节点，默认会打印一次 判断只要不会出现第二次指向首元节点就结束
    do {
        printf("%5d",target->data);
        target = target->next;
    } while (target != head);
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    LinkList L;
    InitList(&L);
    PrinttList(L);


    while (1) {
        int loc;
        printf("输入要删除节点的位置: \n");
        scanf("%d",&loc);
        int location = FindValue(L,loc);
        printf("loc is %d \n",location);
    }
    
//    while (1) {
//        int location;
//        printf("输入要删除节点的位置: \n");
//        scanf("%d",&location);
//        ListData deleteData;
//        DeleteNode(&L, location, &deleteData);
//        printf("删除后的链表是: \n");
//        PrinttList(L);
//        printf("删除的元素结果是: %d\n",deleteData);
//
//
//    }
//    while (1) {
//        int location,number;
//        printf("依次输入插入位置和要插入的数字以空格分开: ");
//        scanf("%d %d",&location,&number);
//        InsertNode(&L, location, number);
//        printf("插入之后的结果是: \n");
//        PrinttList(L);
//    }
    return 0;
}
