//
// An example application of adding polynomial.
// Created by Lizzy on 2020/1/28.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode * PtrToPolyNode;
struct PolyNode{
    int Coef;
    int Expon;
    PtrToPolyNode Next;
};

typedef PtrToPolyNode Polynomial;

int Compare(int e1, int e2);
void Attach(int coef, int expon, Polynomial *PtrRear);
Polynomial PolyAdd(Polynomial P1, Polynomial P2);

int main(void)
{
    Polynomial P1, P2;
    P1 = (Polynomial) malloc(sizeof(struct PolyNode));
    P2 = (Polynomial) malloc(sizeof(struct PolyNode));

    P1->Coef = 2; // 2x^5 + 3x^4
    P1->Expon = 5;
    P1->Next = (Polynomial) malloc(sizeof(struct PolyNode));
    P1->Next->Coef = 3;
    P1->Next->Expon = 4;
    P1->Next->Next = NULL;

    P2->Coef = 7; // 7x^6 - x^5 + 9x^4
    P2->Expon = 6;
    P2->Next = (Polynomial) malloc(sizeof(struct PolyNode));
    P2->Next->Coef = -1;
    P2->Next->Expon = 5;
    P2->Next->Next = (Polynomial) malloc(sizeof(struct PolyNode));
    P2->Next->Next->Coef = 9;
    P2->Next->Next->Expon = 4;
    P2->Next->Next->Next = NULL; // signal for an end of polynomial

    Polynomial res = PolyAdd(P1, P2); // 7x^6 + x^5 + 12x^4
    PtrToPolyNode p = res;
    while(p) {
        printf("Coefficient: %d, Exponential %d\n", p->Coef, p->Expon);
        p = p->Next;
    }

    return 0;
}

int Compare(int e1, int e2)
{ // 比较指数大小
    int ret;
    if (e1>e2) {
        ret = 1;
    } else if (e1<e2) {
        ret = -1;
    } else {
        ret = 0;
    }
    return ret;
}

void Attach(int coef, int expon, Polynomial *PtrRear)
{
    Polynomial tmp = (Polynomial)malloc(sizeof(struct PolyNode));
    tmp->Coef = coef;
    tmp->Expon = expon;
    tmp->Next = NULL;

    (*PtrRear)->Next = tmp;
    *PtrRear = tmp;
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
    PtrToPolyNode front, rear, temp; // temp is important;
    int sum;
    rear = (PtrToPolyNode) malloc(sizeof(struct PolyNode));
    front = rear;

    while (P1 && P2)
    {
        switch (Compare(P1->Expon, P2->Expon)) {
            case 1:
                Attach(P1->Coef, P1->Expon, &rear);
                P1 = P1->Next;
                break;
            case -1:
                Attach(P2->Coef, P2->Expon, &rear);
                P2 = P2->Next;
                break;
            case 0:
                sum = P1->Coef + P2->Coef;
                if (sum) {
                    Attach(sum, P1->Expon, &rear);
                }
                P1 = P1->Next;
                P2 = P2->Next;
                break;
        }
    }

    for(;P1;P1=P1->Next) {
        Attach(P1->Coef, P1->Expon, &rear);
    }
    for(;P2;P2=P2->Next) {
        Attach(P2->Coef, P2->Expon, &rear);
    }

    rear->Next = NULL;
    temp = front;
    front = front->Next;
    free(temp);

    return front;
}

