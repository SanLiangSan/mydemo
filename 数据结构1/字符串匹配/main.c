//
//  main.c
//  字符串匹配
//
//  Created by xingling xu on 2020/4/21.
//  Copyright © 2020 Typeco. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

// BF算法
int indexOf(char *S,char *T) {
    int i = 0,j = 0;
    int lenS = (int)strlen(S);
    int lenT = (int)strlen(T);
    while (i < lenS && j < lenT ) {
        // 比较两个字母若相同则继续比较
        if (S[i] == T[j]) {
            i++;
            j++;
        } else {
            // 找到上一次匹配的首位的下一位
            i = i-j+1;
            // j返回到子串T首位
            j = 0;
        }
    }
    
    if (j == lenT) {
        // 这里+1是为了将index转化为现实生活中的位置
        return i-lenT+1;
    } else {
        return -1;
    }
}

#define d  26 // 进制数

// 即使我们求出了结果，但是为了验证是否冲突加一个验证
int isMatch(char *S, int i, char *P, int m)
{
    int is, ip;
    for(is=i, ip=0; is != m && ip != m; is++, ip++)
        if(S[is] != P[ip])
            return 0;
    return 1;
}

// 计算最高位的幂次方 比如三位子串就是26的平方
int getMaxValue(int Tlength) {
    int value = 1;
    for (int i = 0; i < Tlength-1; i ++) {
        value *= d;
    }
    return value;
}

// RK算法
int RK(char *S, char *T) {
    int slen = (int)strlen(S);
    int tlen = (int)strlen(T);
    
    int hashS = 0;
    int hashT = 0;
    // 分别保存两个字符串的首个哈希值
    for (int i = 0; i < tlen; i++) {
        hashS = hashS*d +(S[i]-'a');
        hashT = hashT*d +(T[i]-'a');
    }
    
    int hValue = getMaxValue(tlen);
    
    for (int i = 0; i <= slen-tlen; i++) {
        // 如果哈希值相等就是找到了
        if (hashS == hashT) {
            // 验证是否真的相同
            if (isMatch(S, i, T, tlen)) {
                return i+1;
            }
        }
        // 更新hashS
        hashS = (hashS- (S[i]-'a')*hValue)*d + (S[i+tlen]-'a');
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int index = RK("abcdex", "ex");
    printf("第一个匹配的位置是 %d \n",index);
    return 0;
}
