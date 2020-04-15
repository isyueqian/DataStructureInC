//
// Basic operations of heap
// Created by Lizzy on 2020/4/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXDATA 1e9
#define ERROR -1

typedef int ElementType;
typedef struct HNode * Heap;
struct HNode {
    ElementType * Data; // the array
    int Size; // current num
    int Capacity; // max num
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

MaxHeap CreateHeap( int MaxSize)
{
    MaxHeap H = (MaxHeap) malloc(sizeof(struct HNode));
    H->Data = (ElementType*) malloc(sizeof(ElementType)*(MaxSize+1)); // index starts from 1
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA;
    return H;
}

bool IsFull(MaxHeap H)
{
    return H->Size == H->Capacity;
}

bool Insert(MaxHeap H, ElementType X)
{
    int i;

    if(IsFull(H)) {
        printf("Already full!");
        return false;
    }

    i = ++H->Size;
    for( ; H->Data[i/2] < X; i/=2) {
        H->Data[i] = H->Data[i/2];
    }
    H->Data[i] = X;  // 上滤，且因为有哨兵结点的存在，不会超过数组的存储范围
    return true;
}

bool IsEmpty(MaxHeap H)
{
    return H->Size == 0;
}

ElementType DeleteMax(MaxHeap H)
{
    int Parent, Child;
    ElementType MaxItem, X;

    if (IsEmpty(H)) {
        printf("Empty Heap!");
        return ERROR;
    }

    MaxItem = H->Data[1];
    X = H->Data[H->Size--];

    for(Parent=1; Parent * 2 <= H->Size; Parent=Child) {
        Child = Parent*2;
        if ((Child!=H->Size) && (H->Data[Child] < H->Data[Child+1])) {
            Child++;
        }
        if (X >= H->Data[Child]) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = X;
    return MaxItem;
}

void PercDown(MaxHeap H, int p) // to build a heap
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = H->Data[p];
    for(Parent=p; Parent*2<=H->Size; Parent=Child) {
        Child = Parent*2;
        if((Child != H->Size) && (H->Data[Child] < H->Data[Child+1])) {
            Child++;
        }
        if (X >= H->Data[Child]) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = X;
}

void BuildHeap(MaxHeap H)
{
    int i;

    for (i=H->Size/2; i>0; i--) {
        PercDown(H, i);
    }
}

void PrintHeap(MaxHeap H)
{
    int i;
    for(i=1; i<=H->Size; i++) {
        printf("%d", H->Data[i]);
        if (i != H->Size) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) // test the functions above
{
    int N;
    scanf("%d", &N);
    MaxHeap H = CreateHeap(20);
    for(int i=1; i<=N; i++) {
        scanf("%d", &H->Data[i]);
        H->Size++;
    }

    BuildHeap(H);
    PrintHeap(H);

    Insert(H, 20);
    PrintHeap(H);
    Insert(H, 50);
    PrintHeap(H);

    DeleteMax(H);
    PrintHeap(H);
    return 0;
}

/* input data
12
79 66 43 83 30 87 38 55 91 72 49 9
*/







