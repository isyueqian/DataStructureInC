/*
04-树4 是否同一棵二叉搜索树 (25分)
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0



输出样例:
Yes
No
No
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode * Tree;
struct TreeNode{
    ElementType data;
    Tree Left, Right;
    int flag;
};

Tree MakeTree(int N);
int Judge(Tree T, int N);
void ResetTree(Tree T);
void FreeTree(Tree T);

int main(void)
{
    int N, L, i;
    Tree T;

    scanf("%d", &N);
    while (N) {
        scanf("%d", &L);
        T = MakeTree(N);
        for(i=0; i<L; i++) {
            if(Judge(T, N)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
            ResetTree(T);
        }
        FreeTree(T);
        scanf("%d", &N);
    }
    return 0;
}

Tree NewNode(ElementType Data)
{
    Tree T= (Tree) malloc(sizeof(struct TreeNode));
    T->data = Data;
    T->Left = T->Right = NULL;
    T->flag = 0;
    return T;
}

Tree Insert(Tree T, ElementType Data)
{
    if(!T) {
        T = NewNode(Data);
    } else {
        if (Data > T->data) {
            T->Right = Insert(T->Right, Data);
        } else {
            T->Left = Insert(T->Left, Data);
        }
    }
    return T;
}

Tree MakeTree(int N)
{
    Tree T;
    int i, Data;

    scanf("%d", &Data);
    T = NewNode(Data);
    for(i=1; i<N; i++) {
        scanf("%d", &Data);
        T = Insert(T, Data);
    }
    return T;
}

int check(Tree T, ElementType Data)
{
    if (T->flag) {
        if (Data < T->data) {
            return check(T->Left, Data);
        } else if (Data > T->data) {
            return check(T->Right, Data);
        } else {
            return 0; //Error
        }
    } else {
        if (Data == T->data) {
            T->flag = 1;
            return 1;
        } else {
            return 0;
        }
    }
}

int Judge(Tree T, int N)
{
    int i, Data, flag=0; // for marking the program

    scanf("%d", &Data);
    if(Data != T->data) {
        flag = 1;
    } else {
        T->flag = 1;
    }

    for(i=1; i<N; i++) {
        scanf("%d", &Data);
        if(!flag && !check(T, Data)) {
            flag = 1;
        }
    }

    if (flag) {
        return 0; // Error
    } else {
        return 1;
    }
}

void ResetTree(Tree T)
{
    if(T->Left) {
        ResetTree(T->Left);
    }
    if(T->Right) {
        ResetTree(T->Right);
    }
    T->flag = 0;
}

void FreeTree(Tree T)
{
    if(T->Left) {
        FreeTree(T->Left);
    }
    if(T->Right) {
        FreeTree(T->Right);
    }
    free(T);
}













