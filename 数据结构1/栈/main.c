//
//  main.c
//  栈
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

typedef struct {
    Data data[MAXSIZE];
    int top;
}Stack;

// 初始化空栈
Status InitStack (Stack *S) {
    S->top = -1;
    return SUCCESS;
}

// 清空栈
Status ClearStack (Stack *S) {
    S->top = -1;
    return SUCCESS;
}

// 判断是否为空栈
Status IsEmpty(Stack S) {
    if (S.top == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// 返回栈长度
int StackLength(Stack s) {
    return s.top+1;
}

// 获取栈顶元素
Status GetStackTop(Stack S,Data *data) {
    if (S.top == -1)return ERROR;
    *data = S.data[S.top];
    return SUCCESS;
}

// 入栈
Status PushData(Stack *S,Data data) {
    if (S->top == MAXSIZE-1) return ERROR;
    int top = S->top+1;
    S->data[top] = data;
    S->top++;
    return SUCCESS;
}

// 出栈
Status Pop(Stack *S,Data *data) {
    if (S->top == -1) return ERROR;
    *data = S->data[S->top];
    S->top--;
    return SUCCESS;
}

// 从栈底到栈顶打印栈
Status PrintStack(Stack S) {
    if (S.top == -1) {
        printf("空栈 \n");
        return ERROR;
    }
    printf("栈中数据是：");
    for (int i = 0; i <= S.top; i ++) {
        printf("%d--",S.data[i]);
    }
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Stack S;
    InitStack(&S);
    for (int i = 0; i < 10; i ++) {
        PushData(&S, i);
    }
    PrintStack(S);
    
    Data data;
    Pop(&S, &data);
    PrintStack(S);
    printf("出栈的数据是： %d \n",data);
    
    GetStackTop(S, &data);
    printf("栈顶的数据是： %d \n",data);
    return 0;
}
