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

Node * CreatList(int n) {
    Node *list = (Node *)malloc(sizeof(Node));
    // 自己指向自己
    list->next = list;
    list->prior = list;
    // 新增数据
    for (int i = 1; i <= n; i ++) {
        
    }
    return list;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
