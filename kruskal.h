#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX_EDGES 100

// ������ ǥ���ϴ� ����ü. ������ ����, ����, ����ġ�� int������ �����մϴ�.
typedef struct {
    int src, dest, weight;
} Edge;

// Graph ����ü. initGraph �Լ��� �����ϸ� ����� ������ ��� ��带 �մ� ������ ������ ����˴ϴ�.
// initNode �Լ��� �����ϸ� Edge ����ü�� �迭�� ����� ����ġ�� ����˴ϴ�. ��尡 n���� �� ������ ����Ǵ� ������ edge[0]�� 0��-0��, edge[1]�� 0��-1��....edge[n-1]�� 0��-n-1��, edge[n]�� 1��-2��....�����Դϴ�
//��� ������ 4�� ��츦 ���÷� ���ڸ� edge[0]: 0��-1���� �մ� ����, edge[1]: 0��-2���� �մ� ����, edge[2]: 0��-3���� �մ� ����, edge[3]: 1��-2���� �մ� ����, edge[4]: 1��-3���� �մ� ����, edge[5]: 2��-3���� �մ� �����Դϴ�.
//�̾����� ���� ������ ����ġ ���Ѵ��̸�, -1�� ǥ���˴ϴ�. ����ġ�� -1�� ������ ����ٸ� �� ���������� ���ܵ˴ϴ�.
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

// �θ� ��� ã��
int find(Subset subsets[], int i);

// �� ���� ��ġ��
void unionSets(Subset subsets[], int x, int y);

// Kruskal MST �˰���
Edge* kruskalMST(Graph* graph);

// �׷��� �ʱ�ȭ �Լ�
void initGraph(Graph* g, int v);

// ��� �ʱ�ȭ �Լ�
void initNode();

// ���� �Լ�
void run();

#endif // KRUSKAL_H
