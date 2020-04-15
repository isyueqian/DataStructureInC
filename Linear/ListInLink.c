//
// List in the data structure of link.
// Created by Lizzy on 2020/1/22.
//
// 链表形式的List，如果设置空的头结点可以方便插入和删除，但是在按照第K个查找，和求长中都要注意去掉空结点。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1

typedef int ElementType;
typedef struct LNode* PtrToNode;
struct LNode {
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode Position; // here position is the pointer of node
typedef PtrToNode List;

int length(List L);
ElementType FindKth(List L, int K);
Position Find(List L, ElementType X);
List Insert(List L, ElementType X, int i);
bool Insert2(List L, ElementType X, int i); // better
bool Delete(List L, int i);
List MakeEmpty();
void PrintList(List L);

int main(void)
{
    List L=MakeEmpty();
    Insert2(L, 40, 1);
    Insert2(L, 5, 2);
    Insert2(L, 55, 3);
    Insert2(L, 18, 4);
    Insert2(L, 23, 3);
    Insert2(L, 34, 2);
    PrintList(L);

    Delete(L, 2);
    PrintList(L);

    printf("index of 55 = %p\n", Find(L, 55));
    printf("check index of 55 = %d\n", Find(L, 55)->Data);
    printf("num of the third = %d\n", FindKth(L, 4));
    printf("length = %d\n", length(L));
    ElementType x = FindKth(L, 3);
    printf("Element = %d\n", x);

    return 0;
}

void PrintList(List L)
{
    Position p=L;
    while(p) {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}

List MakeEmpty()
{
    List L;
    L = (Position)malloc(sizeof(struct LNode));
    L->Data = 0;
    L->Next = NULL;
    return L;

}

int length(List L)
{
    int ret=0;
    Position p=L;
    while(p) {
        ret++;
        p = p->Next;
    }
    return ret-1;
}

ElementType FindKth(List L, int K)
{
    // consider the possibility that K is beyond the link list
    Position p=L;
    ElementType ret;
    int cnt=1;
    while(p && cnt<K+1) {
        p = p->Next;
        cnt++; // keep the synchronization of p and cnt
    }
    if (cnt==K+1 && p) {
        ret = p->Data;
    } else {
        ret = ERROR;
    }
    return ret;
}

Position Find(List L, ElementType X)
{
    Position p=L;
    while (p && p->Data!=X) {
        p = p->Next;
    }
    return p; // if X is not found, then return NULL
}

List Insert(List L, ElementType X, int i)
{
    // consider the possibility of head node insertion
    Position pre, tmp;
    Position ret;
    tmp = (Position) malloc (sizeof(struct LNode));
    tmp->Data = X;
    tmp->Next = NULL;

    if (i==1) { // 1. head node insertion
        tmp->Next = L;
        ret = tmp;
    } else {
        pre = L;
        int cnt=1;
        while(pre && cnt<i-1) { // 2. different situation
            pre = pre->Next;
            cnt++;
        }
        if (pre==NULL || cnt!=i-1) { // 3. illegal case discrimination
            printf("Illegal insertion position.");
            free(tmp);
            ret = NULL; // **not a very good insertion, make a failure
        } else {
            tmp->Next = pre->Next; // simple insertion
            pre->Next = tmp;
            ret = L;
        }

    }
    return ret;
}

// to make sure head node won't change
bool Insert2(List L, ElementType X, int i)
{
    Position tmp, pre;
    int cnt=0; // a default head node
    bool ret;

    pre=L;
    while (pre && cnt<i-1) {
        pre = pre->Next;
        cnt++;
    }
    if (pre==NULL || cnt!=i-1) {
        printf("Illegal insertion position.");
        ret = false;
    } else {
        tmp = (Position)malloc(sizeof(struct LNode));
        tmp->Data = X;
        tmp->Next = pre->Next;
        pre->Next = tmp;
        ret = true;
    }
    return ret;
}

bool Delete(List L, int i)
{
    bool ret;
    int cnt=0;
    Position pre=L, tmp;

    while(pre && cnt<i-1) {
        pre = pre->Next;
        cnt++;
    }
    if (pre==NULL || cnt!=i-1 || pre->Next==NULL) {
        printf("Illegal deletion position.");
        ret = false;
    } else {
        tmp = pre->Next;
        pre->Next = tmp->Next;
        free(tmp);
        ret = true;
    }
    return ret;
}
