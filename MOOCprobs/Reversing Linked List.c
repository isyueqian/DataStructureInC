/*
02-线性结构3 Reversing Linked List (25分)
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (≤10
​5
​​ ) which is the total number of nodes, and a positive K (≤N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next



where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:
For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218



Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
 */

#include "stdio.h"

typedef struct Node List;
struct Node{
    int Address;
    int Data;
    int Next;
};

void Array(List a[], int N, int FirstAddress);
void Swap(List a[], int i, int j);
void Reverse(List a[], int N, int K);

int main(void) {

    int FirstAddress, N, K, i, eff=0; // with extra nodes that's not in the link list
    scanf("%d %d %d", &FirstAddress, &N, &K);
    List a[N];
    for(i=0; i<N; i++) {
        scanf("%d %d %d", &a[i].Address, &a[i].Data, &a[i].Next);
    }

    Array(a, N, FirstAddress);
    for(i=0; i<N; i++) {
        if(a[i].Next == -1) {
            eff = i+1;
        }
    }

    Reverse(a, eff, K);
    for(i=0; i<eff-1; i++) {
        a[i].Next = a[i+1].Address;
    }
    a[N-1].Next = -1;

    for(i=0; i<eff-1; i++) {
        printf("%05d %d %05d\n", a[i].Address, a[i].Data, a[i].Next);
    }
    printf("%05d %d %d\n", a[i].Address, a[i].Data, a[i].Next);

    return 0;
}

void Array(List a[], int N, int FirstAddress)
{
    int i, j;
    for(i=0; i<N; i++) {
        if (a[i].Address == FirstAddress) {
            Swap(a, i, 0);
            break;
        }
    }

    for(i=0; i<N-1; i++) {
        for(j=i+1; j<N; j++) {
            if (a[i].Next == a[j].Address) {
                Swap(a, i+1, j);
                break;
            }
        }
    }
}

void Swap(List a[], int i, int j)
{
    List tmp;
//    tmp.Address = a[i].Address;
//    tmp.Data = a[i].Data;
//    tmp.Next = a[i].Next;
//
//    a[i].Address = a[j].Address;
//    a[i].Data = a[j].Data;
//    a[i].Next = a[j].Next;
//
//    a[j].Address = tmp.Address;
//    a[j].Data = tmp.Data;
//    a[j].Next = tmp.Next;

     tmp = a[i];
     a[i] = a[j];
     a[j] = tmp;

}

void Reverse(List a[], int N, int K)
{
    int cnt = N/K;
    if(cnt) {
        for(int j=1; j<=cnt; j++) {
            for(int i=1; i<=K; i++) {
                if((j-1)*K+i-1 < j*K-i) {
                    Swap(a, (j-1)*K+i-1, j*K-i);
                }
            }
        }
    }
}