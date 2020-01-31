//
// This is an implementation of stack in the format of link list (pop from head).
// Created by Lizzy on 2020/1/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERROR -1

typedef int ElementType;
typedef struct SNode * PtrToSNode;
struct SNode {
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack();
bool IsEmpty(Stack S);
bool Push(Stack S, ElementType X);
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
    PrintStack(S);

    ElementType a1 = Pop(S);
    printf("Pop one = %d\n", a1);
    PrintStack(S);
    ElementType a2 = Pop(S);
    printf("Pop one = %d\n", a2);
    PrintStack(S);

    return 0;
}

void PrintStack(Stack S)
{
    PtrToSNode p=S->Next;
    while(p) {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}

Stack CreateStack()
{   // build an head node pointer
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

bool IsEmpty(Stack S)
{
    return S->Next==NULL;
}

bool Push(Stack S, ElementType X)
{   // It can't be full with the format of link list.
    PtrToSNode p = (PtrToSNode)malloc(sizeof(struct SNode));
    p->Data = X;
    p->Next = S->Next;
    S->Next = p;
    return true;
}

ElementType Pop(Stack S)
{
    ElementType ret;
    if (IsEmpty(S)) {
        printf("The stack is empty.");
        ret = ERROR;
    } else {
        PtrToSNode tmp = S->Next;
        S->Next = tmp->Next;
        ret = tmp->Data;
        free(tmp);
    }
    return ret;
}