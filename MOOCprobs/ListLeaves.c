/*
03-树2 List Leaves (25分)
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6



Sample Output:
4 1 5
*/
// 注意从上至下，从左至右即代表层序遍历

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MaxSize 10
#define Tree int
#define ElementType int // no comma here
#define Null -1

struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxSize];

typedef struct TreeNode * PtrToTNode;

Tree BuildTree(struct TreeNode T[]);
void LevelOrderPrintLeaves(struct TreeNode T[], Tree R);
void PreOrderPrintLeaves(struct TreeNode T[], Tree R);

int main(void)
{
    Tree R = BuildTree(T1);

    LevelOrderPrintLeaves(T1, R);
//    PreOrderPrintLeaves(T1, R);

    return 0;
}

Tree BuildTree(struct TreeNode T[])
{
    int N, i, check[MaxSize];
    char tl, tr;
    Tree Root = Null;
    scanf("%d\n", &N);

    if(N) {
        for(i=0; i<N; i++) {
            check[i] = 0;
        }

        for (i=0; i<N; i++) {
            scanf("%c %c\n",&tl, &tr);
            T[i].Element = i;
            if (tl != '-') {
                T[i].Left = tl - '0';
                check[T[i].Left] = 1;
            } else {
                T[i].Left = Null;
            }

            if (tr != '-') {
                T[i].Right = tr - '0';
                check[T[i].Right] = 1;
            } else {
                T[i].Right = Null;
            }
        }

        for (i=0; i<N; i++) {
            if(!check[i]) {
                break;
            }
        }
        Root = i;
    }
    return Root;
}

typedef struct Node * PtrToNode;
struct Node{
    PtrToTNode TN;
    PtrToNode Next;
};
typedef PtrToNode QPosition;

typedef struct QNode * PtrToQNode;
struct QNode{
    QPosition Front, Rear;
};
typedef PtrToQNode Queue;

Queue CreateQueue()
{
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->Front = (QPosition) malloc(sizeof(struct Node));
    Q->Front->Next = NULL;
    Q->Rear = Q->Front;
    return Q;
}

bool IsEmptyQueue(Queue Q)
{
    return Q->Front->Next == NULL;
}

void AddQ(Queue Q, PtrToTNode TN)
{
    PtrToNode tmp = (PtrToNode) malloc(sizeof(struct Node));
    tmp->TN = TN;
    tmp->Next = NULL;
    Q->Rear->Next = tmp;
    Q->Rear = Q->Rear->Next;
}

PtrToTNode DeleteQ(Queue Q)
{
    PtrToTNode ret;
    if (IsEmptyQueue(Q)) {
        ret = NULL;
    } else {
        PtrToNode tmp = Q->Front->Next;
        ret = tmp->TN;
        Q->Front->Next = Q->Front->Next->Next;
        if (!Q->Front->Next) {
            Q->Rear = Q->Front;
        }
        free(tmp);
    }
    return ret;
}


void LevelOrderPrintLeaves(struct TreeNode T[], Tree R)
{
    if(R==Null) return;

    Queue Q = CreateQueue();
    PtrToTNode P;
    AddQ(Q, &T[R]);
    int flag = 1;
    while(!IsEmptyQueue(Q)) {
        P = DeleteQ(Q);
        if (P->Left==Null && P->Right==Null) {
            if (flag) {
                printf("%d", P->Element);
                flag = 0;
            } else {
                printf(" %d", P->Element);
            }
        }
        if (P->Left!=Null) {
            AddQ(Q, &T[P->Left]);
        }
        if (P->Right!=Null) {
            AddQ(Q, &T[P->Right]);
        }
    }
}

void PreOrderPrintLeaves(struct TreeNode T[], Tree R)
{
    if (R!=Null) {
        if (T[R].Left==Null && T[R].Right==Null) {
            printf("%d", T[R].Element);
        }
        PreOrderPrintLeaves(T, T[R].Left);
        PreOrderPrintLeaves(T, T[R].Right);
    }
}

