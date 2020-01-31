//
// This is an implementation of adding and multiplying two polynomials.
// Created by Lizzy on 2020/1/28.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct PolyNode * Polynomial;
struct PolyNode{
    int coef;
    int expon;
    Polynomial link;
};

Polynomial ReadPoly();
Polynomial Mult(Polynomial P1, Polynomial P2);
Polynomial Add(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);

int main(void)
{
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    PS = Add(P1, P2);
    PrintPoly(PS);

    return 0;
}

