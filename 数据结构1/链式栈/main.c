//
//  main.c
//  链式栈
//
//  Created by xingling xu on 2020/4/12.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef int Data;

// 栈中每个位置的数据
typedef struct Node {
    Data data;
    struct Node *next;
} Node;

// 栈的结构
typedef struct {
    Node *top; // 栈顶节点
    int count; // 栈的数据量
} Stack;

// 创建一个空栈
Status InitStack(Stack *S) {
    S->top = (Node *)malloc(sizeof(Node));
    if (!S->top) return ERROR;
    S->top = NULL;
    S->count = 0;
    return SUCCESS;
}

// 入栈
Status PushData(Stack *S, Data data) {
    if (!S) return ERROR;
    Node *newTop = (Node *)malloc(sizeof(Node));
    newTop->data = data;
    newTop->next = S->top;
    S->top = newTop;
    S->count++;
    return SUCCESS;
}

// 出栈
Status Pop(Stack *S,Data *data) {
    if (!S) return ERROR;
    Node *temp = S->top;
    S->top = temp->next;
    S->count--;
    *data = temp->data;
    free(temp);
    return SUCCESS;
}

// 获取栈顶元素
Status GetTop(Stack S,Data *data) {
    if (S.count == 0) return ERROR;
    *data = S.top->data;
    return SUCCESS;
}

// 清空栈
Status ClearStack(Stack *S) {
    Node *temp = S->top;
    while (temp) {
        Node *target = temp;
        temp = temp->next;
        free(target);
    }
    S->top = NULL;
    S->count = 0;
    return SUCCESS;
}

// 从栈顶到栈底打印
Status PrintStack(Stack S) {
    if (S.count <= 0) return ERROR;
    printf("栈的数据从顶到底是：");
    Node *temp = S.top;
    while (temp) {
        printf("%d - ",temp->data);
        temp = temp->next;
    }
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Stack S;
    InitStack(&S);
    if (InitStack(&S) == SUCCESS) {
        for (int i = 1; i < 10; i++) {
            PushData(&S, i);
        }
    }
    PrintStack(S);
    
    Data data;
    Pop(&S, &data);
    PrintStack(S);
    printf("出栈的元素是: %d \n",data);
    
    GetTop(S, &data);
    printf("栈顶的元素是: %d \n",data);
    return 0;
}
