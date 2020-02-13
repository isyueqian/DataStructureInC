#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MaxSize 100
#define ERROR 0

typedef char ElementType;
typedef int Position;
typedef struct SNode * PtrToSNode;
struct SNode {
    char data[MaxSize];
    Position top;
};
typedef PtrToSNode Stack;

bool IsEmpty(Stack S);
bool IsFull(Stack S);
bool push(Stack S, ElementType X);
ElementType pop(Stack S);

int main(void)
{
    char code[MaxSize];
    char tmp[MaxSize];
    while (1) {
        gets(tmp);
        if (strcmp(tmp, ".") != 0) {
            strcat(code, tmp);
        } else {
            break;
        }
    }
    // 应该一边读一边判断

    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->top = -1;

    int flag = 1;
    char message;
    for (int i=0; code[i]!='\0'; ) {
        if (code[i] == '(') {
            push(S, code[i]);
            i++;
        } else if (code[i] == '[') {
            push(S, code[i]);
            i++;
        } else if (code[i] == '/' && code[i+1] == '*') {
            push(S, code[i]);
            push(S, code[i+1]);
            i += 2;
        } else if (code[i] == ')') {
            message = pop(S);
            if (message != '(') {
                printf("NO\n");
                printf("?-)");
                flag = 0; // 应该最后统一输出
                break;
            }
            i++;

        } else if (code[i] == ']') { // 逻辑混乱，没有抓住共同规律
            message = pop(S);
            if (message != '[') {
                printf("NO\n");
                printf("?-]");
                flag = 0;
                break;
            }
            i++;

        } else if (code[i] == '*' && code[i+1] =='/') {
            message = pop(S); // 不一定能pop时要用逻辑判断
            if (message != '*') {
                printf("NO\n");
                printf("?-*/");
                flag = 0;
                break;
            }
            message = pop(S);
            if (message != '/') {
                printf("NO\n");
                printf("?-*/");
                flag = 0;
                break;
            }
            i+=2;

        } else {
            i++;
        }

    }

    if (flag && IsEmpty(S)) {
        printf("YES\n");
    }
    if (flag && !IsEmpty(S)) {
        printf("NO\n");
        message = pop(S);
        if (message == '(' || message == '[') {
            printf("%c-?", message);
        } else {
            printf("/*-?");
        }
    }
    return 0;
}

bool IsEmpty(Stack S)
{
    return S->top == -1;
}

bool IsFull(Stack S)
{
    return S->top == MaxSize-1;
}

bool push(Stack S, ElementType X)
{
    bool ret;
    if (IsFull(S)) {
//        printf("The stack is full!");
        ret = false;
    } else {
        S->data[++S->top] = X;
        ret = true;
    }
    return ret;
}

ElementType pop(Stack S)
{
    ElementType ret;
    if (IsEmpty(S)) {
//        printf("The stack is empty!");
        ret = ERROR;
    } else {
        ret = S->data[S->top--];
    }
    return ret;
}

/*
 void test()
{
    int i, A[10];
    for (i=0; i<10; i++)
A[i] = i;
}))
.
*/