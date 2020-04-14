//
//  main.c
//  线性队列
//
//  Created by xingling xu on 2020/4/14.
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

typedef struct Node {
    Data data[MAXSIZE];
    int rear;
    int front;
} Queue;

// 初始化一个空队列
Status InitQueue(Queue *Q) {
    Q->rear = 0;
    Q->rear = 0;
    return SUCCESS;
}

// 清空一个队列
Status ClearQueue(Queue *Q) {
    Q->rear = 0;
    Q->front = 0;
    return SUCCESS;
}

// 是否为空队列
Status IsEmpty(Queue Q) {
    return Q.rear == Q.front ? TRUE:FALSE;
}

// 队列长度
int Length(Queue Q) {
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

// 获取头节点
Status GetHead(Queue Q,Data *data) {
    if (IsEmpty(Q)) return ERROR;
    *data = Q.data[Q.front];
    return SUCCESS;
}

// 入丢列
Status QueueEnter(Queue *Q,Data data) {
    if ((Q->rear+1)%MAXSIZE == Q->front) return ERROR;
    Q->data[Q->rear] = data;
    // rear 指针向后移一位，如果到达最后则转到数组头部
    Q->rear = (Q->rear+1)%MAXSIZE;
    return SUCCESS;
}

// 出队列
Status QueuePop(Queue *Q, Data *data) {
    if (IsEmpty(*Q)) return ERROR;
    *data = Q->data[Q->front];
    // front 同上面出队列的rear一样
    Q->front = (Q->front+1)%MAXSIZE;
    return SUCCESS;
}

// 遍历队列
Status QueueTraverse(Queue Q) {
    if (IsEmpty(Q)) return ERROR;
    int i = Q.front;
    while ((i+Q.front) != Q.rear) {
        printf("%d   ",Q.data[i]);
        i = (i+1)%MAXSIZE;
    }
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    printf("001--顺序队列表示与操作实现\n");
    
    Status j;
    Queue Q;
    int i=0;
    Data data;
    InitQueue(&Q);
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n",IsEmpty(Q));
    
    printf("入队:\n");
    while (i < 10) {
        QueueEnter(&Q, i);
        i++;
    }
    QueueTraverse(Q);
    printf("队列长度为: %d\n",Length(Q));
    printf("现在队列空否？%u(1:空 0:否)\n",IsEmpty(Q));
    printf("出队:\n");
    
    //出队
    QueuePop(&Q, &data );
    printf("出队的元素:%d\n",data);
    QueueTraverse(Q);
    
    //获取队头
    j=GetHead(Q, &data);
    if(j)
        printf("现在队头元素为: %d\n",data);
    ClearQueue(&Q);
    printf("清空队列后, 队列空否？%u(1:空 0:否)\n",IsEmpty(Q));
    return 0;
}
