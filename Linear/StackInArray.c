//
// This is an implementation of Stack with the data structure of array.
// Created by Lizzy on 2020/1/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERROR -1

typedef int ElementType;
typedef int Position;
typedef struct SNode * PtrToSNode;
struct SNode {
    ElementType * Data; // a pointer to save the array
    Position Top; // an index for top element
    int MaxSize;
};
typedef PtrToSNode Stack;

Stack CreateStack(int MaxSize);
bool IsFull(Stack S);
bool Push(Stack S, ElementType X);
bool IsEmpty(Stack S);
ElementType Pop(Stack S);
void PrintStack(Stack S);

int main(void)
{
    Stack S = CreateStack(10);
    printf("Is empty = %d\n", IsEmpty(S));
    PrintStack(S);

    Push(S, 2);
    Push(S, 4);
    Push(S, 6);
    Push(S, 8);
    Push(S, 10);
    printf("Is full = %d\n", IsFull(S));
    PrintStack(S);

    ElementType a1 = Pop(S);
    printf("Pop one = %d\n", a1);
    PrintStack(S);
    ElementType a2 = Pop(S);
    printf("Pop one = %d\n", a2);
    PrintStack(S);

    printf("The top = %d\n", S->Top);

    return 0;
}

void PrintStack(Stack S)
{
    for (int i=0; i<=S->Top; i++) {
        printf("%d ", S->Data[i]);
    }
    printf("\n");
}

Stack CreateStack(int MaxSize)
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Data = (ElementType *)malloc(MaxSize* sizeof(ElementType)); // 动态申请数组空间
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

bool IsFull(Stack S)
{
    return S->Top==S->MaxSize-1;
}

bool Push(Stack S, ElementType X)
{
    bool ret;
    if (IsFull(S)) {
        printf("The stack is full.");
        ret = false;
    } else {
        S->Data[++S->Top] = X;
        ret = true;
    }
    return ret;
}

bool IsEmpty(Stack S)
{
    return S->Top==-1;
}

ElementType Pop(Stack S)
{
    ElementType ret;
    if (IsEmpty(S)) {
        printf("The stack is empty.");
        ret = ERROR;
    } else {
        ret = S->Data[S->Top--];
    }
    return ret;
}


