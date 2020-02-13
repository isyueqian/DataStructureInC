//
// This is an implementation of Binary Tree.
// Created by Lizzy on 2020/2/13.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode * Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
