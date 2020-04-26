//
//  main.c
//  树结构的链式存储
//
//  Created by xingling xu on 2020/4/26.
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

typedef int Status;

typedef struct Node {
    char data;
    struct Node *leftNode;//  左子树
    struct Node *rightNode;// 右子树
} Node;

typedef Node* BiTree;

int stringIndex = 0;
char *charStr = "ABDH#K###E##CFI###G#J##";
//char *charStr = "ABCD#EFGH#I##";
//---------------------------------------------------------------------
typedef Node* Data;
typedef struct Node1 {
    BiTree data;
    struct Node1 *next;
} Node1;

typedef struct {
    Node1 *front;
    Node1 *rear;
} Queue;

// 初始化队列
Status InitQueue(Queue *Q) {
    Q->front = Q->rear = (Node1 *)malloc(sizeof(Node1));
    if (!Q->front) return ERROR;
    Q->front->next = NULL;
    return OK;
}

// 入队
Status QueueEnter(Queue *Q,Data data) {
    Node1 *node = (Node1 *)malloc(sizeof(Node1));
    if (!node) return ERROR;
    node->data = data;
    node->next = NULL;
    Q->rear->next = node;
    // 修改队尾指针
    Q->rear = node;
    return OK;
}

// 出队
Status QueuePop(Queue *Q,Data *data) {
    if (Q->front == Q->rear) return ERROR;
    Node1 *temp = Q->front->next;
    *data = temp->data;
    Q->front->next = temp->next;
    // 如果只有一个节点，就要移动尾指针
    if (temp == Q->rear) {
        Q->rear = Q->front;
    }
    free(temp);
    return OK;
}

// 获取队头元素
Status GetHead(Queue Q,Data *data) {
    if (Q.front == Q.rear) return ERROR;
    *data = Q.front->next->data;
    return OK;
}

Status IsEmpty(Queue Q) {
    return (Q.rear == Q.front)?TRUE:FALSE;
}

//---------------------------------------------------------------------



void CreateBiTree(BiTree *tree) {
    char ch = charStr[stringIndex];
    stringIndex++;
    if (ch == '#') {
        *tree = NULL;
    } else {
        *tree = (Node *)malloc(sizeof(Node));
        if (!*tree) exit(OVERFLOW);
        (*tree)->data = ch;
        CreateBiTree(&(*tree)->leftNode);
        CreateBiTree(&(*tree)->rightNode);
    }
}

void PreOrder(BiTree Tree) {
    if (Tree == NULL) {
        return;
    }
    printf("%c - ",Tree->data);
    PreOrder(Tree->leftNode);
    PreOrder(Tree->rightNode);
}

void MiddelOrder(BiTree tree) {
    if (tree == NULL) {
        return;
    }
    MiddelOrder(tree->leftNode);
    printf("%c - ",tree->data);
    MiddelOrder(tree->rightNode);
}

void PostOrder(BiTree tree) {
    if (tree == NULL) {
        return;
    }
    PostOrder(tree->leftNode);
    PostOrder(tree->rightNode);
    printf("%c - ",tree->data);
}

void CengOrder(BiTree tree) {
    if (tree == NULL) return;
    Queue q;
    //1.初始化队列q
    InitQueue(&q);
    QueueEnter(&q, tree);
    Data ctree;
    while (!IsEmpty(q)) {
        GetHead(q, &ctree);
        printf("%c - ",ctree->data);
        Data head;
        QueuePop(&q, &head);
        if (head->leftNode) {
            QueueEnter(&q, head->leftNode);
        }
        if (head->rightNode) {
            QueueEnter(&q, head->rightNode);
        }
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    BiTree tree;
    CreateBiTree(&tree);
    PreOrder(tree);
    printf("\n");
    
    MiddelOrder(tree);
    printf("\n");
    
    PostOrder(tree);
    printf("\n");
    
    CengOrder(tree);
    printf("\n");
    return 0;
}
