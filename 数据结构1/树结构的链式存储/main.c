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

int stringIndex = 0;
char *charStr = "ABDH#K###E##CFI###G#J##";
//char *charStr = "ABCD#EFGH#I##";

typedef struct Node {
    char data;
    struct Node *leftNode;//  左子树
    struct Node *rightNode;// 右子树
} Node;

typedef Node* BiTree;


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
    return 0;
}
