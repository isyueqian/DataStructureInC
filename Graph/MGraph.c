#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct GNode * PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];  // there are data in vertex
};
typedef PtrToGNode MGraph;  // matrix graph

// edge definition
typedef struct ENode * PtrToENode;
struct ENode {
    Vertex  V1, V2; // <V1, V2>
    WeightType Weight;
};
typedef PtrToENode Edge;


MGraph CreateGraph(int VertexNum) // create a graph with VertexNum vertex, no edge
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph) malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V=0; V<Graph->Nv; V++) { // initialization
        for(W=0; W<Graph->Nv; W++) {
            Graph->G[V][W] = INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight; // if no direction graph
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv); // num of vertex
    Graph = CreateGraph(Nv);

    scanf("%d", &(Graph->Ne));
    if(Graph->Ne != 0) {
        E = (Edge) malloc(sizeof(struct ENode));
        for(i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }

    // if there are data
    scanf("\n");
    for(V=0; V<Graph->Nv; V++) {
        if (V<Graph->Nv-1) {
            scanf("%c ", &Graph->Data[V]);
        } else {
            scanf("%c", &Graph->Data[V]);
        }
    }

    return Graph;
}

void PrintGraph(MGraph Graph)
{
    printf("Num of vertex: %d\n", Graph->Nv);
    printf("Num of edge: %d\n", Graph->Ne);
    int i, j;
    // print data
    for(i=0; i<Graph->Nv; i++) {
        printf("%c\t", Graph->Data[i]);
    }
    printf("\n");
    // print weight
    for(i=0; i<Graph->Nv; i++) {
        for(j=0; j<Graph->Nv; j++) {
            printf("%d\t", Graph->G[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    MGraph G;
    G = BuildGraph();
    PrintGraph(G);

    return 0;
}


/*
### test input: ###
5
3
0 1 -2
2 3 -4
0 4 -10
A B C D E

### output: ###
Num of vertex: 5
Num of edge: 3
A       B       C       D       E
65535   -2      65535   65535   -10
-2      65535   65535   65535   65535
65535   65535   65535   -4      65535
65535   65535   -4      65535   65535
-10     65535   65535   65535   65535
 */


