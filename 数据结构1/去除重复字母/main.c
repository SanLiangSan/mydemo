//
//  main.c
//  去除重复字母
//
//  Created by xingling xu on 2020/4/20.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

typedef struct Node {
    int count;
    int exist;
} Node;

char *MinString(char *string) {
    // 边界判断
    if (string == NULL || strlen(string) == 0) return "";
    if (strlen(string) == 1) return string;
    // 用一个数组保存每个字母出现的次数
    int record[26] = {0};
    unsigned long len = strlen(string);
    int top = -1;
    char *stack = (char *)malloc(len*sizeof(char)+1);
    stack = memset(stack, 0, len*sizeof(char)+1);
    for (int i = 0; i < len; i++) {
        record[string[i]-'a']++;
    }
    
    for (int i = 0; i < len; i++) {
        // 判断当前字符是否已经在栈中
        int exist = 0;
        for (int j = 0; j <= top; j ++) {
            if (stack[j] == string[i]) {
                exist = 1;
            }
        }
        
        if (exist == 1) {// 如果存在直接对数组中相应字母数量减一
            record[string[i]-'a']--;
        } else {
            // 如果栈为空或者栈顶小于当前元素直接入栈，并减少数量
            if (top == -1 || stack[top] < string[i]) {
                top++;
                stack[top] = string[i];
                record[string[i]-'a']--;
            } else {
                // 否则一直出栈直到栈顶元素小于当前元素
                while (top>=0 && record[stack[top]-'a'] > 0 && stack[top] > string[i]) {
                    top--;
                }
                // 入栈新元素，并减少数量
                stack[++top] = string[i];
                record[string[i]-'a']--;
            }
        }
    }
    // 字符串末尾补\0
    stack[++top] = '\0';
    return stack;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char *string = "badabasdfk";
    char *min = MinString(string);
    printf("min string is %s \n",min);
    return 0;
}
