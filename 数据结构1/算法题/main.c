//
//  main.c
//  算法题
//
//  Created by xingling xu on 2020/4/15.
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
typedef char Data;

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

Status IsEmpty(Stack S) {
    if (S.top == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
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

// 爬楼梯问题
int StairStep(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else {
        return StairStep(n-1) + StairStep(n-2);
    }
}

// 括号匹配
Status IsCorrect(char *string) {
    Stack S;
    InitStack(&S);
    
    int i = 0;
    char temp = string[0];
    while (temp) {
        printf("string is %c \n",temp);
        if (temp == '[') {
            PushData(&S, '[');
        } else if (temp == '(') {
            PushData(&S, '(');
        } else if (temp == ')') {
            char top;
            GetTop(S, &top);
            if (top == '(') {
                Pop(&S, &top);
            } else {
                PushData(&S, ')');
                // return FALSE;
            }
        } else if (temp == ']') {
            char top;
            GetTop(S, &top);
            if (top == '[') {
                Pop(&S, &top);
            } else {
                PushData(&S, ']');
                // return FALSE;
            }
        }
        i ++;
        temp = string[i];
    }
    
    return IsEmpty(S)?SUCCESS:FALSE;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
//    while (1) {
//        int n;
//        scanf("%d",&n);
//        if (n==0) break;
//        printf("%d 步阶梯共有%d 种走法 \n",n,StairStep(n));
//    }
    
    char *string = "[[(]]([()][()])]";
    Status value = IsCorrect(string);
    if (value == SUCCESS) {
        printf("合法字符串 \n");
    } else {
        printf("非法字符串 \n");
    }
    return 0;
}
