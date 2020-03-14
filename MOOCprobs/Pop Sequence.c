/*
02-线性结构4 Pop Sequence (25分)
Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

Sample Output:
YES
NO
NO
YES
NO
 */



#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#define MAXSIZE 1001
#define ERROR -1

// stack in array
typedef int ElementType;
typedef int SPosition;

typedef struct SNode* PtrToSNode;
struct SNode{
    ElementType Data[MAXSIZE];
    SPosition Top;
    int MaxSize;
};
typedef PtrToSNode Stack;

// stack initialization
Stack initStack(int MaxSize)
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Top = -1; // empty condition
    S->MaxSize = MaxSize;
    return S;
}

// stack isEmpty
bool isEmpyStack(Stack S)
{
    return S->Top == -1;
}

// stack isFull
bool isFullStack(Stack S)
{
    return S->Top == S->MaxSize-1;
}

// stack Pop
ElementType PopStack(Stack S)
{
    ElementType ret;
    if (isEmpyStack(S)) {
        ret = ERROR;
    } else {
        ret = S->Data[S->Top--];
    }
    return ret;
}

// stack Push
bool PushStack(Stack S, ElementType X)
{
    bool ret;
    if (isFullStack(S)) {
        ret = false;
    } else {
        S->Data[++S->Top] = X;
        ret = true;
    }
    return ret;
}

// get the element
ElementType getTopStack(Stack S)
{
    ElementType ret;
    if (isEmpyStack(S)) {
        ret = ERROR;
    } else {
        ret = S->Data[S->Top];
    }
    return ret;
}


// queue in link
typedef struct Node* PtrToNode;
struct Node{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode QPosition;

typedef struct QNode* PtrToQNode;
struct QNode{
    QPosition Front, Rear;
    int MaxSize;
};
typedef PtrToQNode Queue;

// queue initialization
Queue initQueue(int MaxSize)
{
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->MaxSize = MaxSize;
    Q->Front = (QPosition) malloc(sizeof(struct Node));
    Q->Front->Next = NULL;
    Q->Rear = Q->Front; // with empty head node
    return Q;
}

// queue isEmpty
bool isEmptyQueue(Queue Q)
{
    return Q->Front->Next == NULL;
//    return Q->Front == Q->Rear;
}

// queue isFull
bool isFullQueue(Queue Q)
{
    int cnt=0;
    QPosition tmp=Q->Front;
    while(tmp!=Q->Rear) {
        tmp = tmp->Next;
        cnt++;
    }
    return cnt == Q->MaxSize;
}

// queue AddQ
bool AddQ(Queue Q, ElementType X)
{
    bool ret;
    if (isFullQueue(Q)) {
        ret = false;
    } else {
        PtrToNode cell = (PtrToNode) malloc(sizeof(struct Node));
        cell->Data = X;
        cell->Next = NULL;
        Q->Rear->Next = cell;
        Q->Rear = Q->Rear->Next;
        ret = true;
    }
    return ret;
}

// queue DeleteQ
// the most difficult function
ElementType DeleteQ(Queue Q)
{
    ElementType ret;
    if (isEmptyQueue(Q)) {
        ret = ERROR;
    } else {
        ret = Q->Front->Next->Data;
        QPosition tmp = Q->Front->Next;
        Q->Front->Next = Q->Front->Next->Next; // dont delete the head pointer
        if (Q->Front->Next == NULL) {
            Q->Rear = Q->Front;
        }
        free(tmp);
    }
    return ret;
}

// get the element
ElementType getTopQueue(Queue Q)
{
    ElementType ret;
    if (isEmptyQueue(Q)) {
        ret = ERROR;
    } else {
        ret = Q->Front->Next->Data;
    }
    return ret;
}

void PrintQ(Queue Q)
{
    QPosition p=Q->Front->Next;
    while(p!=Q->Rear) {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("%d\n", p->Data);
}


// algorithm to solve the problem
//int main(void)
//{
//    int M, N, K, err;
//    scanf("%d %d %d", &M, &N, &K);
//
//    Queue mainQ, inputQ, subQ;
//    mainQ = initQueue(N);
//    subQ = initQueue(N);
//    Stack S;
//    ElementType tmp;
//
//    for(int j=1; j<=N; j++) {
//        AddQ(mainQ, j);
//    }
//
//    for(int i=0; i<K; i++) {
//        err = 0;
//        inputQ = initQueue(N);
//        S = initStack(M);
//        for(int k=0; k<N; k++){
//            scanf("%d", &tmp);
//            AddQ(inputQ, tmp);
//        }
//
//        while(1) {
//            if (isEmpyStack(S)) {
//                if (isEmptyQueue(inputQ)) {
//                    break;
//                } else {
//                    tmp = DeleteQ(mainQ);
//                    AddQ(subQ, tmp);
//                    PushStack(S, tmp);
//
//                }
//            } else if (getTopStack(S) != getTopQueue(inputQ)) {
//                tmp = DeleteQ(mainQ);
//                if (tmp == ERROR) {
//                    err = 1;
//                    break;
//                } else {
//                    AddQ(subQ, tmp);
//                    if (!PushStack(S, tmp)) {
//                        err = 1;
//                        break;
//                    }
//                }
//            } else if (getTopStack(S) == getTopQueue(inputQ)) {
//                tmp = PopStack(S);
//                DeleteQ(inputQ);
//            }
//        }
//
//        while (!isEmptyQueue(mainQ)) {
//            AddQ(subQ, DeleteQ(mainQ));
//        }
//        while (!isEmptyQueue(subQ)) {
//            AddQ(mainQ, DeleteQ(subQ));
//        }
//
//
//        if (err==1) {
//            printf("NO\n");
//        } else {
//            printf("YES\n");
//        }
//
//        free(inputQ);
//        free(S);
//    }
//
//    return 0;
//}

int main(void)
{
    int M, N, K, err;
    scanf("%d %d %d", &M, &N, &K);
    Queue mainQ, inputQ;
    Stack S;
    ElementType tmp;


    for(int i=0; i<K; i++) {
        err = 0;
        mainQ = initQueue(N);
        inputQ = initQueue(N);
        S = initStack(M);

        for(int j=1; j<=N; j++) {
            AddQ(mainQ, j);
        }

        for(int k=0; k<N; k++){
            scanf("%d", &tmp);
            AddQ(inputQ, tmp);
        }

        while(1) {
            if (isEmpyStack(S)) {
                if (isEmptyQueue(inputQ)) {
                    break;
                } else {
                    tmp = DeleteQ(mainQ);
                    PushStack(S, tmp);
                }

            } else if (getTopStack(S) != getTopQueue(inputQ)) {
                tmp = DeleteQ(mainQ);
                if (tmp == ERROR) {
                    err = 1;
                    break;
                } else {
                    if (!PushStack(S, tmp)) {
                        err = 1;
                        break;
                    }
                }

            } else if (getTopStack(S) == getTopQueue(inputQ)) {
                tmp = PopStack(S);
                DeleteQ(inputQ);
            }
        }


        if (err==1) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }

        free(inputQ);
        free(mainQ);
        free(S);
    }

    return 0;
}