//
//  main.c
//  双向循环链表
//
//  Created by xingling xu on 2020/4/7.
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
    struct Node *prior;
    ListData data;
    struct Node *next;
} Node;

typedef Node* LinkList;

Status CreatList (LinkList *L, int n) {
    *L = (LinkList)malloc(sizeof(Node));
    if (!*L) return ERROR;
    LinkList list = *L;
    Node *target = list;
    // 自己指向自己
    list->next = list;
    list->prior = list;
    // 新增数据
    for (int i = 1; i <= n; i ++) {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = i;
        temp->next = list;
        list->prior = temp;
        target->next = temp;
        temp->prior = target;
        target = target->next;
    }
    return SUCCESS;
}

Status InsertData(LinkList *L,int location, ListData data) {
    // 找到要插入位置的前一个位置的节点
    Node *target = *L;
    if (!target) return ERROR;
    int i;
    for (i = 1; i < location && target->next != *L; i ++) {
        target = target->next;
    }
    // 超出范围
    if (i < location) return ERROR;
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp) return ERROR;
    temp->data = data;
    temp->next = target->next;
    temp->next->prior = temp;
    target->next = temp;
    temp->prior = target;
    return SUCCESS;
}

Status DeleteData(LinkList *L,int location, ListData *data) {
    if (*L == NULL) return ERROR;
    Node *target = (*L)->next;
    // 如果只剩下首元节点，直接清空*L
    if (target->next == *L) {
        free(*L);
        (*L) = NULL;
        return SUCCESS;
    }
    for (int i = 1; i < location && target->next != *L; i ++) {
        target = target->next;
    }
    target->prior->next = target->next;
    target->next->prior = target->prior;
    *data = target->data;
    free(target);
    return SUCCESS;
}

Status PrintList(LinkList L) {
    if (L == NULL) {
        printf("空链表");
        return ERROR;
    }
    printf("双向循环链表的内容: ");
    Node *target = L->next;
    while (target != L) {
        printf("%d--",target->data);
        target = target->next;
    }
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    LinkList list;
    CreatList(&list, 10);
    printf("初始化带10个数据的双向循环链表的数据是：\n");
    PrintList(list);
    
    InsertData(&list, 3, 44);
    printf("第三个位置插入44后打印：\n");
    PrintList(list);
    
    InsertData(&list, 20, 999);
    printf("第20个位置插入999后打印：\n");
    PrintList(list);
    
    ListData data;
    DeleteData(&list, 3, &data);
    printf("删除第3个节点之后打印：\n");
    PrintList(list);
    printf("删除的数据是：%d \n",data);
    
    return 0;
}
