//
//  main.c
//  双向链表
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

// 初始化
Node * InitList(int total)  {
    //创建头节点 0x000000010064a390
    Node *list = (Node *)malloc(sizeof(Node));
    if (list == NULL) return ERROR;
    list->prior = NULL;
    list->next = NULL;
    list->data = -1;
    
    Node *target = list;
    Node *temp;
    for (int i = 1; i <= total; i ++) {
        temp = (Node *)malloc(sizeof(Node));
        temp->data = i;
        temp->prior = target;
        temp->next = NULL;
        target->next = temp;
        target = target->next;
    }
    return list;
}

// 打印链表
void PrintList (Node *list) {
    if (list == NULL) {
        printf("啥都没有\n");
        return;
    }
    Node *target = list->next;
    if (target == NULL) {
        printf("链表为空 \n");
        return;
    }
    while (target) {
        printf("%d - ",target->data);
        target = target->next;
    }
    printf("\n");
}

// 指定位置插入节点
Status InserListData(Node **list,int location, ListData data) {
    Node *target = *list;
    int i ;
    // 找到要插入的前一个节点
    for (i = 1; i < location && target; i ++) {
        target = target->next;
    }
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = target->next;
    temp->prior = target;
    target->next = temp;
    temp->next->prior = temp;
    return SUCCESS;
}

// 删除指定位置的节点
Status DeleteData(Node **list,int location, ListData *data) {
    if (location <= 0) return ERROR;
    Node *target = *list;
    // 找到要删除的节点
    int i;
    for (i = 0; i < location && target != NULL; i ++) {
        target = target->next;
    }
    if (i > location || target == NULL) {
        return ERROR;
    }
    target->prior->next = target->next;
    if (target->next != NULL) {
        target->next->prior = target->prior;
    }
    *data = target->data;
    free(target);
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    Node *list = InitList(3);
    printf("打印双向链表: \n");
    PrintList(list);
    InserListData(&list,2,998);
    printf("打印双向链表: \n");
    PrintList(list);
    
    ListData data;
    Status status = DeleteData(&list, 2,&data);
    printf("打印双向链表: \n");
    PrintList(list);
    if (status == SUCCESS) {
        printf("被删除的数字是: %d\n",data);
    }
    return 0;
}
