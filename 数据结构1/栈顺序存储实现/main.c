//
//  main.c
//  栈顺序存储实现
//
//  Created by xingling xu on 2020/4/10.
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

typedef struct {
    int data[MAXSIZE];
    int top;// 栈顶
} Stack;

Status InitStack(Stack *S) {
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
