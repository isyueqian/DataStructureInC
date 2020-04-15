//
// List in the data structure of array
// Created by Lizzy on 2020/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10
#define ERROR -1

typedef int Position;
typedef int ElementType;
typedef struct LNode* PtrToLNode;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last;
};
typedef PtrToLNode List; // List is a pointer to the first element of the array

List MakeEmpty();
Position Find(List L, ElementType X);
bool Insert(List L, ElementType X, int i);
bool Delete(List L, int i);
ElementType FindKth(int K, List L);
int Length(List L);
void PrintList(List L);


int main(void) {

    List L = MakeEmpty();
    Insert(L, 40, 1);
    Insert(L, 5, 2);
    Insert(L, 55, 3);
    Insert(L, 18, 4);
    Insert(L, 23, 3);
    Insert(L, 34, 2);
    PrintList(L);

    Delete(L, 2);
    PrintList(L);

    printf("index of 55 = %d\n", Find(L, 55));
    printf("index of 100 = %d\n", Find(L, 100));
    printf("length = %d\n", Length(L));
    ElementType x = FindKth(3, L);
    printf("Element = %d\n", x);

    return 0;
}

void PrintList(List L) {
    Position i;
    for (i=0; i<=L->Last; i++) {
        printf("%d ", L->Data[i]);
    }
    printf("\n");
}

List MakeEmpty()
{
    List L;
    L = (List) malloc (sizeof(struct LNode));
    L->Last = -1;
    return L;
}

Position Find(List L, ElementType X) {
    Position i=0;
    while (L->Data[i]!=X && i<=L->Last) {
        i++;
    }
    Position ret;
    if (i>L->Last) {
        ret = ERROR;
    } else {
        ret = i;
    }
    return ret;
    // (1+2+3+...+n)/n = (1+n)/2 - time complexity
}

bool Insert(List L, ElementType X, int i)
{
    // i - make X the i-th object
    Position j;
    bool ret;
    if (L->Last==MAXSIZE-1) {
        printf("Full list. No insertion.");
        ret = false;
    } else if (i<1 || i>L->Last+2) {
        printf("Illegal position.");
        ret = false;
    } else {
        for (j=L->Last; j>=i-1; j--) {
            L->Data[j+1] = L->Data[j];
        }
        L->Data[i-1] = X;
        L->Last++;
        ret = true;
    }
    return ret;
    // (0+1+2+...+n)/(n+1) = n/2 - time complexity
}

bool Delete(List L, int i)
{
    // i - delete the i-th object
    bool ret;
    Position j;
    if (L->Last==-1) {
        printf("Empty list.");
        ret = false;
    } else if (i<1 || i>L->Last+1) {
        printf("Illegal position.");
        ret = false;
    } else {
        for (j=i; j<=L->Last; j++) {
            L->Data[j-1] = L->Data[j];
        }
        L->Last--;
        ret = true;
    }
    return ret;
    // (0 + 1 + ... + n-1)/n = (n-1)/2
}

ElementType FindKth(int K, List L)
{
    ElementType ret;
    if (K<1 || K>L->Last+1) {
        printf("Empty list or illegal position.");
        ret = ERROR;
    } else {
        ret = L->Data[K-1];
    }
    return ret;
}

int Length(List L)
{
    return L->Last+1;
}

