#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX_EDGES 100

// 간선을 표현하는 구조체
typedef struct {
    int src, dest, weight;
} Edge;

// Graph 구조체
typedef struct {
    int vertices, edges;
    Edge edge[MAX_EDGES];
} Graph;

// Subset 구조체 (Union-Find에서 사용)
typedef struct {
    int parent;
    int rank;
} Subset;

// 간선 비교 함수
int compareEdges(const void* a, const void* b);

// Union-Find: 부모 노드 찾기
int find(Subset subsets[], int i);

// Union-Find: 두 집합 합치기
void unionSets(Subset subsets[], int x, int y);

// Kruskal의 MST 알고리즘
void kruskalMST(Graph* graph);

// 실행 함수
void run();

#endif // KRUSKAL_H
