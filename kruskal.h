#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX_EDGES 100

// 간선 구조체
typedef struct {
    int src, dest, weight;
} Edge;

// Graph 구조체
typedef struct {
    int vertices, edges;
    Edge edge[MAX_EDGES];
} Graph;

// Subset 구조체
typedef struct {
    int parent;
    int rank;
} Subset;

// 간선 비교 함수
int compareEdges(const void* a, const void* b);

int find(Subset subsets[], int i);

void unionSets(Subset subsets[], int x, int y);

void kruskalMST(Graph* graph);

void run();

#endif // KRUSKAL_H
