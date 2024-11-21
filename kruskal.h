#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX_EDGES 100

// 간선을 표현하는 구조체. 간선의 시작, 종료, 가중치를 int값으로 저장합니다.
typedef struct {
    int src, dest, weight;
} Edge;

// Graph 구조체. initGraph 함수를 실행하면 노드의 갯수와 모든 노드를 잇는 간선의 갯수가 저장됩니다.
// initNode 함수를 실행하면 Edge 구조체의 배열에 노드의 가중치가 저장됩니다. 노드가 n개일 때 간선이 저장되는 순서는 edge[0]에 0번-0번, edge[1]에 0번-1번....edge[n-1]에 0번-n-1번, edge[n]에 1번-2번....순서입니다
//노드 개수가 4인 경우를 예시로 들자면 edge[0]: 0번-1번을 잇는 간선, edge[1]: 0번-2번을 잇는 간선, edge[2]: 0번-3번을 잇는 간선, edge[3]: 1번-2번을 잇는 간선, edge[4]: 1번-3번을 잇는 간선, edge[5]: 2번-3번을 잇는 간선입니다.
//이어지지 않은 간선은 가중치 무한대이며, -1로 표현됩니다. 가중치가 -1인 간선이 생긴다면 총 간선수에서 제외됩니다.
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

// 부모 노드 찾기
int find(Subset subsets[], int i);

// 두 집합 합치기
void unionSets(Subset subsets[], int x, int y);

// Kruskal MST 알고리즘
Edge* kruskalMST(Graph* graph);

// 그래프 초기화 함수
void initGraph(Graph* g, int v);

// 노드 초기화 함수
void initNode();

// 실행 함수
void run();

#endif // KRUSKAL_H
