#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX_EDGES 100

// ������ ǥ���ϴ� ����ü
typedef struct {
    int src, dest, weight;
} Edge;

// Graph ����ü
typedef struct {
    int vertices, edges;
    Edge edge[MAX_EDGES];
} Graph;

// Subset ����ü (Union-Find���� ���)
typedef struct {
    int parent;
    int rank;
} Subset;

// ���� �� �Լ�
int compareEdges(const void* a, const void* b);

// Union-Find: �θ� ��� ã��
int find(Subset subsets[], int i);

// Union-Find: �� ���� ��ġ��
void unionSets(Subset subsets[], int x, int y);

// Kruskal�� MST �˰���
void kruskalMST(Graph* graph);

// ���� �Լ�
void run();

#endif // KRUSKAL_H
