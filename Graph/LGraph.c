#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

// edge
typedef struct ENode * PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

// adjacent node
typedef struct AdjVNode * PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

// head node
typedef struct Vnode {
    PtrToAdjVNode FirstEdge;
    DataType Data;
} AdjList[MaxVertexNum];

// graph node
typedef struct GNode * PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

// initialize
LGraph CreateGraph(int VertexNum)
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph) malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V=0; V<Graph->Nv; V++) {
        Graph->G[V].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode) malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge; // insert at the head of E->V1
    Graph->G[E->V1].FirstEdge = NewNode;

    // if no-direction graph, <V2, V1> also needs to be attached.
    NewNode = (PtrToAdjVNode) malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);
    Graph=CreateGraph(Nv);

    scanf("%d", &(Graph->Ne));
    if(Graph->Ne!=0) {
        E = (Edge) malloc(sizeof(struct ENode));
        for(i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }
    scanf("\n");
    for(V=0; V<Graph->Nv; V++) {
        if (V<Graph->Nv-1) {
            scanf("%c ", &(Graph->G[V].Data));
        } else {
            scanf("%c", &(Graph->G[V].Data));
        }

    }

    return Graph;
}

void PrintGraph(LGraph Graph)
{
    PtrToAdjVNode p;
    printf("Num of vertex: %d\n", Graph->Nv);
    printf("Num of edge: %d\n", Graph->Ne);
    Vertex i;
    for(i=0; i<Graph->Nv; i++) {
        printf("%c ", Graph->G[i].Data);
        p = Graph->G[i].FirstEdge;
        while(p) {
            printf("-> %d(%d) ", p->AdjV, p->Weight);
            p = p->Next;
        }
        printf("\n");
    }
}

int main(void)
{
    LGraph G;
    G = BuildGraph();
    PrintGraph(G);
}



/*
### test input: ###
5
3
0 1 -2
2 3 -4
0 4 -10
A B C D E

### test output ###
Num of vertex: 5
Num of edge: 3
A -> 4(-10) -> 1(-2)
B -> 0(-2)
C -> 3(-4)
D -> 2(-4)
E -> 0(-10)
*/




















