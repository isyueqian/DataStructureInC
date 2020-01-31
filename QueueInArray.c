//
// This is an example of queue with the implementation format of array.
// Created by Lizzy on 2020/1/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERROR -1;

typedef int ElementType;
typedef int Position;
typedef struct QNode * PtrToQNode;
struct QNode{
    ElementType * Data; // the array
    Position Front, Rear;
    int MaxSize;
};
typedef PtrToQNode Queue;

void PrintQueue(Queue Q);
Queue CreateQueue(int MaxSize);
bool IsFull(Queue Q);
bool AddQ(Queue Q, ElementType X);
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);

int main(void)
{
    Queue Q = CreateQueue(10);
    printf("Is Empty = %d\n", IsEmpty(Q));
    AddQ(Q, 2);
    AddQ(Q, 3);
    AddQ(Q, 4);
    AddQ(Q, 35);
    PrintQueue(Q);
    printf("Is Full = %d\n", IsFull(Q));

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
    for (int i=Q->Front+1; i<=Q->Rear; i++) {
        printf("%d ", Q->Data[i]);
    }
    printf("\n");
}

Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->Data = (ElementType *) malloc(sizeof(ElementType)*MaxSize);
    Q->Front = Q->Rear = 0; // the condition of a empty queue
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsFull(Queue Q)
{
    return (Q->Rear+1)%Q->MaxSize == Q->Front;
}

bool AddQ(Queue Q, ElementType X)
{
    bool ret;
    if (IsFull(Q)) {
        printf("This queue is already full.");
        ret = false;
    } else {
        Q->Rear = (Q->Rear+1) % Q->MaxSize;
        Q->Data[Q->Rear] = X;
        ret = true;
    }
    return ret;
}

bool IsEmpty(Queue Q)
{
    return Q->Front == Q->Rear;
}

ElementType DeleteQ(Queue Q)
{
    ElementType ret;
    if (IsEmpty(Q)) {
        printf("This queue is empty.");
        ret = ERROR;
    } else {
        Q->Front = (Q->Front+1) % Q->MaxSize;
        ret = Q->Data[Q->Front]; // front并不是指向第一个元素，而是更前面一个
    }
    return ret;
}


