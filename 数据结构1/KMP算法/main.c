//
//  main.c
//  KMP算法
//
//  Created by xingling xu on 2020/4/23.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;        /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

Status ConvertString(char *result,char *string) {
    long len = strlen(string);
    result[0] = len;
    for (int i = 0; i < len; i ++) {
        result[i+1] = string[i];
    }
    return OK;
}

void get_next(char *T,int *next) {
    int i = 0,j=1;
    next[1] = 0;
    while (j < T[0]) {
        if (i == 0 || T[i] == T[j]) {
            i++;
            j++;
            next[j] = i;
        } else {
            i = next[i];
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
//    char *T = (char *)malloc(sizeof(char) * MAXSIZE);
    char T[100];
    ConvertString(T, "abc");
    
    int len = (int)strlen(T);
    int *next = (int *)malloc(sizeof(int)*len);
    get_next(T, next);
    for (int i = 0; i < len; i ++) {
        printf("next is %d \n",next[i]);
    }
    return 0;
}
