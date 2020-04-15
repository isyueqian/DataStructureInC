//
// Created by Lizzy on 2020/2/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERROR 'N'

typedef int Position;
typedef char ElementType;
typedef struct SNode * PtrToSNode;
struct SNode{
    ElementType *Data;
    Position Top;
    int MaxSize;
};
typedef PtrToSNode Stack;

Stack CreateStack(int MaxSize)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(MaxSize*sizeof(ElementType));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

bool IsFull(Stack S)
{
    return (S->Top == S->MaxSize-1);
}

bool Push(Stack S, ElementType X)
{
    if (IsFull(S)) {
        printf("The stack is full.");
        return false;
    } else {
        S->Data[++S->Top] = X;
        return true;
    }
}

bool IsEmpty(Stack S)
{
    return (S->Top == -1);
}

ElementType Pop(Stack S)
{
    if (IsEmpty(S)) {
        printf("The stack is empty.");
        return ERROR;
    } else {
        return (S->Data[S->Top--]);
    }
}

ElementType GetTop(Stack S)
{
    return S->Data[S->Top];
}

char t; // 用于后面记录

bool deal(Stack S)
{
    char c[101];
    bool f = true;
    int i;
    while(gets(c)) {
        if (c[0]=='.' && c[1]=='\0') break;
        for (i=0; c[i]!='\0'; i++) {
            if (c[i] == '/' && c[i + 1] == '*') {
                Push(S, c[i]);
                Push(S, c[i + 1]);
                i++;
            } else if (c[i] == '(' || c[i] == '{' || c[i] == '[') {
                Push(S, c[i]);
            } else if (c[i] == '*' && c[i + 1] == '/') {
                if (!IsEmpty(S) && GetTop(S) == '*') {
                    Pop(S);
                    if (!IsEmpty(S) && GetTop(S) == '/') {
                        Pop(S);
                    } else {
                        f = false;
                        t = c[i];
                        break;
                    }
                } else {
                    f = false;
                    t = c[i];
                    break;
                }
            } else if (c[i] == ')') {
                if (!IsEmpty(S) && GetTop(S) == '(') {
                    Pop(S);
                } else {
                    f = false;
                    t = c[i];
                    break;
                }
            } else if (c[i] == ']') {
                if (!IsEmpty(S) && GetTop(S) == '[') {
                    Pop(S);
                } else {
                    f = false;
                    t = c[i];
                    break;
                }
            } else if (c[i] == '}') {
                if (!IsEmpty(S) && GetTop(S) == '{') {
                    Pop(S);
                } else {
                    f = false;
                    t = c[i];
                    break;
                }
            }
        }
    }
    if (IsEmpty(S) && f) return true;
    else return false;
}

int main()
{
    Stack S;
    S = CreateStack(100);
    if(deal(S))
        printf("YES\n");
    else
    {
        printf("NO\n");
        if(!IsEmpty(S))
        {
            if(GetTop(S)=='(')printf("(-?");
            if(GetTop(S)=='[')printf("[-?");
            if(GetTop(S)=='{')printf("{-?");
            if(GetTop(S)=='*')printf("/*-?");
        }
        else
        {
            if(t==')')printf("?-)");
            if(t==']')printf("?-]");
            if(t=='}')printf("?-}");
            if(t=='*')printf("?-*/");
        }
    }
    system("pause");
    return 0;
}
















