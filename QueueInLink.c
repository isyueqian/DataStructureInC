//
// This is an example of queue with the implementation format of array.
// Created by Lizzy on 2020/1/27.
//
// 这里要注意的最大的不同是链式实现中，初始化将Q->Front和Q->Rear都指向同一个头结点。

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1

typedef int ElementType;
typedef struct Node * PtrToNode;
struct Node{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode Position;

typedef struct QNode * PtrToQNode;
struct QNode{
    Position Front, Rear;
    int MaxSize;
};
typedef PtrToQNode Queue;

bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);
bool IsFull(Queue Q);
bool AddQ(Queue Q, ElementType X);
void PrintQueue(Queue Q);
Queue CreateQueue(int MaxSize);

int main(void)
{
    Queue Q = CreateQueue(10);
    printf("Is Empty = %d\n", IsEmpty(Q));

    AddQ(Q, 2);
    DeleteQ(Q); // 这种实现只有在加入第一个元素后删掉头结点才可使用，疑问：没有头结点的情况下如何入队？

    AddQ(Q, 3);
    AddQ(Q, 4);
    AddQ(Q, 35);
    PrintQueue(Q);


    AddQ(Q, 6);
    ElementType a = DeleteQ(Q);
    printf("The left element is = %d\n", a);
    AddQ(Q, 9);
    ElementType b = DeleteQ(Q);
    printf("The left element is = %d\n", b);
    AddQ(Q, 22);

    PrintQueue(Q);

    return 0;
}

void PrintQueue(Queue Q)
{
    PtrToNode p = Q->Front;
    while (p!=Q->Rear) {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("%d ", p->Data);
    printf("\n");
}

Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue) malloc (sizeof(struct QNode));
    PtrToNode head = (PtrToNode) malloc (sizeof(struct Node));
    Q->Rear = Q->Front = head;
    Q->Front->Next = NULL;

//    Q->Front = (PtrToNode) malloc (sizeof(struct Node));
//    Q->Rear = Q->Front;
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsEmpty(Queue Q)
{
    return Q->Front->Next==NULL; // Q->Front就是第一个放元素的位置
}

ElementType DeleteQ(Queue Q)
{
    ElementType ret;
    if (IsEmpty(Q)) {
        printf("This queue is empty.");
        ret = ERROR;
    } else {
        PtrToNode FrontCell = Q->Front;
        if (Q->Front == Q->Rear) { // 只有一个元素的条件
            Q->Front = Q->Rear = NULL;
        } else {
            Q->Front = Q->Front->Next;
        }
        ret = FrontCell->Data;
        free(FrontCell);
    }
    return ret;
}

bool IsFull(Queue Q)
{
    int cnt=1;
    PtrToNode p=Q->Front;
    while (p!=Q->Rear) {
        p = p->Next;
        cnt++;
    }
    return (cnt==Q->MaxSize);
}

bool AddQ(Queue Q, ElementType X)
{
    bool ret;
    if (IsFull(Q)) {
        printf("This queue is already full.");
        ret = false;
    } else {
        PtrToNode tmp = (PtrToNode) malloc(sizeof(struct Node));
        tmp->Data = X;
        tmp->Next = NULL;

        Q->Rear->Next = tmp;
        Q->Rear = tmp;
        ret = true;
    }
    return ret;
}












