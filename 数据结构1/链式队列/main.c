//
//  main.c
//  链式队列
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
    Data data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

// 初始化队列
Status InitQueue(Queue *Q) {
    Q->front = Q->rear = (Node *)malloc(sizeof(Node));
    if (!Q->front) return ERROR;
    Q->front->next = NULL;
    return SUCCESS;
}

// 销毁队列
Status DestroyQueue(Queue *Q) {
    // 遍历链表进行销毁
    while (Q->front) {
        Node *temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    return SUCCESS;
}

// 将队列置空
Status ClearQueue(Queue *Q) {
    Node *target = Q->front->next;
    while (target) {
        Node *temp = target;
        target = target->next;
        free(temp);
    }
    Q->front->next = Q->rear->next = NULL;
    return SUCCESS;
}

// 判断队列是否为空
Status IsEmpty(Queue Q) {
    return (Q.rear == Q.front)?TRUE:FALSE;
}

// 获取队列的长度
int GetLength(Queue Q) {
    Node *target = Q.front->next;
    int i=0;
    while (target) {
        i++;
        target = target->next;
    }
    return i;
}

// 入队
Status QueueEnter(Queue *Q,Data data) {
    Node *node = (Node *)malloc(sizeof(node));
    if (!node) return ERROR;
    node->data = data;
    node->next = NULL;
    Q->rear->next = node;
    // 修改队尾指针
    Q->rear = node;
    return SUCCESS;
}

// 出队
Status QueuePop(Queue *Q,Data *data) {
    if (Q->front == Q->rear) return ERROR;
    Node *temp = Q->front->next;
    *data = temp->data;
    Q->front->next = temp->next;
    // 如果只有一个节点，就要移动尾指针
    if (temp == Q->rear) {
        Q->rear = Q->front;
    }
    free(temp);
    return SUCCESS;
}

// 获取队头元素
Status GetHead(Queue Q,Data *data) {
    if (Q.front == Q.rear) return ERROR;
    *data = Q.front->next->data;
    return SUCCESS;
}

// 遍历队列
Status QueueTraverse(Queue Q) {
    Node *target = Q.front->next;
    printf("打印队列是：");
    while (target) {
        printf("%d ",target->data);
        target = target->next;
    }
    printf("\n");
    return SUCCESS;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("链队列的表示与操作!\n");
    
    Status iStatus;
    Data d;
    Queue q;
    
    //1.初始化队列q
    iStatus = InitQueue(&q);
    
    //2. 判断是否创建成
    if (iStatus) {
        printf("成功地构造了一个空队列\n");
    }
    
    //3.判断队列是否为空
    printf("是否为空队列?%d (1:是 0:否)\n",IsEmpty(q));
    
    //4.获取队列的长度
    printf("队列的长度为%d\n",GetLength(q));
    
    //5.插入元素到队列中
    QueueEnter(&q, -3);
    QueueEnter(&q, 6);
    QueueEnter(&q, 12);
    
    printf("队列的长度为%d\n",GetLength(q));
    printf("是否为空队列?%d (1:是 0:否)\n",IsEmpty(q));
    
    //6.遍历队列
    printf("队列中的元素如下:\n");
    QueueTraverse(q);
    
    //7.获取队列头元素
    iStatus = GetHead(q, &d);
    if (iStatus == SUCCESS) {
        printf("队头元素是:%d\n",d);
    }
    
    //8.删除队头元素
    iStatus = QueuePop(&q, &d);
    if (iStatus == SUCCESS) {
        printf("删除了的队头元素为:%d\n",d);
    }
    
    //9.获取队头元素
    iStatus = GetHead(q, &d);
    if (iStatus == SUCCESS) {
        printf("新的队头元素为:%d\n",d);
    }
    
    //10.清空队列
    ClearQueue(&q);
    
    //11.销毁队列
    DestroyQueue(&q);
    
    
    
    return 0;
}
