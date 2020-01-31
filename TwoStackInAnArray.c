//
// This is an implementation of two stacks by using only one array.
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
    ElementType * Data;
    Position Top1;
    Position Top2;
    int MaxSize; // to restrict the size of array
};
typedef PtrToSNode Stack;

Stack CreateStack(int MaxSize);
bool Push(Stack S, ElementType X, int Tag);
ElementType Pop(Stack S, int Tag);
void PrintStack(Stack S);

int main(void)
{
    Stack S = CreateStack(20);
    PrintStack(S);

    Push(S, 2, 1);
    Push(S, 3, 2);
    Push(S, 4, 1);
    Push(S, 5, 2);
    Push(S, 6, 1);
    Push(S, 7, 2);
    Push(S, 8, 1);
    Push(S, 10, 1);
    PrintStack(S);

    int a1 = Pop(S, 1);
    printf("Pop one = %d\n", a1);
    PrintStack(S);
    int a2 = Pop(S, 2);
    printf("Pop one = %d\n", a2);
    PrintStack(S);

    printf("The top1 = %d\n", S->Top1);
    printf("The top2 = %d\n", S->Top2); // there is a lot of empty in between.

    return 0;
}

void PrintStack(Stack S) {
    int i,j;
    for (i=0; i<=S->Top1; i++) {
        printf("%d ", S->Data[i]);
    }
    printf("\t");
    for (j=S->MaxSize-1; j>=S->Top2; j--) {
        printf("%d ", S->Data[j]);
    }
    printf("\n");
}

Stack CreateStack(int MaxSize)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(sizeof(ElementType)*MaxSize);
    S->MaxSize = MaxSize;
    S->Top1=-1;
    S->Top2=MaxSize; // empty
    return S;
}

bool Push(Stack S, ElementType X, int Tag)
{ // tag is to differentiate stack 1 and stack 2
    bool ret;
    if (S->Top2-S->Top1==1) {
        printf("The stacks are full.");
        ret = false;
    } else {
        if (Tag==1) {
            S->Data[++S->Top1] = X;
        }
        if (Tag==2) {
            S->Data[--S->Top2] = X;
        }
        ret = true;
    }
    return ret;
}

ElementType Pop(Stack S, int Tag)
{
    ElementType ret=0;
    if (Tag==1) {
        if (S->Top1==-1) {
            printf("The stack 1 is empty.");
            ret = ERROR;
        } else {
            ret = S->Data[S->Top1--];
        }
    } else if (Tag==2) {
        if (S->Top2==S->MaxSize) {
            printf("The stack 2 is empty.");
            ret = ERROR;
        } else {
            ret = S->Data[S->Top2++];
        }
    }
    return ret;
}
