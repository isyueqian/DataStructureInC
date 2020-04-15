//
// This is an implementation of Binary Tree.
// Created by Lizzy on 2020/2/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 10
#define NoInfo 0

// Tree
typedef int ElementType;
typedef struct TNode * Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

// Stack
typedef struct SNode * PtrToSNode;
struct SNode{
    BinTree Nodes[MaxSize];
    int Top;
};
typedef PtrToSNode Stack;


Stack CreateStack()
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Top = -1;
    return S;
}

bool IsEmptyStack(Stack S)
{
    return S->Top == -1;
}


BinTree Pop(Stack S)
{
    BinTree ret;
    if(IsEmptyStack(S)) {
        ret = NULL;
    } else {
        ret = S->Nodes[S->Top--];
    }
    return ret;
}

bool Push(Stack S, BinTree BT)
{
    bool ret;
    if(S->Top == MaxSize-1) {
        ret = false;
    } else {
        S->Nodes[++S->Top] = BT;
        ret = true;
    }
    return ret;
}

// Queue
typedef struct Node * PtrToNode;
struct Node{
    BinTree Data;
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

bool IsEmtpyQueue(Queue Q)
{
    return Q->Front->Next == NULL;
}

void AddQ(Queue Q, BinTree BT)
{
    PtrToNode p = (PtrToNode) malloc(sizeof(struct Node));
    p->Data = BT;
    p->Next = NULL;
    Q->Rear->Next = p;
    Q->Rear = Q->Rear->Next;
}

BinTree DeleteQ(Queue Q)
{
    BinTree ret;
    if (IsEmtpyQueue(Q)) {
        ret = NULL;
    } else {
        PtrToNode tmp = Q->Front->Next;
        ret = tmp->Data;

        Q->Front->Next = Q->Front->Next->Next;
        if(Q->Front->Next==NULL) {
            Q->Rear = Q->Front;
        }
        free(tmp);
    }
    return ret;
}

// the function declarations
void InOrderTraversal(BinTree BT);
void PreOrderTraversal(BinTree BT);
void PostOrderTraversal(BinTree BT);

void InOrderTraversalStack(BinTree BT);
void PreOrderTraversalStack(BinTree BT);
void PostOrderTraversalStack(BinTree BT);

void LevelOrderTraversal(BinTree BT);
BinTree CreateBinTree();
void PreOrderPrintLeaves(BinTree BT);
int GetHeight(BinTree BT);


// main function
int main(void)
{
    BinTree BT;
    BT = CreateBinTree();

    InOrderTraversal(BT);
    printf("\n");
    InOrderTraversalStack(BT);
    printf("\n");

    PreOrderTraversal(BT);
    printf("\n");
    PreOrderTraversalStack(BT);
    printf("\n");

    PostOrderTraversal(BT);
    printf("\n");
    PostOrderTraversalStack(BT);
    printf("\n");

    LevelOrderTraversal(BT);
    printf("\n");
    PreOrderPrintLeaves(BT);
    printf("\n");
    GetHeight(BT);

    return 0;
}

// input:
// 1 2 3 5 7 4 6 6 0 0 0 2 0 9 8 0 0 0 0 0 0 0 0
// output:
//65271243968
//65271243968
//12567342698
//12567342698
//65722498631
//65722498631
//12357466298
//67298


// build a tree
BinTree CreateBinTree()
{
    ElementType Data;
    BinTree BT, T;
    Queue Q = CreateQueue();
    int cnt = 1;

    scanf("%d", &Data);
    if (Data != NoInfo) {
        BT = (BinTree) malloc(sizeof(struct TNode));
        BT->Data = Data;
        BT->Left = BT->Right = NULL;
        AddQ(Q, BT);
    } else {
        return NULL;
    }

    while (!IsEmtpyQueue(Q)) {
        T = DeleteQ(Q);

        scanf("%d", &Data);
        if (Data == NoInfo) {
            T->Left = NULL;
        } else {
            T->Left = (BinTree) malloc(sizeof(struct TNode));
            T->Left->Data = Data;
            T->Left->Left = T->Left->Right = NULL;
            AddQ(Q, T->Left);
        }

        scanf("%d", &Data);
        if (Data == NoInfo) {
            T->Right = NULL;
        } else {
            T->Right = (BinTree) malloc(sizeof(struct TNode));
            T->Right->Data = Data;
            T->Right->Left = T->Right->Right = NULL;
            AddQ(Q, T->Right);
        }
    }
    return BT;
}


// traverse the tree in recurrence version
void InOrderTraversal(BinTree BT)
{
    if(BT) {
        InOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        InOrderTraversal(BT->Right);
    }
}

void PreOrderTraversal(BinTree BT)
{
    if(BT) {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}

void PostOrderTraversal(BinTree BT)
{
    if(BT) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }

}

// traverse the tree  with a stack
void InOrderTraversalStack(BinTree BT)
{
    BinTree T=BT;
    Stack S = CreateStack();

    while (T || !IsEmptyStack(S)) {
        while (T) {
            Push(S, T);
            T = T->Left;
        }
        T = Pop(S);
        printf("%d", T->Data);
        T = T->Right;
    }
}

void PreOrderTraversalStack(BinTree BT)
{
    BinTree T=BT;
    Stack S = CreateStack();

    while (T || !IsEmptyStack(S)) {
        while (T) {
            Push(S, T);
            printf("%d", T->Data); // print while first meeting
            T = T->Left;
        }
        T = Pop(S);
        T = T->Right;
    }
}


void PostOrderTraversalStack(BinTree BT)
{
    BinTree T=BT, P=NULL; // P represents that last visited node
    Stack S = CreateStack();

    while (T || !IsEmptyStack(S)) {
        while (T) {
            Push(S, T);
            T = T->Left;
        }
        if(!IsEmptyStack(S)) {
            T = Pop(S);
            if (T->Right == P || T->Right == NULL) {
                printf("%d", T->Data); // print while last meeting
                P = T;
                T = NULL;
            } else {
                Push(S, T);
                T = T->Right;
                }
        }
    }
}


void LevelOrderTraversal(BinTree BT)
{
    Queue Q = CreateQueue();
    BinTree T;

    if(!BT) return;

    AddQ(Q, BT);
    while (!IsEmtpyQueue(Q)) {
        T = DeleteQ(Q);
        printf("%d", T->Data);
        if(T->Left) {
            AddQ(Q, T->Left);
        }
        if(T->Right) {
            AddQ(Q, T->Right);
        }
    }
}

void PreOrderPrintLeaves(BinTree BT)
{
    if(BT) {
        if (!BT->Left && !BT->Right) { // a leave
            printf("%d", BT->Data);
        }
        PreOrderPrintLeaves(BT->Left);
        PreOrderPrintLeaves(BT->Right);
    }
}

int GetHeight(BinTree BT) // by using the recurrence
{
    int HL, HR, HMax;
    if(BT) {
        HL = GetHeight(BT->Left);
        HR = GetHeight(BT->Right);
        HMax = HL > HR ? HL:HR;
        return HMax + 1;
    } else {
        return 0;
    }
}
