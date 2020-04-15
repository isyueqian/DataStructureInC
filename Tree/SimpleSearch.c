//
// This is an implementation of simple search algorithms: sequential search and binary search.
// Created by Lizzy on 2020/2/13.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define NotFound 0

typedef int Position;
typedef int ElementType;
typedef struct LNode * PtrToLNode;
struct LNode{
    ElementType data[MAX_SIZE];
    Position Last;
};
typedef PtrToLNode List;

Position SequentialSearch(List Tb1, ElementType K);
Position BinarySearch(List Tb1, ElementType K);

int main(void)
{
    int N;
    scanf("%d", &N);
    List Tb1 = (List) malloc(sizeof(struct LNode));
    Tb1->Last = N;
    for (int i=1; i<N+1; i++) {
        scanf("%d", &Tb1->data[i]);
    }
    int K;
    scanf("%d", &K);

    printf("Result of sequential search: %d\n", SequentialSearch(Tb1, K));
    printf("Result of binary search: %d\n", BinarySearch(Tb1, K));

    return 0;
}

Position SequentialSearch(List Tb1, ElementType K)
{
    Position i;
    Tb1->data[0] = K; // 建立哨兵，然后无需再担心边界情况
    for(i=Tb1->Last; Tb1->data[i]!=K; i--);
    return i; // 如果没找到，返回0
}

Position BinarySearch(List Tb1, ElementType K)
{
    Position i;
    Position left=1, right=Tb1->Last, middle=left;

    while (left<=right) {
        middle = (left + right) / 2;
        if (K < Tb1->data[middle]) {
            right = middle - 1;
        } else if (K > Tb1->data[middle]) {
            left = middle + 1;
        } else {
            break;
        }
    }
    if (left<=right) {
        i = middle;
    } else {
        i = NotFound;
    }
    return i;
}

// 注意：在建立哨兵的算法中，数组下标的从1开始的
