//
// This is an implementation of union and find algorithm: 集合及其运算
// Created by Lizzy on 2020/4/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXN 1000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXN];

SetName Find(const SetType S, ElementType X)
{
    for(; S[X]>=0; X=S[X]);
    return X;
}

void Union(SetType S, SetName Root1, SetName Root2)
{
    S[Root2] = Root1;
}

void Union2(SetType S, SetName Root1, SetName Root2)  // 防止树越来越高
{
    if (S[Root2] < S[Root1]) { // 2>1, negative
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    } else {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}

SetName Find2(SetType S, ElementType X)  // 防止多次查找较远元素
{
    if (S[X]<0) {
        return X;
    } else {
        return S[X] = Find(S, S[X]);
    }
}