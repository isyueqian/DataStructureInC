//
// An application of stack: get the value of expressions
// Created by Lizzy on 2020/1/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXOP 100
#define ERROR -1
#define INFINITY 1e9

typedef int Position;
typedef double ElementType;
typedef enum{num, opr, end} Type; // enumeration

typedef struct SNode * PtrToSNode;
struct SNode {
    ElementType *Data;
    Position Top;
    int MaxSize;
};
typedef PtrToSNode Stack;

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

Type GetOp(const char *Expr, int *start, char *str)
{ /* read the next object(operation or operator) from *start, save it to str*/
    int i=0;
    while((str[0]=Expr[(*start)++])==' ') ; // skip the blank before expression

    while(str[i]!=' ' && str[i]!='\0') {
        str[++i] = Expr[(*start)++];
    }
    if (str[i]=='\0') {
        (*start)--;
    }
    str[i] = '\0';

    Type ret;
    if (i==0) {
        ret = end;
    } else if (isdigit(str[0]) || isdigit(str[1])) {
        ret = num;
    } else {
        ret = opr;
    }
    return ret;
}

ElementType PostfixExp(char *Expr)
{ /* read in the Post fixing Expression and get the value by using GetOp */
    Stack S;
    Type T;
    ElementType Op1, Op2;
    char str[MAXOP];
    int start=0;

    S = CreateStack(MAXOP);

    Op1 = Op2 = 0;
    while((T=GetOp(Expr, &start, str))!=end) { // while it is not end
        if (T==num) {
            Push(S, atof(str));
        } else { // opr
            if (!IsEmpty(S)) {
                Op2 = Pop(S);
            } else {
                Op2 = INFINITY;
            }

            if (!IsEmpty(S)) {
                Op1 = Pop(S);
            } else {
                Op2 = INFINITY;
            }

            switch (str[0]) {
                case '+': Push(S, Op1+Op2); break;
                case '*': Push(S, Op1*Op2); break;
                case '-': Push(S, Op1-Op2); break;
                case '/':
                    if(Op2 != 0.0) {
                        Push(S, Op1/Op2);
                    } else {
                        printf("Illegal denominator.");
                        Op2 = INFINITY;
                    } break;
                default:
                    printf("Unknown operator %s.", str);
                    Op2 = INFINITY;
                    break;
            }

            if (Op2 >= INFINITY) break;
        }
    }

    if (Op2<INFINITY) {
        if (!IsEmpty(S)) {
            Op2 = Pop(S);
        } else {
            Op2 = INFINITY;
        }
    }

    free(S); // free the stack;
    return Op2;
}

int main()
{
    char Expr[MAXOP];
    ElementType f;

    gets(Expr);
    f = PostfixExp(Expr);

    if (f<INFINITY) {
        printf("%.4f\n", f);
    } else {
        printf("Wrong Expression.\n");
    }

    return 0;
}
