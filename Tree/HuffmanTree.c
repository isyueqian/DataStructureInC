//
// This is an implementation of Huffman Tree by using minimum heap.
// Created by Lizzy on 2020/4/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MINDATA 0
#define ERROR NULL

typedef int ElementType;
typedef struct HTNode * HuffmanTree;
struct HTNode {
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

typedef struct HNode * Heap;
struct HNode {
    HuffmanTree * Data; // the array
    int Size; // current num
    int Capacity; // max num
};
typedef Heap MinHeap;

MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap) malloc(sizeof(struct HNode));
    H->Data = (HuffmanTree *) malloc(sizeof(HuffmanTree) * (MaxSize + 1)); // index starts from 1
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = (HuffmanTree) malloc(sizeof(struct HTNode));
    H->Data[0]->Weight = MINDATA; // 哨兵 = 0
    H->Data[0]->Right = H->Data[0]->Left = NULL;
    return H;
}

bool IsFull(MinHeap H)
{
    return H->Size == H->Capacity;
}

bool Insert(MinHeap H, HuffmanTree X)
{
    int i;

    if(IsFull(H)) {
        printf("Already full!");
        return false;
    }

    i = ++H->Size;
    for( ; H->Data[i / 2]->Weight > X->Weight; i/=2) {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = X;  // 上滤，且因为有哨兵结点的存在，不会超过数组的存储范围
    return true;
}

bool IsEmpty(MinHeap H)
{
    return H->Size == 0;
}

HuffmanTree DeleteMin(MinHeap H)
{
    int Parent, Child;
    HuffmanTree MinItem, X;

    if (IsEmpty(H)) {
        printf("Empty Heap!");
        return ERROR;
    }

    MinItem = H->Data[1];
    X = H->Data[H->Size--];

    for(Parent=1; Parent * 2 <= H->Size; Parent=Child) {
        Child = Parent*2;
        if ((Child!=H->Size) && (H->Data[Child]->Weight > H->Data[Child + 1]->Weight)) {
            Child++;
        }
        if (X->Weight <= H->Data[Child]->Weight) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = X;
    return MinItem;
}

void PercDown(MinHeap H, int p) // to build a heap
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
    int Parent, Child;
    HuffmanTree X;

    X = H->Data[p];
    for(Parent=p; Parent*2<=H->Size; Parent=Child) {
        Child = Parent*2;
        if((Child != H->Size) && (H->Data[Child]->Weight > H->Data[Child + 1]->Weight)) {
            Child++;
        }
        if (X->Weight <= H->Data[Child]->Weight) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = X;
}

void BuildHeap(MinHeap H)
{
    int i;

    for (i=H->Size/2; i>0; i--) {
        PercDown(H, i);
    }
}

HuffmanTree Huffman(MinHeap H)
{
    int i, N;
    HuffmanTree T;
    BuildHeap(H); // 调整为最小堆
    N = H->Size;
    for(i=1; i<N; i++) {
        T = (HuffmanTree) malloc(sizeof(struct HTNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    return DeleteMin(H);
}


// Queue
typedef struct Node * PtrToNode;
struct Node{
    HuffmanTree Data;
    PtrToNode Next;
};
typedef PtrToNode QPosition;
typedef struct QNode * PtrToQNode;
struct QNode{
    QPosition Front, Rear;
};
typedef PtrToQNode Queue;

Queue CreateQueue()
{
    Queue Q = (Queue) malloc(sizeof(struct QNode));
    Q->Front = (QPosition) malloc(sizeof(struct Node));
    Q->Front->Next = NULL;
    Q->Rear = Q->Front;
    return Q;
}

bool IsEmtpyQueue(Queue Q)
{
    return Q->Front->Next == NULL;
}

void AddQ(Queue Q, HuffmanTree BT)
{
    PtrToNode p = (PtrToNode) malloc(sizeof(struct Node));
    p->Data = BT;
    p->Next = NULL;
    Q->Rear->Next = p;
    Q->Rear = Q->Rear->Next;
}

HuffmanTree DeleteQ(Queue Q)
{
    HuffmanTree ret;
    if (IsEmtpyQueue(Q)) {
        ret = NULL;
    } else {
        PtrToNode tmp = Q->Front->Next;
        ret = tmp->Data;

        Q->Front->Next = Q->Front->Next->Next;
        if(Q->Front->Next==NULL) {
            Q->Rear = Q->Front;
        }
        free(tmp);
    }
    return ret;
}

void PrintHuffmanTree(HuffmanTree BT)
{
    Queue Q = CreateQueue();
    HuffmanTree T;

    if(!BT) return;

    AddQ(Q, BT);
    while (!IsEmtpyQueue(Q)) {
        T = DeleteQ(Q);
        printf("%d ", T->Weight);
        if(T->Left) {
            AddQ(Q, T->Left);
        }
        if(T->Right) {
            AddQ(Q, T->Right);
        }
    }
}


int main(void)
{
    int N, tmp;
    scanf("%d", &N);
    MinHeap H = CreateHeap(20);
    for (int i=1; i<=N; i++) {
        H->Data[i] = (HuffmanTree) malloc(sizeof(struct HTNode));
        scanf("%d", &tmp);
        H->Data[i]->Weight = tmp;
        H->Data[i]->Left = H->Data[i]->Right = NULL;
        H->Size++;
    }

    HuffmanTree T = Huffman(H);
    PrintHuffmanTree(T);

    return 0;
}

/*
input data:
5
1 2 3 4 5

output should be:
15 6 9 3 3 4 5 1 2

Things to learn from:
remember to initialize every pointer in an array, not just the array
 */
