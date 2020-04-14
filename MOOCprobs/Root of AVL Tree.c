/*
04-树5 Root of AVL Tree (25分)
An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.




Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.
Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤20) which is the total number of keys to be inserted. Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120



Sample Output 1:
70



Sample Input 2:
7
88 70 61 96 120 90 65



Sample Output 2:
88
 */

#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef struct AVLNode * Position;
typedef Position AVLTree;
struct AVLNode {
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(int a, int b)
{
    return a > b ? a: b;
}

int GetHeight(AVLTree A) {
    if (!A) return 0;
    if (!A->Left && !A->Right) return 1;
    if (A->Left && !A->Right) return GetHeight(A->Left) + 1;
    if (!A->Left && A->Right) return GetHeight(A->Right) + 1;
    return Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}


AVLTree Insert(AVLTree T, ElementType X)
{
    if(!T) {
        T = (AVLTree) malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Left = T->Right = NULL;
        T->Height = 1;
    }
    else if (X<T->Data) {
        T->Left = Insert(T->Left, X);
        if(GetHeight(T->Left) - GetHeight(T->Right) == 2) {// need left rotation
            if (X<T->Left->Data) {
                T = SingleLeftRotation(T);
            } else {
                T = DoubleLeftRightRotation(T);
            }
        }
    }
    else if (X>T->Data) {
        T->Right = Insert(T->Right, X);
        if(GetHeight(T->Left) - GetHeight(T->Right) == -2) {// need right rotation
            if (X>T->Right->Data) {
                T = SingleRightRotation(T);
            } else {
                T = DoubleRightLeftRotation(T);
            }
        }
    }
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}

int main(void)
{
    int N;
    ElementType X;
    scanf("%d\n", &N);
    AVLTree T=NULL;

    for (int i=0; i<N; i++) {
        scanf("%d", &X);
        T = Insert(T, X);
    }
    printf("%d", T->Data);

    return 0;
}

