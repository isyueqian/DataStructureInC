/*
03-树3 Tree Traversals Again (25分)
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.


Figure 1
Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop



Sample Output:
3 4 2 6 5 1
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 30
#define ERROR -1

int pre[MAXN], in[MAXN], post[MAXN];

typedef int ElementType;
typedef struct SNode * PtrToSNode;
struct SNode{
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack()
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Data = 0; // empty head node
    S->Next = NULL;
    return S;
}

bool IsEmptyStack(Stack S)
{
    return S->Next==NULL;
}

void Push(Stack S, ElementType X)
{
    PtrToSNode tmp = (PtrToSNode) malloc(sizeof(struct SNode));
    tmp->Data = X;
    tmp->Next = S->Next;
    S->Next = tmp;
}

ElementType Pop(Stack S)
{
    ElementType ret;
    if (IsEmptyStack(S)) {
        ret = ERROR;
    } else {
        PtrToSNode tmp = S->Next;
        ret = tmp->Data;
        S->Next = S->Next->Next;
        free(tmp);
    }
    return ret;
}

int GetNum(char input[])
{
    int ret=0, tmp;
    for(int i=0; i<strlen(input); i++) {
        if (input[i]>='0' && input[i]<='9') {
            tmp = input[i] - '0';
            ret = ret*10 + tmp;
        }
    }
    return ret;
}

void Solve(int preL, int inL, int postL, int N)
{ // 核心思想：每一次递归唯一能确定的是Root
    int root, i, L, R;
    if (N==0) return;
    if (N==1) {
        post[postL] = pre[preL];
    }

    root = pre[preL];
    post[postL+N-1] = root; // is it necessary? yes, for get the root for each recursion.

    for(i=0; i<N; i++) {
        if (in[inL+i] == root) {
            break;
        }
    }
    L = i;
    R = N - L - 1;

    Solve(preL+1, inL, postL, L);

    Solve(preL+L+1, inL+L+1, postL+L, R);
}

void PrintPost(int N)  // what is like for empty tree? -> \n
{
    int i;
    for(i=0; i<N; i++) {
        if (i==0) {
            printf("%d", post[i]);
        } else {
            printf(" %d", post[i]);
        }
    }
    printf("\n");
}

int main(void)
{
    int preCount=0, inCount=0, num;
    char input[20] = "\0";
    int N;
    scanf("%d\n", &N);
    Stack S = CreateStack();

    for(int i=0; i<2*N; i++) {
        gets(input);
        if (input[1] == 'u') {
            num = GetNum(input);
            Push(S, num);
            pre[preCount] = num;
            preCount++;
        } else if (input[1] == 'o') {
            num = Pop(S);
            if (num != ERROR) {
                in[inCount] = num;
                inCount++;
            }
        }
    }
    Solve(0, 0, 0, N);
    PrintPost(N);

    return 0;
}










