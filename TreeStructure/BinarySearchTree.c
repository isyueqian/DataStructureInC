/*
输入样例：
10
5 8 6 2 4 1 0 10 9 7
5
6 3 10 0 5
5
5 7 0 10 3



输出样例：
Preorder: 5 2 1 0 4 8 6 7 10 9
6 is found
3 is not found
10 is found
10 is the largest key
0 is found
0 is the smallest key
5 is found
Not Found
Inorder: 1 2 4 6 8 9
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

void InorderTraversal(BinTree BT)
{
    if(BT) {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
}

void PreorderTraversal(BinTree BT)
{
    if(BT) {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

BinTree Insert(BinTree BST, ElementType X)
{
    if(!BST) {
        BST = (BinTree) malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right =NULL;
    } else {
        if(X < BST->Data) {
            BST->Left = Insert(BST->Left, X);
        } else if (X > BST->Data) {
            BST->Right = Insert(BST->Right, X);
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    while (BST) {
        if(X > BST->Data) {
            BST = BST->Right;
        } else if (X < BST->Data) {
            BST = BST->Left;
        } else {
            break;
        }
    }
    return BST;
}

Position FindMin(BinTree BST)
{
    if(!BST) {
        return NULL;
    } if(!BST->Left) {
        return BST;
    } else {
        return FindMin(BST->Left);
    }
}

Position FindMax(BinTree BST)
{
    if(!BST) {
        return NULL;
    } else {
        while (BST->Right) {
            BST = BST->Right;
        }
        return BST;
    }
}

BinTree Delete(BinTree BST, ElementType X)
{
    Position tmp;
    if(!BST) {
        printf("Not Found\n");
    } else {
        if (X < BST->Data) {
            BST->Left = Delete(BST->Left, X);
        } else if (X > BST->Data) {
            BST->Right = Delete(BST->Right, X);
        } else {
            if (BST->Left && BST->Right) {
                tmp = FindMin(BST->Right);
//                tmp = FindMax(BST->Left);
                BST->Data = tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data); // watch out here, not X
            } else {
                tmp = BST;
                if (!BST->Left) { // with right child or no child
                    BST = BST->Right;
                } else { // with left child
                    BST = BST->Left;
                }
                free(tmp);
            }
        }
    }
    return BST;
}